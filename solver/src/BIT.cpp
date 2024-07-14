#include "BIT.hpp"

#include <cassert>

BIT::BIT() : BIT(0) {}
BIT::BIT(int _n) : n(_n), data(_n, 0) {}

void BIT::add(int p, uint16_t x) {
    assert(0 <= p && p < n);
    for (p++; p <= n; p += p & -p) {
        data[p - 1] += x;
    }
}

int BIT::sum(int p) const {
    assert(0 <= p && p <= n);
    uint16_t res = 0;
    for (; p > 0; p -= p & -p) {
        res += data[p - 1];
    }
    return res;
}

int BIT::sum(int l, int r) const {
    assert(0 <= l && l <= r && r <= n);
    return sum(r) - sum(l);
}