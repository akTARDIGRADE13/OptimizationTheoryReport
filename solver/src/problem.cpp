#include "problem.hpp"
#include "common.hpp"

#include <fstream>
#include <sstream>

Problem load_problem(const std::string &filename) {
    Problem problem;
    auto lines = read_file_lines(filename);

    if (!lines.empty()) {
        std::istringstream iss(lines[0]);
        iss >> problem.N >> problem.K;
        problem.grid.resize(problem.N, std::vector<int>(problem.N));

        for (int i = 0; i < problem.N; ++i) {
            std::istringstream row_stream(lines[i + 1]);
            for (int j = 0; j < problem.N; ++j) {
                row_stream >> problem.grid[i][j];
            }
        }
    }

    return problem;
}