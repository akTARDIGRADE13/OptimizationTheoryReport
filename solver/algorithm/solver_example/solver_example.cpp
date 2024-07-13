#include "common.hpp"
#include "solver_example.hpp"
#include "validator.hpp"

#include <string>
#include <cassert>

Solution SolverExample::solve(const Problem& problem) {
    Solution solution;
    // 具体的な解決アルゴリズムを実装
    // ここにアルゴリズムを記述

    // 仮の実装例
    solution.costs.push_back(1);
    solution.multi_operations.push_back(Operations{});
    solution.multi_operations[0].push_back("R");

    // とりあえず動作確認したいだけなら以下はコメントアウトしてよい
    if (validate_solution(problem, solution.multi_operations[0]) == -1) {
        log_message(LogLevel::ERROR, "Invalid solution");
        assert(false);    
    }

    return solution;
}
