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

    // ベストスコア
    Cost best_cost = std::numeric_limits<Cost>::max();
    // ベストスコアの順列
    std::vector<int> best_permutation;

    // 10秒間乱択を繰り返す
    Timer timer;
    timer.start();
    while (timer.getElapsedMilliseconds() < 10000) {
        // ランダムに順列を生成
        std::vector<int> permutation(M);
        std::iota(permutation.begin(), permutation.end(), 1);
        rng.randshf(permutation);

        // コストを求める
        Cost cost = 0;
        Coordinate current = std::make_pair(0, 0);
        for (int i : permutation) {
            // 荷物 i がある座標
            Coordinate start = problem.start[i];
            // 荷物 i の目的地
            Coordinate goal = problem.goal[i];

            // 移動コストを計算
            cost += manhattan_distance(current, start);
            cost++;
            cost += manhattan_distance(start, goal) * 2;
            cost++;
            current = goal;
        }
        cost += manhattan_distance(current, std::make_pair(0, 0));

        // これまでの最良解よりも良ければ追加
        // if (solution.costs.empty() || cost < solution.costs.back()) {
        //     solution.costs.push_back(cost);
        //     Operations operations;
        //     current = std::make_pair(0, 0);
        //     for (int i : permutation) {
        //         // 荷物 i がある座標
        //         Coordinate start = problem.start[i];
        //         // 荷物 i の目的地
        //         Coordinate goal = problem.goal[i];

        //         Operations move = move_operation(i, current, start, goal);
        //         operations.insert(operations.end(), move.begin(), move.end());
        //         current = goal;
        //     }
        //     Operations move = get_route(current, std::make_pair(0, 0));
        //     operations.insert(operations.end(), move.begin(), move.end());
        //     solution.multi_operations.push_back(operations);
        // }

        if(cost < best_cost) {
            best_cost = cost;
            best_permutation = permutation;
        }
    }
    solution.costs.push_back(best_cost);
    Operations operations;
    Coordinate current = std::make_pair(0, 0);
    for (int i : best_permutation) {
        // 荷物 i がある座標
        Coordinate start = problem.start[i];
        // 荷物 i の目的地
        Coordinate goal = problem.goal[i];

        Operations move = move_operation(i, current, start, goal);
        operations.insert(operations.end(), move.begin(), move.end());
        current = goal;
    }
    Operations move = get_route(current, std::make_pair(0, 0));
    operations.insert(operations.end(), move.begin(), move.end());
    solution.multi_operations.push_back(operations);
    
    return solution;
}
