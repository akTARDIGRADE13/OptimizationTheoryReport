#include "random_generator.hpp"

RandomGenerator& RandomGenerator::getInstance() {
    static RandomGenerator instance;
    return instance;
}

RandomGenerator::RandomGenerator()
    : rx(123456789), ry(362436069), rz(521288629), rw(88675123) {}

uint64_t RandomGenerator::rng() {
    std::lock_guard<std::mutex> lock(mtx);
    uint64_t rt = (rx ^ (rx << 11));
    rx = ry;
    ry = rz;
    rz = rw;
    return (rw = (rw ^ (rw >> 19)) ^ (rt ^ (rt >> 8)));
}

int64_t RandomGenerator::randint(int64_t l, int64_t r) {
    assert(l < r);
    return l + rng() % (r - l);
}

double RandomGenerator::rnd() {
    return rng() * 5.42101086242752217004e-20;
}