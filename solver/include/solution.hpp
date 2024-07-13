#pragma once

#include "common.hpp"

#include <string>
#include <vector>

struct Solution {
    std::vector<Operations> multi_operations;
    std::vector<Cost> costs;
};

void print_solution(const Solution &solution);