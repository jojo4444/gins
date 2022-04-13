//
// Created by jojo on 01.04.2022.
//

#include "algo.h"

std::tuple<ll, ll, ld, err> calculateAlgo(const Algo &a, int points, int seed) {
    auto t_start = std::chrono::high_resolution_clock::now();

    auto[checksum, inside, err] = a.Run(points, seed);

    auto t_end = std::chrono::high_resolution_clock::now();

    ld tm = std::chrono::duration_cast<std::chrono::nanoseconds>(t_end - t_start).count();
    tm /= 1e9;

    return std::make_tuple(checksum, inside, tm, err);
}