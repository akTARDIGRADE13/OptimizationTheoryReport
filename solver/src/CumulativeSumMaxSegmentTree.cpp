#include "CumulativeSumMaxSegmentTree.hpp"

CumulativeSumMaxSegmentTree::CumulativeSumMaxSegmentTree()
    : CumulativeSumMaxSegmentTree(0) {}

CumulativeSumMaxSegmentTree::CumulativeSumMaxSegmentTree(int _n)
    : n(_n), data(n << 1, 0) {}

CumulativeSumMaxSegmentTree::CumulativeSumMaxSegmentTree(
    const std::vector<int> &v)
    : n(v.size()), data(n << 1, 0) {
    build(v);
}

void CumulativeSumMaxSegmentTree::build(const std::vector<int> &v) {
    assert(n == v.size());
    for (int i = 0; i < n; i++) {
        data[i + n] = pack(v[i], v[i]);
    }
    for (int i = n - 1; i >= 1; i--) {
        data[i] = func(data[i << 1], data[i << 1 | 1]);
    }
}

void CumulativeSumMaxSegmentTree::set(int p, int x) {
    assert(0 <= p && p < n);
    p += n;
    data[p] = pack(x, x);
    while (p >>= 1) {
        data[p] = func(data[p << 1], data[p << 1 | 1]);
    }
}

std::pair<int, int> CumulativeSumMaxSegmentTree::get(int p) const {
    assert(0 <= p && p < n);
    p += n;
    return unpack(data[p]);
}

std::pair<int, int> CumulativeSumMaxSegmentTree::prod(int l, int r) const {
    assert(0 <= l && l <= r && r <= n);
    int sml = 0, smr = 0;
    l += n;
    r += n;

    while (l < r) {
        if (l & 1) {
            sml = func(sml, data[l++]);
        }
        if (r & 1) {
            smr = func(data[--r], smr);
        }
        l >>= 1;
        r >>= 1;
    }
    int res = func(sml, smr);
    return unpack(res);
}

int CumulativeSumMaxSegmentTree::prodSum(int l, int r) const {
    assert(0 <= l && l <= r && r <= n);
    int sml = 0, smr = 0;
    l += n;
    r += n;

    while (l < r) {
        if (l & 1) {
            sml = func(sml, data[l++]);
        }
        if (r & 1) {
            smr = func(data[--r], smr);
        }
        l >>= 1;
        r >>= 1;
    }
    int res = func(sml, smr);
    return static_cast<int16_t>(res & MASK);
}

std::pair<int, int> CumulativeSumMaxSegmentTree::all_prod() const {
    return unpack(data[1]);
}

bool CumulativeSumMaxSegmentTree::is_valid_cargo(int k) const {
    int16_t maxSum = static_cast<int16_t>(data[1] >> BIT_LENGTH);
    return maxSum <= k;
}

int CumulativeSumMaxSegmentTree::func(int a, int b) const {
    int sumA = static_cast<int16_t>(a & MASK);
    int sumB = static_cast<int16_t>(b & MASK);
    int maxSumA = static_cast<int16_t>(a >> BIT_LENGTH);
    int maxSumB = static_cast<int16_t>(b >> BIT_LENGTH);

    int sum = sumA + sumB;
    int maxSum = std::max(maxSumA, maxSumB + sumA);

    return pack(maxSum, sum);
}

int CumulativeSumMaxSegmentTree::pack(int16_t maxSum, int16_t sum) const {
    return (static_cast<int>(maxSum) << BIT_LENGTH) |
           (static_cast<int>(sum) & MASK);
}

std::pair<int, int> CumulativeSumMaxSegmentTree::unpack(int packed) const {
    int16_t maxSum = static_cast<int16_t>(packed >> BIT_LENGTH);
    int16_t sum = static_cast<int16_t>(packed & MASK);
    return {maxSum, sum};
}