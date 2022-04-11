//
// Created by jojo on 03.04.2022.
//

#ifndef GINS_LOW_H
#define GINS_LOW_H

#include "../algo.h"

class Low : public Algo {
public:
    Low() = default;

    ~Low() = default;

    [[nodiscard]] std::tuple<ll, ll, err> Run(int points, int seed) const override;
};


#endif //GINS_LOW_H
