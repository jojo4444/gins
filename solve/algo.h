//
// Created by jojo on 01.04.2022.
//

#ifndef GINS_ALGO_H
#define GINS_ALGO_H

#include "../pdata/data.h"

class Algo {
public:
    Algo() = default;

    ~Algo() = default;

    [[nodiscard]] virtual ll Test(const PolygonData& polygon, const PointData& q) const = 0;
};


#endif //GINS_ALGO_H
