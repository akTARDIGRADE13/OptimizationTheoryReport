#pragma once

#include "SA_base.hpp"

struct SimulatedAnnealingSolver : public SABase {
  public:
    // Problemを受け取りSolutionを返すsolve関数の実装
    Solution solve(const Problem &problem) override;
};
