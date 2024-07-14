#pragma once

#include <algorithm>
#include <cassert>
#include <functional>
#include <vector>

struct CumulativeSumMaxSegmentTree {
  public:
    CumulativeSumMaxSegmentTree();
    explicit CumulativeSumMaxSegmentTree(int _n);
    explicit CumulativeSumMaxSegmentTree(const std::vector<int> &v);

    void build(const std::vector<int> &v);

    void set(int p, int x);

    std::pair<int, int> get(int p) const;

    std::pair<int, int> prod(int l, int r) const;

    int prodSum(int l, int r) const;

    std::pair<int, int> all_prod() const;

    bool is_valid_cargo(int k) const;

  private:
    int n;
    std::vector<int> data;
    const int BIT_LENGTH = 16;
    const int16_t MASK = (1 << BIT_LENGTH) - 1;

    int func(int a, int b) const;

    int pack(int16_t maxSum, int16_t sum) const;

    std::pair<int, int> unpack(int x) const;
};