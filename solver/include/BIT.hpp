#pragma once

#include <cstdint>
#include <vector>

struct BIT {
  public:
    BIT();
    explicit BIT(int _n);

    void add(int p, uint16_t x);

    int sum(int p) const;

    int sum(int l, int r) const;

  private:
    int n;
    std::vector<uint16_t> data;
};