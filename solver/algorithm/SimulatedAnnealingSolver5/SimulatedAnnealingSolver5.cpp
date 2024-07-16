#include "SimulatedAnnealingSolver5.hpp"
#include "BIT.hpp"
#include "StarrySkyTree.hpp"
#include "common.hpp"
#include "random_generator.hpp"
#include "timer.hpp"
#include "validator.hpp"

Solution SimulatedAnnealingSolver5::solve(const Problem &problem) {
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
    StarrySkyTree sst(M << 1);
    {
        std::vector<int> val(M << 1);
        for (int i = 0; i < M << 1; i++) {
            val[i] = (currentPerm[i] > 0 ? 1 : -1);
        }
        sst.build(val);
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
    double totalTime = 600000;
    double nowTime = 0.0;

    int iter = 0;
    int accepted = 0;

    while (nowTime < totalTime) {
        // 現在の温度
        double temp = updateTemp(startTemp, endTemp, nowTime, totalTime);

        // 経過時間の更新
        nowTime = timer.getElapsedMilliseconds();

        int BORDER = 30;
        if (rng.randint(0, 100) < BORDER) {

            // 2点swap
            int DIFF = 5;
            int l = rng.randint(0, (M << 1) - DIFF),
                r = rng.randint(l + 1, std::min(M << 1, l + DIFF + 1));
            while (l == r || currentPerm[l] == -currentPerm[r]) {
                l = rng.randint(0, (M << 1) - DIFF),
                r = rng.randint(l + 1, std::min(M << 1, l + DIFF + 1));
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
            if (currentPerm[l] * currentPerm[r] < 0) {
                sst.set(l, currentPerm[r] > 0 ? 1 : -1);
                sst.set(r, currentPerm[l] > 0 ? 1 : -1);
            }
            if (!sst.is_valid_cargo(problem.K)) {
                if (currentPerm[l] * currentPerm[r] < 0) {
                    sst.set(l, currentPerm[l] > 0 ? 1 : -1);
                    sst.set(r, currentPerm[r] > 0 ? 1 : -1);
                }
                continue;
            }

            // if (iter % 5000000 == 0) {
            //     log_message(LogLevel::INFO,
            //                 "bestCost: " + std::to_string(bestCost) +
            //                     " iter: " + std::to_string(iter) +
            //                     " temperature: " + std::to_string(temp));
            // }

            ++iter;

            std::swap(currentPerm[l], currentPerm[r]);

            // 経路長の差分計算
            updateDistance(l, currentPerm, problem, bt, M);
            updateDistance(r, currentPerm, problem, bt, M);

            // スコア計算（差分計算）
            Cost newCost = calculateNewCost(l, r, currentPerm, problem, bt, sst,
                                            currentCost);
            std::swap(currentPerm[l], currentPerm[r]);
            if (currentPerm[l] * currentPerm[r] < 0) {
                sst.set(l, currentPerm[l] > 0 ? 1 : -1);
                sst.set(r, currentPerm[r] > 0 ? 1 : -1);
            }
            updateDistance(l, currentPerm, problem, bt, M);
            updateDistance(r, currentPerm, problem, bt, M);
            newCost = calculateCostAfterSwapBack(l, r, currentPerm, problem, bt,
                                                 sst, newCost);

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
                if (currentPerm[l] * currentPerm[r] < 0) {
                    sst.set(l, currentPerm[l] > 0 ? 1 : -1);
                    sst.set(r, currentPerm[r] > 0 ? 1 : -1);
                }
                updateDistance(l, currentPerm, problem, bt, M);
                updateDistance(r, currentPerm, problem, bt, M);
                ++accepted;
            }
        } else {
            // 荷物を二つ選ぶ
            int l = rng.randint(0, M), r = rng.randint(0, M);
            while (l == r) {
                r = rng.randint(0, M);
            }
            ++l, ++r;
            if (startTime[l] > startTime[r]) {
                std::swap(l, r);
            }

            // if (iter % 5000000 == 0) {
            //     log_message(LogLevel::INFO,
            //                 "bestCost: " + std::to_string(bestCost) +
            //                     " iter: " + std::to_string(iter) +
            //                     " temperature: " + std::to_string(temp));
            // }

            ++iter;

            // 変更される経路
            std::vector<int> change;
            change.push_back(startTime[l]);
            change.push_back(startTime[l] + 1);
            change.push_back(goalTime[l]);
            change.push_back(goalTime[l] + 1);
            change.push_back(startTime[r]);
            change.push_back(startTime[r] + 1);
            change.push_back(goalTime[r]);
            change.push_back(goalTime[r] + 1);
            std::sort(change.begin(), change.end());
            change.erase(std::unique(change.begin(), change.end()),
                         change.end());

            // スコア計算（差分計算）
            Cost newCost = currentCost;
            for (auto i : change) {
                int cargo = 0;
                if (i > 0) {
                    cargo = sst.prodSum(0, i);
                }
                newCost -= (cargo + 1) * bt.sum(i, i + 1);
            }

            std::swap(currentPerm[startTime[l]], currentPerm[startTime[r]]);
            std::swap(currentPerm[goalTime[l]], currentPerm[goalTime[r]]);
            if (currentPerm[startTime[l]] * currentPerm[startTime[r]] < 0) {
                sst.set(startTime[l], currentPerm[startTime[l]] > 0 ? 1 : -1);
                sst.set(startTime[r], currentPerm[startTime[r]] > 0 ? 1 : -1);
            }
            if (currentPerm[goalTime[l]] * currentPerm[goalTime[r]] < 0) {
                sst.set(goalTime[l], currentPerm[goalTime[l]] > 0 ? 1 : -1);
                sst.set(goalTime[r], currentPerm[goalTime[r]] > 0 ? 1 : -1);
            }
            updateDistance(startTime[l], currentPerm, problem, bt, M);
            updateDistance(startTime[r], currentPerm, problem, bt, M);
            updateDistance(goalTime[l], currentPerm, problem, bt, M);
            updateDistance(goalTime[r], currentPerm, problem, bt, M);

            for (auto i : change) {
                int cargo = 0;
                if (i > 0) {
                    cargo = sst.prodSum(0, i);
                }
                newCost += (cargo + 1) * bt.sum(i, i + 1);
            }

            if (acceptanceProb(currentCost, newCost, temp) > rng.rnd()) {
                currentCost = newCost;
                std::swap(startTime[l], startTime[r]);
                std::swap(goalTime[l], goalTime[r]);
                ++accepted;
            } else {
                std::swap(currentPerm[startTime[l]], currentPerm[startTime[r]]);
                std::swap(currentPerm[goalTime[l]], currentPerm[goalTime[r]]);
                if (currentPerm[startTime[l]] * currentPerm[startTime[r]] < 0) {
                    sst.set(startTime[l],
                            currentPerm[startTime[l]] > 0 ? 1 : -1);
                    sst.set(startTime[r],
                            currentPerm[startTime[r]] > 0 ? 1 : -1);
                }
                if (currentPerm[goalTime[l]] * currentPerm[goalTime[r]] < 0) {
                    sst.set(goalTime[l], currentPerm[goalTime[l]] > 0 ? 1 : -1);
                    sst.set(goalTime[r], currentPerm[goalTime[r]] > 0 ? 1 : -1);
                }
                updateDistance(startTime[l], currentPerm, problem, bt, M);
                updateDistance(startTime[r], currentPerm, problem, bt, M);
                updateDistance(goalTime[l], currentPerm, problem, bt, M);
                updateDistance(goalTime[r], currentPerm, problem, bt, M);
            }
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

Coordinate SimulatedAnnealingSolver5::getPoint(const std::vector<int> &perm,
                                               const Problem &problem,
                                               int index) {
    if (perm[index] > 0) {
        return problem.start[perm[index]];
    } else {
        return problem.goal[-perm[index]];
    }
}

void SimulatedAnnealingSolver5::updateDistance(int index,
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

Cost SimulatedAnnealingSolver5::calculateNewCost(int l, int r,
                                                 const std::vector<int> &perm,
                                                 const Problem &problem,
                                                 BIT &bt, StarrySkyTree &sst,
                                                 Cost currentCost) {
    Cost newCost = currentCost;
    if (perm[l] * perm[r] < 0 && r > l + 2) {
        newCost += (perm[l] / std::abs(perm[l]) - perm[r] / std::abs(perm[r])) *
                   bt.sum(l + 2, r);
    }

    int cargo = 0;
    if (l > 0) {
        cargo = sst.prodSum(0, l);
    }
    newCost += (cargo + 1) * bt.sum(l, l + 1);
    cargo += (perm[l] > 0 ? 1 : -1);
    newCost += (cargo + 1) * bt.sum(l + 1, l + 2);
    cargo += (perm[l + 1] > 0 ? 1 : -1);
    if (r != l + 1) {
        cargo = sst.prodSum(0, r);
        newCost += (cargo + 1) * bt.sum(r, r + 1);
        cargo += (perm[r] > 0 ? 1 : -1);
    }
    newCost += (cargo + 1) * bt.sum(r + 1, r + 2);

    return newCost;
}

Cost SimulatedAnnealingSolver5::calculateCostAfterSwapBack(
    int l, int r, const std::vector<int> &perm, const Problem &problem, BIT &bt,
    StarrySkyTree &sst, Cost currentCost) {
    Cost newCost = currentCost;

    int cargo = 0;
    if (l > 0) {
        cargo = sst.prodSum(0, l);
    }
    newCost -= (cargo + 1) * bt.sum(l, l + 1);
    cargo += (perm[l] > 0 ? 1 : -1);
    newCost -= (cargo + 1) * bt.sum(l + 1, l + 2);
    cargo += (perm[l + 1] > 0 ? 1 : -1);
    if (r != l + 1) {
        cargo = sst.prodSum(0, r);
        newCost -= (cargo + 1) * bt.sum(r, r + 1);
        cargo += (perm[r] > 0 ? 1 : -1);
    }
    newCost -= (cargo + 1) * bt.sum(r + 1, r + 2);

    return newCost;
}