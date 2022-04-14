//
// Created by jojo on 14.04.2022.
//

#ifndef GINS_HARDPLUS_H
#define GINS_HARDPLUS_H

#pragma GCC target("avx2")

#include <x86intrin.h>
#include <thread>
#include <sys/mman.h>
#include "../algo.h"

/// 8 * 8b = 64b (cache line size)
const int B = 8;

const double INF_TAN = 1e18;

class HardPlus : public Algo {
public:
    HardPlus() = default;

    ~HardPlus() = default;

    [[nodiscard]] std::tuple<ll, ll, err> Run(int points, int seed) const override;
};

int go(int k, int i);

void build(int k, int &t, int n, int blocks, double *__restrict__ btree, int *__restrict__ num,
           const double *__restrict__ a);

int cmp(const __m256d &x, const double *ptr);

#endif //GINS_HARDPLUS_H
