#pragma once

#include "common.hpp"

#include <string>
#include <vector>

struct Problem {
    int N, K;
    Grid grid;
    // 荷物 i がある座標
    std::vector<Coordinate> start;
    // 荷物 i の目的地
    std::vector<Coordinate> goal;
};

Problem load_problem(const std::string &filename);