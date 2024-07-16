#pragma once

#include "SA_base.hpp"
#include "common.hpp"

struct SimulatedAnnealingSolver7 : public SABase {
  public:
    // Problemを受け取りSolutionを返すsolve関数の実装
    Solution solve(const Problem &problem) override;

  private:
    inline Coordinate getPoint(const std::vector<int> &perm, const Problem &problem,
                        int index);

    inline Cost calcCost(const std::vector<int> &perm, const Problem &problem, int M,
                  std::vector<Cost> &costs, std::vector<int> &cargos,
                  int start);
};
