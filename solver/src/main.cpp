#include "RandomRouteSolver.hpp"
#include "SimulatedAnnealingSolver.hpp"
#include "SimulatedAnnealingSolver2.hpp"
#include "SimulatedAnnealingSolver3.hpp"
#include "SimulatedAnnealingSolver4.hpp"
#include "SimulatedAnnealingSolver5.hpp"
#include "common.hpp"
#include "problem.hpp"
#include "solution.hpp"
#include "solver_example.hpp"

#include <iostream>
#include <string>

void print_usage() {
    std::cout << "Usage: DeliveryRobot <solver> <input_file_path>" << std::endl;
    std::cout << "Available solvers: RR SA SA2 SA3 SA4 SA5 example" << std::endl;
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

    // 目的マスまでのマンハッタン距離の総和を計算
    Cost total_manhattan_distance = 0;
    std::vector<Coordinate> goal_positions(problem.N * problem.N);
    for (int i = 0; i < problem.N; i++) {
        for (int j = 0; j < problem.N; j++) {
            if (problem.grid[i][j] < 0) {
                goal_positions[-problem.grid[i][j]] = {i, j};
            }
        }
    }
    for (int i = 0; i < problem.N; i++) {
        for (int j = 0; j < problem.N; j++) {
            if (problem.grid[i][j] > 0) {
                total_manhattan_distance += manhattan_distance(
                    {i, j}, goal_positions[problem.grid[i][j]]);
            }
        }
    }

    log_message(LogLevel::INFO, "Total manhattan distance: " +
                                    std::to_string(total_manhattan_distance));
    // 最適値の下界
    log_message(LogLevel::INFO,
                "Lower bound: " +
                    std::to_string(total_manhattan_distance +
                                   total_manhattan_distance / problem.K +
                                   problem.N * (problem.N - 1)));

    if (solver_name == "RR") {
        RandomRouteSolver solver;
        Solution solution = solver.solve(problem);
        print_solution(solution);
    } else if (solver_name == "SA") {
        SimulatedAnnealingSolver solver;
        Solution solution = solver.solve(problem);
        print_solution(solution);
    } else if (solver_name == "SA2") {
        SimulatedAnnealingSolver2 solver;
        Solution solution = solver.solve(problem);
        print_solution(solution);
    } else if (solver_name == "SA3") {
        SimulatedAnnealingSolver3 solver;
        Solution solution = solver.solve(problem);
        print_solution(solution);
    } else if (solver_name == "SA4") {
        SimulatedAnnealingSolver4 solver;
        Solution solution = solver.solve(problem);
        print_solution(solution);
    } else if(solver_name == "SA5") {
        SimulatedAnnealingSolver5 solver;
        Solution solution = solver.solve(problem);
        print_solution(solution);

    }else if (solver_name == "example") {
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