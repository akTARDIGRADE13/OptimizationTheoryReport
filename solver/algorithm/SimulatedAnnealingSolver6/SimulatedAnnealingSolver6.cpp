#include "SimulatedAnnealingSolver6.hpp"
#include "common.hpp"
#include "random_generator.hpp"
#include "timer.hpp"
#include "validator.hpp"

Solution SimulatedAnnealingSolver6::solve(const Problem &problem) {
    Solution solution;
    RandomGenerator &rng = RandomGenerator::getInstance();

    // 荷物の総数
    int M = (problem.N * problem.N - 1) >> 1;

    // 初期温度と終了温度
    double startTemp = 10;
    double endTemp = 0;

    // 各荷物について積まれるタイミングと降ろされるタイミングを記録
    std::vector<int> startTime(M + 1, 0);
    std::vector<int> goalTime(M + 1, 0);

    // 初期解の生成
    std::vector<int> currentPerm(M << 1);
    for (int i = 0; i < M; i++) {
        currentPerm[i << 1] = i + 1;
        currentPerm[i << 1 | 1] = -i - 1;
        startTime[i + 1] = i << 1;
        goalTime[i + 1] = i << 1 | 1;
    }
    std::vector<Cost> costs((M << 1) + 2, 0);
    std::vector<int> cargos((M << 1) + 1, 0);

    // 初期解の評価
    Cost currentCost = calcCost(currentPerm, problem, M, costs, cargos, 0);

    // 現在の解を最良解として記録
    std::vector<int> bestPerm = currentPerm;
    Cost bestCost = currentCost;

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

        // 抜き出して別の場所に挿入
        int DIFF = 3;
        int now = rng.randint(0, (M << 1) - DIFF),
            nxt = rng.randint(std::max(0, now - DIFF),
                              std::min(M << 1, now + DIFF + 1));

        // validか判定
        auto isValid = [&](int now, int nxt) {
            if (now == nxt)
                return false;
            if (currentPerm[now] == -currentPerm[nxt])
                return false;
            if (now < nxt) {
                if (currentPerm[now] > 0) {
                    if (goalTime[currentPerm[now]] - 1 < nxt) {
                        return false;
                    }
                } else {
                    for (int i = now + 1; i <= nxt; i++) {
                        if (cargos[i] + 1 > problem.K) {
                            return false;
                        }
                    }
                }
            } else {
                if (currentPerm[now] < 0) {
                    if (startTime[-currentPerm[now]] + 1 > nxt) {
                        return false;
                    }
                } else {
                    for (int i = nxt; i < now; i++) {
                        if (cargos[i] + 1 > problem.K) {
                            return false;
                        }
                    }
                }
            }
            return true;
        };

        while (!isValid(now, nxt)) {
            now = rng.randint(0, (M << 1) - DIFF);
            nxt = rng.randint(std::max(0, now - DIFF),
                              std::min(M << 1, now + DIFF + 1));
        }

        ++iter;

        if (now < nxt) {
            std::rotate(currentPerm.begin() + now,
                        currentPerm.begin() + now + 1,
                        currentPerm.begin() + nxt + 1);
        } else {
            std::rotate(currentPerm.begin() + nxt, currentPerm.begin() + now,
                        currentPerm.begin() + now + 1);
        }

        // 評価
        Cost nextCost = calcCost(currentPerm, problem, M, costs, cargos,
                                 std::min(now, nxt));

        if (acceptanceProb(currentCost, nextCost, temp) > rng.rnd()) {
            currentCost = nextCost;
            accepted++;
            for (int i = std::min(now, nxt); i <= std::max(now, nxt); i++) {
                if (currentPerm[i] > 0) {
                    startTime[currentPerm[i]] = i;
                } else {
                    goalTime[-currentPerm[i]] = i;
                }
            }
        } else {
            if (now < nxt) {
                std::rotate(currentPerm.begin() + now,
                            currentPerm.begin() + nxt,
                            currentPerm.begin() + nxt + 1);
            } else {
                std::rotate(currentPerm.begin() + nxt,
                            currentPerm.begin() + nxt + 1,
                            currentPerm.begin() + now + 1);
            }
            calcCost(currentPerm, problem, M, costs, cargos,
                     std::min(now, nxt));
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
    Coordinate currentPos = std::make_pair(0, 0);
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

Coordinate SimulatedAnnealingSolver6::getPoint(const std::vector<int> &perm,
                                               const Problem &problem,
                                               int index) {
    if (perm[index] > 0) {
        return problem.start[perm[index]];
    } else {
        return problem.goal[-perm[index]];
    }
}

Cost SimulatedAnnealingSolver6::calcCost(const std::vector<int> &perm,
                                         const Problem &problem, int M,
                                         std::vector<Cost> &costs,
                                         std::vector<int> &cargos, int start) {
    Coordinate currentPos = std::make_pair(0, 0);
    if (start > 0) {
        currentPos = getPoint(perm, problem, start - 1);
    }
    for (int i = start; i < (M << 1); i++) {
        if (perm[i] > 0) {
            Coordinate tmp = problem.start[perm[i]];
            costs[i + 1] =
                manhattan_distance(currentPos, tmp) * (cargos[i] + 1) +
                costs[i];
            cargos[i + 1] = cargos[i] + 1;
            costs[i + 1]++;
            currentPos = tmp;
        } else {
            Coordinate tmp = problem.goal[-perm[i]];
            costs[i + 1] =
                manhattan_distance(currentPos, tmp) * (cargos[i] + 1) +
                costs[i];
            cargos[i + 1] = cargos[i] - 1;
            costs[i + 1]++;
            currentPos = tmp;
        }
    }
    costs[(M << 1) + 1] =
        costs[M << 1] + manhattan_distance(currentPos, std::make_pair(0, 0)) *
                            (cargos[M << 1] + 1);
    return costs[(M << 1) + 1];
}