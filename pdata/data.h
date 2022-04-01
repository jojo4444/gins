//
// Created by jojo on 21.03.2022.
//

#ifndef GINS_DATA_H
#define GINS_DATA_H

#include <fstream>
#include <iostream>
#include <string>
#include <new>
#include <random>

#include "../primitives/point.h"
#include "../errors/errors.h"

using err = errors::error;

const int MAX_POINT = 1 << 16;
const int CORD_MAX = 2e9;

class PolygonData {
public:
    PolygonData();

    ~PolygonData();

    err Create(int cnt = MAX_POINT);

    err Load(const std::string& file);

    err Save(const std::string& file) const;

    err Validation() const;

    [[nodiscard]] int GetLen() const;

    [[nodiscard]] const Point<int, ll> *GetData() const;

private:
    int n_;
    Point<int, ll> *p;
};

#endif //GINS_DATA_H
