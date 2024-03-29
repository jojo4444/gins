//
// Created by jojo on 11.04.2022.
//

#ifndef GINS_LOWPLUS_H
#define GINS_LOWPLUS_H

#include "../algo.h"
#include <thread>

class LowPlus : public Algo {
public:
    LowPlus() = default;

    ~LowPlus() = default;

    [[nodiscard]] std::tuple<ll, ll, err> Run(int points, int seed) const override;
};


#endif //GINS_LOWPLUS_H
