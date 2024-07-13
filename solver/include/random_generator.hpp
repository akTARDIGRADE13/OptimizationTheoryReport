#pragma once

#include <cassert>
#include <cstdint>
#include <vector>
#include <algorithm>
#include <mutex>

struct RandomGenerator {
public:
    static RandomGenerator& getInstance();

    uint64_t rng();
    int64_t randint(int64_t l, int64_t r);
    double rnd();

    template <typename T>
    void randshf(std::vector<T>& v);

private:
    RandomGenerator();
    ~RandomGenerator() = default;

    RandomGenerator(const RandomGenerator&) = delete;
    RandomGenerator& operator=(const RandomGenerator&) = delete;

    uint64_t rx, ry, rz, rw;
    std::mutex mtx;
};

template <typename T>
void RandomGenerator::randshf(std::vector<T>& v) {
    int n = v.size();
    for (int i = 1; i < n; i++) {
        std::swap(v[i], v[randint(0, i + 1)]);
    }
}