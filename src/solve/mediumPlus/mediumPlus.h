//
// Created by jojo on 11.04.2022.
//

#ifndef GINS_MEDIUMPLUS_H
#define GINS_MEDIUMPLUS_H

#include "../algo.h"
#include <thread>

class MediumPlus : public Algo {
public:
    MediumPlus() = default;

    ~MediumPlus() = default;

    [[nodiscard]] std::tuple<ll, ll, err> Run(int points, int seed) const override;
};

#endif //GINS_MEDIUMPLUS_H
