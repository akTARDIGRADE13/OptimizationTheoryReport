#pragma once

#include "solver_base.hpp"

struct RandomRouteSolver : public SolverBase {
  public:
    // Problemを受け取りSolutionを返すsolve関数の実装
    Solution solve(const Problem &problem) override;
};
