#include "solution.hpp"
#include "common.hpp"

void print_solution(const Solution &solution) {
    for (int i = 0; i < solution.multi_operations.size(); i++) {
        for (int j = 0; j < solution.multi_operations[i].size(); j++) {
            std::cout << solution.multi_operations[i][j]
                      << " \n"[j == solution.multi_operations[i].size() - 1];
        }
        log_message(LogLevel::INFO,
                    "Cost: " + std::to_string(solution.costs[i]));
    }
}