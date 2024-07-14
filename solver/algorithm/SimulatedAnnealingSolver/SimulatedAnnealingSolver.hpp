#pragma once

#include "solver_base.hpp"

struct SimulatedAnnealingSolver : public SolverBase {
  public:
    // Problemを受け取りSolutionを返すsolve関数の実装
    Solution solve(const Problem &problem) override;

  private:
    double acceptanceProb(Cost currentCost, Cost newCost, double temp);
    double updateTemp(double startTemp, double endTemp, double elapsed,
                      double duration);
};
