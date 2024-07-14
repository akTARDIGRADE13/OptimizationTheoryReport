#include "SimulatedAnnealingSolver.hpp"
#include "common.hpp"
#include "random_generator.hpp"
#include "timer.hpp"
#include "validator.hpp"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <numeric>
#include <string>

Solution SimulatedAnnealingSolver::solve(const Problem &problem) {
    Solution solution;
    RandomGenerator &rng = RandomGenerator::getInstance();

    // 荷物の総数
    int M = (problem.N * problem.N - 1) >> 1;

    // 初期温度と終了温度
    double startTemp = 50;
    double endTemp = 0;

    // 初期解の生成
    std::vector<int> currentPerm(M);
    std::iota(currentPerm.begin(), currentPerm.end(), 1);
    rng.randshf(currentPerm);

    // 初期解の評価
    Cost currentCost = 0;
    Coordinate currentPos = std::make_pair(0, 0);
    for (auto i : currentPerm) {
        Coordinate start = problem.start[i];
        Coordinate goal = problem.goal[i];
        currentCost += manhattan_distance(currentPos, start);
        currentCost++;
        currentCost += manhattan_distance(start, goal) * 2;
        currentCost++;
        currentPos = goal;
    }
    currentCost += manhattan_distance(currentPos, std::make_pair(0, 0));

    // 現在の解を最良解として記録
    Cost bestCost = currentCost;
    std::vector<int> bestPerm = currentPerm;

    // 焼きなまし法
    Timer timer;
    timer.start();
    double totalTime = 10000;
    double nowTime = 0.0;
    while (nowTime < totalTime) {
        // 現在の温度
        double temp = updateTemp(startTemp, endTemp, nowTime, totalTime);

        // 2点swap
        int l = rng.randint(0, M);
        int r = rng.randint(0, M);
        if (l > r)
            std::swap(l, r);

        // スコア計算（差分計算）
        Cost newCost = currentCost;
        auto calc = [&](int idx, std::vector<int> &perm) -> Cost {
            assert(0 <= idx && idx < M);
            Cost ret = 0;
            Coordinate start = problem.start[perm[idx]];
            Coordinate goal = problem.goal[perm[idx]];
            if (idx > 0) {
                ret += manhattan_distance(problem.goal[perm[idx - 1]], start);
            } else {
                ret += manhattan_distance(std::make_pair(0, 0), start);
            }
            if (idx < M - 1) {
                ret += manhattan_distance(goal, problem.start[perm[idx + 1]]);
            } else {
                ret += manhattan_distance(goal, std::make_pair(0, 0));
            }
            return ret;
        };

        newCost -= calc(l, currentPerm);
        newCost -= calc(r, currentPerm);
        if (l + 1 == r) {
            newCost += manhattan_distance(problem.goal[currentPerm[l]],
                                          problem.start[currentPerm[r]]);
        }
        std::swap(currentPerm[l], currentPerm[r]);
        newCost += calc(l, currentPerm);
        newCost += calc(r, currentPerm);
        if (l + 1 == r) {
            newCost -= manhattan_distance(problem.goal[currentPerm[l]],
                                          problem.start[currentPerm[r]]);
        }

        // 遷移
        if (acceptanceProb(currentCost, newCost, temp) > rng.rnd()) {
            currentCost = newCost;
        } else {
            std::swap(currentPerm[l], currentPerm[r]);
        }

        // 最良解の更新
        if (currentCost < bestCost) {
            bestPerm = currentPerm;
            bestCost = currentCost;
        }

        // 時間の更新
        nowTime = timer.getElapsedMilliseconds();
    }

    // 最良解を解として返す
    solution.costs.push_back(bestCost);
    currentPos = std::make_pair(0, 0);
    Operations operations;
    for (auto i : bestPerm) {
        Coordinate start = problem.start[i];
        Coordinate goal = problem.goal[i];
        Operations move = move_operation(i, currentPos, start, goal);
        operations.insert(operations.end(), move.begin(), move.end());
        currentPos = goal;
    }
    Operations move = get_route(currentPos, std::make_pair(0, 0));
    operations.insert(operations.end(), move.begin(), move.end());
    solution.multi_operations.push_back(operations);
    log_message(LogLevel::INFO,
                "Simulated Annealing: " + std::to_string(bestCost) + " " +
                    std::to_string(validate_solution(problem, operations)));
    std::cerr << std::endl;
    assert(validate_solution(problem, operations) == bestCost);
    return solution;
}