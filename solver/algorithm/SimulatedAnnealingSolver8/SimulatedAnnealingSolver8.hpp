#pragma once

#include "BIT.hpp"
#include "StarrySkyTree.hpp"
#include "SA_base.hpp"
#include "common.hpp"

struct SimulatedAnnealingSolver8 : public SABase {
  public:
    // Problemを受け取りSolutionを返すsolve関数の実装
    Solution solve(const Problem &problem) override;

  private:
    std::pair<Solution, Coordinate> solve(const Problem &problem, const std::vector<int> &candidate, Coordinate &robot, bool LAST);

    inline Coordinate getPoint(const std::vector<int> &perm, const Problem &problem,
                        int index);

    inline void updateDistance(int index, const std::vector<int> &perm,
                        const Problem &problem, BIT &bt, int M, Coordinate &robot, bool LAST);

    inline Cost calculateNewCost(int l, int r, const std::vector<int> &prem,
                          const Problem &problem, BIT &bt,
                          StarrySkyTree &sst, Cost currentCost);

    inline Cost calculateCostAfterSwapBack(int l, int r, const std::vector<int> &perm,
                                    const Problem &problem, BIT &bt,
                                    StarrySkyTree &sst,
                                    Cost currentCost);
};