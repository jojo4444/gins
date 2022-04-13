//
// Created by jojo on 01.04.2022.
//

#ifndef GINS_ALGO_H
#define GINS_ALGO_H

#include "../pdata/data.h"
#include <chrono>

const int CHECK_MOD = 1e9 + 7;
const int BASE_MOD = 147;

class Algo {
public:
    Algo() = default;

    ~Algo() = default;

    [[nodiscard]] virtual std::tuple<ll, ll, err> Run(int points, int seed) const = 0;
};

std::tuple<ll, ll, ld, err> calculateAlgo(const Algo &a, int points, int seed);

void eytzinger(int k, int n, int &i, double *t, int *num, const double *a);

#endif //GINS_ALGO_H
