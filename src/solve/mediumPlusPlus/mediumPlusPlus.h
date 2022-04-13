//
// Created by jojo on 12.04.2022.
//

#ifndef GINS_MEDIUMPLUSPLUS_H
#define GINS_MEDIUMPLUSPLUS_H

#include "../algo.h"
#include <thread>

class MediumPlusPlus : public Algo {
public:
    MediumPlusPlus() = default;

    ~MediumPlusPlus() = default;

    [[nodiscard]] std::tuple<ll, ll, err> Run(int points, int seed) const override;
};

#endif //GINS_MEDIUMPLUSPLUS_H
