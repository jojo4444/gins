//
// Created by jojo on 01.04.2022.
//

#ifndef GINS_ALGO_H
#define GINS_ALGO_H

#include "../pdata/data.h"
#include <chrono>

// __builtin_ funcs:
// https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html

const int CHECK_MOD = 1e9 + 7;
const int BASE_MOD = 147;

class Algo {
public:
    Algo() = default;

    ~Algo() = default;

    [[nodiscard]] virtual std::tuple<ll, ll, err> Run(int points, int seed) const = 0;
};

/// checksum, inside, time, error
std::tuple<ll, ll, ld, err> calculateAlgo(const Algo &a, int points, int seed);

template<typename T>
void eytzinger(int k, int n, int &i, T *t, int *num, const T *a) {
    if (k <= n) {
        eytzinger(2 * k, n, i, t, num, a);
        num[k] = i;
        t[k] = a[i++];
        eytzinger(2 * k + 1, n, i, t, num, a);
    }
}

#endif //GINS_ALGO_H
