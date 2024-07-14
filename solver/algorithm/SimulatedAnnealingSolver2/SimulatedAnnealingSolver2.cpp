#include "SimulatedAnnealingSolver2.hpp"
#include "BIT.hpp"
#include "CumulativeSumMaxSegmentTree.hpp"
#include "common.hpp"
#include "random_generator.hpp"
#include "timer.hpp"
#include "validator.hpp"

Solution SimulatedAnnealingSolver2::solve(const Problem &problem) {
    Solution solution;
    RandomGenerator &rng = RandomGenerator::getInstance();

    // 荷物の総数
    int M = (problem.N * problem.N - 1) >> 1;

    // 初期温度と終了温度
    double startTemp = 50;
    double endTemp = 0;

    // 各荷物について積まれるタイミングと降ろされるタイミングを記録
    std::vector<int> startTime(M + 1, 0);
    std::vector<int> goalTime(M + 1, 0);

    // 初期解の生成
    std::vector<int> currentPerm(M << 1);
    BIT bt(M << 1 | 1);
    for (int i = 0; i < M; i++) {
        currentPerm[i << 1] = i + 1;
        currentPerm[i << 1 | 1] = -i - 1;
        startTime[i + 1] = i << 1;
        goalTime[i + 1] = i << 1 | 1;
        if (i == 0) {
            bt.add(i << 1, manhattan_distance(std::make_pair(0, 0),
                                              problem.start[i + 1]));
            bt.add(i << 1 | 1, manhattan_distance(problem.start[i + 1],
                                                  problem.goal[i + 1]));
        } else {
            bt.add(i << 1,
                   manhattan_distance(problem.goal[i], problem.start[i + 1]));
            bt.add(i << 1 | 1, manhattan_distance(problem.start[i + 1],
                                                  problem.goal[i + 1]));
        }
    }
    bt.add(M << 1, manhattan_distance(problem.goal[M], std::make_pair(0, 0)));
    CumulativeSumMaxSegmentTree cst(M << 1);
    {
        std::vector<int> val(M << 1);
        for (int i = 0; i < M << 1; i++) {
            val[i] = (currentPerm[i] > 0 ? 1 : -1);
        }
        cst.build(val);
    }

    // 初期解の評価
    Cost currentCost = 0;
    Coordinate currentPos = std::make_pair(0, 0);
    {
        int cargo = 0;
        for (auto i : currentPerm) {
            if (i > 0) {
                Coordinate start = problem.start[i];
                currentCost +=
                    manhattan_distance(currentPos, start) * (cargo + 1);
                cargo++;
                currentCost++;
                currentPos = start;
            } else {
                Coordinate goal = problem.goal[-i];
                currentCost +=
                    manhattan_distance(currentPos, goal) * (cargo + 1);
                cargo--;
                currentCost++;
                currentPos = goal;
            }
        }
        currentCost +=
            manhattan_distance(currentPos, std::make_pair(0, 0)) * (cargo + 1);
    }

    // 現在の解を最良解として記録
    Cost bestCost = currentCost;
    std::vector<int> bestPerm = currentPerm;

    // 焼きなまし法
    Timer timer;
    timer.start();
    double totalTime = 10000;
    double nowTime = 0.0;

    int iter = 0;
    int accepted = 0;

    while (nowTime < totalTime) {
        // 現在の温度
        double temp = updateTemp(startTemp, endTemp, nowTime, totalTime);

        // 経過時間の更新
        nowTime = timer.getElapsedMilliseconds();

        // 2点swap
        int l = rng.randint(0, M << 1), r = rng.randint(0, M << 1);
        // int l = rng.randint(0, (M << 1) - 1), r = l + 1;
        if (l > r)
            std::swap(l, r);
        while (l == r || currentPerm[l] == -currentPerm[r]) {
            r = rng.randint(0, M << 1);
            if (l > r)
                std::swap(l, r);
        }
        bool flag = true;
        if (currentPerm[l] > 0) {
            if (r > goalTime[currentPerm[l]])
                flag = false;
        }
        if (currentPerm[r] < 0) {
            if (l < startTime[-currentPerm[r]])
                flag = false;
        }
        if (!flag)
            continue;

        ++iter;

        cst.set(l, currentPerm[r] > 0 ? 1 : -1);
        cst.set(r, currentPerm[l] > 0 ? 1 : -1);
        if (!cst.is_valid_cargo(problem.K)) {
            cst.set(l, currentPerm[l] > 0 ? 1 : -1);
            cst.set(r, currentPerm[r] > 0 ? 1 : -1);
            continue;
        }

        // コスト計算
        // Cost newCost = currentCost;
        // currentPos = std::make_pair(0, 0);
        // {
        //     int cargo = 0;
        //     for (auto i : currentPerm) {
        //         if (i > 0) {
        //             Coordinate start = problem.start[i];
        //             currentCost +=
        //                 manhattan_distance(currentPos, start) * (cargo + 1);
        //             cargo++;
        //             currentCost++;
        //             currentPos = start;
        //         } else {
        //             Coordinate goal = problem.goal[-i];
        //             currentCost +=
        //                 manhattan_distance(currentPos, goal) * (cargo + 1);
        //             cargo--;
        //             currentCost++;
        //             currentPos = goal;
        //         }
        //     }
        //     currentCost +=
        //         manhattan_distance(currentPos, std::make_pair(0, 0)) *
        //         (cargo + 1);
        // }

        std::swap(currentPerm[l], currentPerm[r]);

        // 経路長の差分計算
        updateDistance(l, currentPerm, problem, bt, M);
        updateDistance(r, currentPerm, problem, bt, M);

        // スコア計算（差分計算）
        Cost newCost = currentCost;
        if (currentPerm[l] * currentPerm[r] < 0 && r > l + 2) {
            newCost += (currentPerm[l] / std::abs(currentPerm[l]) -
                        currentPerm[r] / std::abs(currentPerm[r])) *
                       bt.sum(l + 2, r);
        }

        {
            int cargo = 0;
            if (l > 0) {
                cargo = cst.prodSum(0, l);
            }
            newCost += (cargo + 1) * bt.sum(l, l + 1);
            cargo += (currentPerm[l] > 0 ? 1 : -1);
            newCost += (cargo + 1) * bt.sum(l + 1, l + 2);
            cargo += (currentPerm[l + 1] > 0 ? 1 : -1);
            if (r != l + 1) {
                cargo = cst.prodSum(0, r);
                newCost += (cargo + 1) * bt.sum(r, r + 1);
                cargo += (currentPerm[r] > 0 ? 1 : -1);
            }
            newCost += (cargo + 1) * bt.sum(r + 1, r + 2);
        }
        std::swap(currentPerm[l], currentPerm[r]);
        cst.set(l, currentPerm[l] > 0 ? 1 : -1);
        cst.set(r, currentPerm[r] > 0 ? 1 : -1);
        updateDistance(l, currentPerm, problem, bt, M);
        updateDistance(r, currentPerm, problem, bt, M);
        {
            int cargo = 0;
            if (l > 0) {
                cargo = cst.prodSum(0, l);
            }
            newCost -= (cargo + 1) * bt.sum(l, l + 1);
            cargo += (currentPerm[l] > 0 ? 1 : -1);
            newCost -= (cargo + 1) * bt.sum(l + 1, l + 2);
            cargo += (currentPerm[l + 1] > 0 ? 1 : -1);
            if (r != l + 1) {
                cargo = cst.prodSum(0, r);
                newCost -= (cargo + 1) * bt.sum(r, r + 1);
                cargo += (currentPerm[r] > 0 ? 1 : -1);
            }
            newCost -= (cargo + 1) * bt.sum(r + 1, r + 2);
        }

        if (acceptanceProb(currentCost, newCost, temp) > rng.rnd()) {
            currentCost = newCost;
            if (currentPerm[l] < 0) {
                goalTime[-currentPerm[l]] = r;
            } else {
                startTime[currentPerm[l]] = r;
            }
            if (currentPerm[r] < 0) {
                goalTime[-currentPerm[r]] = l;
            } else {
                startTime[currentPerm[r]] = l;
            }
            std::swap(currentPerm[l], currentPerm[r]);
            cst.set(l, currentPerm[l] > 0 ? 1 : -1);
            cst.set(r, currentPerm[r] > 0 ? 1 : -1);
            updateDistance(l, currentPerm, problem, bt, M);
            updateDistance(r, currentPerm, problem, bt, M);
            ++accepted;
            // log_message(LogLevel::DEBUG,
            //         "l: " + std::to_string(l) + ", r: " + std::to_string(r) +
            //             ", cost: " + std::to_string(newCost) +
            //             ", L: " + std::to_string(currentPerm[l]) +
            //             ", R: " + std::to_string(currentPerm[r]));
        }

        // 最良解の更新
        if (currentCost < bestCost) {
            bestPerm = currentPerm;
            bestCost = currentCost;
        }
    }

    log_message(LogLevel::INFO, "iter: " + std::to_string(iter));
    log_message(LogLevel::INFO, "accepted: " + std::to_string(accepted));

    // 最良解をsolutionに変換
    solution.costs.push_back(bestCost);
    Operations operations;
    currentPos = std::make_pair(0, 0);
    for (auto i : bestPerm) {
        if (i > 0) {
            Coordinate start = problem.start[i];
            Operations move = load_operation(i, currentPos, start);
            operations.insert(operations.end(), move.begin(), move.end());
            currentPos = start;
        } else {
            Coordinate goal = problem.goal[-i];
            Operations move = unload_operation(-i, currentPos, goal);
            operations.insert(operations.end(), move.begin(), move.end());
            currentPos = goal;
        }
    }
    Operations move = get_route(currentPos, std::make_pair(0, 0));
    operations.insert(operations.end(), move.begin(), move.end());
    solution.multi_operations.push_back(operations);

    return solution;
}

Coordinate SimulatedAnnealingSolver2::getPoint(const std::vector<int> &perm,
                                               const Problem &problem,
                                               int index) {
    if (perm[index] > 0) {
        return problem.start[perm[index]];
    } else {
        return problem.goal[-perm[index]];
    }
}

void SimulatedAnnealingSolver2::updateDistance(int index,
                                               const std::vector<int> &perm,
                                               const Problem &problem, BIT &bt,
                                               int M) {
    int dist = 0;
    if (index > 0) {
        dist += manhattan_distance(getPoint(perm, problem, index - 1),
                                   getPoint(perm, problem, index));
    } else {
        dist += manhattan_distance(std::make_pair(0, 0),
                                   getPoint(perm, problem, index));
    }
    bt.add(index, -bt.sum(index, index + 1) + dist);

    dist = 0;
    if (index < (M << 1) - 1) {
        dist += manhattan_distance(getPoint(perm, problem, index),
                                   getPoint(perm, problem, index + 1));
    } else {
        dist += manhattan_distance(getPoint(perm, problem, index),
                                   std::make_pair(0, 0));
    }
    bt.add(index + 1, -bt.sum(index + 1, index + 2) + dist);
}