//
// Created by jojo on 11.04.2022.
//

#ifndef GINS_MEDIUM_H
#define GINS_MEDIUM_H

#include "../algo.h"
#include <thread>

class Medium : public Algo {
public:
    Medium() = default;

    ~Medium() = default;

    [[nodiscard]] std::tuple<ll, ll, err> Run(int points, int seed) const override;
};

#endif //GINS_MEDIUM_H
