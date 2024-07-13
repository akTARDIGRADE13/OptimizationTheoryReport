#include "validator.hpp"
#include "common.hpp"

#include <algorithm>
#include <vector>

// validならコストを返す、invalidなら-1を返す
Cost validate_solution(const Problem &problem, const Operations &operations) {
    // テスト用
    // return 0;

    int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};
    int x = 0, y = 0;
    std::vector<int> cargo(((problem.N * problem.N - 1) >> 1) + 1, 0);
    int cnt = 0;
    Cost cost = 0;
    auto is_valid_range = [&](int x, int y) {
        return 0 <= x && x < problem.N && 0 <= y && y < problem.N;
    };

    Grid grid = problem.grid;

    for (auto &op : operations) {
        ++cost;
        if (op == "R") {
            x += dx[0];
            y += dy[0];
            cost += cnt;
            if (cnt > problem.K) {
                return -1;
            }
        } else if (op == "D") {
            x += dx[1];
            y += dy[1];
            cost += cnt;
            if (cnt > problem.K) {
                return -1;
            }
        } else if (op == "L") {
            x += dx[2];
            y += dy[2];
            cost += cnt;
            if (cnt > problem.K) {
                return -1;
            }
        } else if (op == "U") {
            x += dx[3];
            y += dy[3];
            cost += cnt;
            if (cnt > problem.K) {
                return -1;
            }
        } else if (op[0] == '+') {
            int num = std::stoi(op.substr(1));
            if (cargo[num]) {
                return -1;
            }
            if (grid[x][y] != num) {
                return -1;
            }
            grid[x][y] = std::min(problem.grid[x][y], 0);
            cargo[num] = 1;
            ++cnt;
        } else if (op[0] == '-') {
            int num = std::stoi(op.substr(1));
            if (!cargo[num]) {
                return -1;
            }
            if (grid[x][y] > 0) {
                return -1;
            }
            grid[x][y] = num;
            cargo[num] = 0;
            --cnt;
        } else {
            return -1;
        }
        if (!is_valid_range(x, y)) {
            return -1;
        }
    }
    if (std::any_of(cargo.begin(), cargo.end(), [](int x) { return x != 0; })) {
        return -1;
    }
    for (int i = 0; i < problem.N; ++i) {
        for (int j = 0; j < problem.N; ++j) {
            if (grid[i][j] < 0) {
                return -1;
            }
            if (grid[i][j] > 0 && grid[i][j] != -problem.grid[i][j]) {
                return -1;
            }
        }
    }
    return cost;
}