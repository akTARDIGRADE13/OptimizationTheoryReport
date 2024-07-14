#pragma once

#include "SA_base.hpp"
#include "common.hpp"
#include "BIT.hpp"

struct SimulatedAnnealingSolver2 : public SABase {
  public:
    // Problemを受け取りSolutionを返すsolve関数の実装
    Solution solve(const Problem &problem) override;

  private:
    Coordinate getPoint(const std::vector<int> &perm, const Problem &problem,
                        int index);
    
    void updateDistance(int index, const std::vector<int> &perm,
                        const Problem &problem, BIT &bt, int M);
};
