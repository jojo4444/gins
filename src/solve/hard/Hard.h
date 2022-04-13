//
// Created by jojo on 13.04.2022.
//

#ifndef GINS_HARD_H
#define GINS_HARD_H

#include "../algo.h"
#include <thread>

class Hard : public Algo {
public:
    Hard() = default;

    ~Hard() = default;

    [[nodiscard]] std::tuple<ll, ll, err> Run(int points, int seed) const override;
};

#endif //GINS_HARD_H
