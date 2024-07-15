#include "StarrySkyTree.hpp"

#include <cassert>

StarrySkyTree::StarrySkyTree() : StarrySkyTree(0) {}

StarrySkyTree::StarrySkyTree(int _n) : n(1) {
    while (n < _n)
        n *= 2;
    dat.assign(2 * n, 0);
    bt.assign(n, 0);
}

void StarrySkyTree::build(const std::vector<int> &v) {
    for (int i = 0; i < (int)v.size(); i++) {
        dat[i + n] = v[i];
        add(i, v[i]);
    }
    for (int i = n - 1; i > 0; i--) {
        dat[i] = std::max(dat[i << 1], dat[i << 1 | 1]);
        dat[i << 1] -= dat[i];
        dat[i << 1 | 1] -= dat[i];
    }
}

void StarrySkyTree::set(int p, int x) {
    assert(0 <= p && p < n);
    add(p, n, x * 2);
    add(p, x * 2);
}

int StarrySkyTree::prodSum(int l, int r) const { return sum(r) - sum(l); }

bool StarrySkyTree::is_valid_cargo(int k) const { return dat[1] <= k; }

int StarrySkyTree::max() const { return dat[1]; }

void StarrySkyTree::fix(int idx) {
    dat[idx] = std::max(dat[idx << 1], dat[idx << 1 | 1]);
    dat[idx << 1] -= dat[idx];
    dat[idx << 1 | 1] -= dat[idx];
}

void StarrySkyTree::add(int l, int r, int x) {
    assert(l < r);
    l += n;
    r += n;
    while (l < r) {
        if (l & 1) {
            dat[l++] += x;
        }
        if (r & 1) {
            dat[--r] += x;
        }
        if ((l - 1) > 1) {
            fix((l - 1) >> 1);
        }
        if (r < (n << 1)) {
            fix(r >> 1);
        }
        l >>= 1;
        r >>= 1;
    }
    for (int i = l - 1; i > 1; i >>= 1) {
        fix(i);
    }
    assert(r < (n << 1));
    for (int i = r; i >= 1; i >>= 1) {
        fix(i);
    }
}

void StarrySkyTree::add(int idx, int x) {
    assert(0 <= idx && idx < n);
    for (idx++; idx <= n; idx += idx & -idx) {
        bt[idx - 1] += x;
    }
}

int StarrySkyTree::sum(int idx) const {
    assert(0 <= idx && idx <= n);
    uint8_t res = 0;
    for (; idx > 0; idx -= idx & -idx) {
        res += bt[idx - 1];
    }
    return res;
}