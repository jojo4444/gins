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

    [[nodiscard]] virtual std::tuple<ll, err> Run(bool check) const = 0;
};

std::tuple<ll, ld, err> calcTime(const Algo& a, bool check);

#endif //GINS_ALGO_H
