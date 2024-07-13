#pragma once

#include "common.hpp"

#include <string>
#include <vector>

struct Problem {
    int N, K;
    Grid grid;
};

Problem load_problem(const std::string &filename);