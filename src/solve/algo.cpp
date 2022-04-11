//
// Created by jojo on 01.04.2022.
//

#include "algo.h"

std::tuple<ll, ld, err> calcTime(const Algo& a, bool check) {
    auto t_start = std::chrono::high_resolution_clock::now();

    auto [checksum, err] = a.Run(check);

    auto t_end = std::chrono::high_resolution_clock::now();

    ld tm = std::chrono::duration_cast<std::chrono::nanoseconds>(t_end-t_start).count();
    tm /= 1e9;

    return std::make_tuple(checksum, tm, err);
}