#pragma once

#include "problem.hpp"
#include "solution.hpp"

struct SolverBase {
    virtual Solution solve(const Problem &problem) = 0;
    virtual ~SolverBase() = default;
};