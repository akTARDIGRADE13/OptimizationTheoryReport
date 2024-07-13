#include "common.hpp"
#include "problem.hpp"
#include "solution.hpp"
#include "solver_example.hpp"

#include <iostream>
#include <string>

void print_usage() {
    std::cout << "Usage: DeliveryRobot <solver> <input_file>" << std::endl;
    std::cout << "Available solvers: solver1" << std::endl;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        print_usage();
        return 1;
    }

    std::string solver_name = argv[1];
    std::string input_file = argv[2];

    Problem problem = load_problem(input_file);

    // std::cout << problem.N << " " << problem.K << std::endl;
    // for (const auto &row : problem.grid) {
    //     for (int cell : row) {
    //         std::cout << cell << " ";
    //     }
    //     std::cout << std::endl;
    // }

    if (solver_name == "example") {
        SolverExample solver;
        Solution solution = solver.solve(problem);
        print_solution(solution);
    } else {
        log_message(LogLevel::ERROR, "Unknown solver: " + solver_name);
        print_usage();
        return 1;
    }

    return 0;
}