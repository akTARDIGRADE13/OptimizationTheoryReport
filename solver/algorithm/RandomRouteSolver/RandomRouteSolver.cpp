#include "RandomRouteSolver.hpp"
#include "common.hpp"
#include "random_generator.hpp"
#include "timer.hpp"
#include "validator.hpp"

#include <algorithm>
#include <cassert>
#include <numeric>
#include <string>

Solution RandomRouteSolver::solve(const Problem &problem) {
    Solution solution;
    RandomGenerator &rng = RandomGenerator::getInstance();

    // 荷物の総数
    int M = (problem.N * problem.N - 1) >> 1;

    // 10秒間乱択を繰り返す
    Timer timer;
    timer.start();
    while (timer.getElapsedMilliseconds() < 10000) {
        // ランダムに順列を生成
        std::vector<int> permutation(M);
        std::iota(permutation.begin(), permutation.end(), 1);
        rng.randshf(permutation);

        // 順列を操作に変換
        Operations operations;
        Coordinate current = std::make_pair(0, 0);
        for (int i : permutation) {

            // 荷物 i がある座標
            Coordinate start = std::make_pair(-1, -1);
            for (int x = 0; x < problem.N && start.first < 0; ++x) {
                for (int y = 0; y < problem.N && start.first < 0; ++y) {
                    if (problem.grid[x][y] == i) {
                        start = std::make_pair(x, y);
                    }
                }
            }

            // 荷物 i の目的地
            Coordinate goal = std::make_pair(-1, -1);
            for (int x = 0; x < problem.N && goal.first < 0; ++x) {
                for (int y = 0; y < problem.N && goal.first < 0; ++y) {
                    if (problem.grid[x][y] == -i) {
                        goal = std::make_pair(x, y);
                    }
                }
            }

            Operations move = move_operation(i, current, start, goal);
            operations.insert(operations.end(), move.begin(), move.end());
            current = goal;
        }

        std::string operations_str = "";
        for (const auto &op : operations) {
            operations_str += op + " ";
        }

        // この操作列のコストを計算
        Cost cost = validate_solution(problem, operations);
        if (cost == -1) {
            log_message(LogLevel::ERROR, "Invalid solution");
            assert(false);
        }

        // これまでの最良解よりも良ければ追加
        if (solution.costs.empty() || cost < solution.costs.back()) {
            solution.costs.push_back(cost);
            solution.multi_operations.push_back(operations);
        }
    }
    return solution;
}
