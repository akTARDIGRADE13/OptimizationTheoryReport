#pragma once

#include "solver_base.hpp"
#include "problem.hpp"
#include "solution.hpp"

struct SABase : public SolverBase {
    virtual Solution solve(const Problem &problem) = 0;
    virtual ~SABase() = default;

    double acceptanceProb(Cost currentCost, Cost newCost, double temp);
    double updateTemp(double startTemp, double endTemp, double elapsed,
                      double duration);
};