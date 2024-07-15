#pragma once

#include <cstdint>
#include <vector>

struct StarrySkyTree {
  public:
    StarrySkyTree();
    StarrySkyTree(int _n);

    void build(const std::vector<int> &v);

    void set(int p, int x);

    int prodSum(int l, int r) const;

    bool is_valid_cargo(int k) const;

    int max() const;

  private:
    int n;
    std::vector<int8_t> dat;
    std::vector<int8_t> bt;

    inline void fix(int idx);

    inline void add(int l, int r, int x);

    inline void add(int idx, int x);

    inline int sum(int idx) const;
};