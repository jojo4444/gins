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

const int MAX_POINT = 1e5;

class PolygonData {
public:
    PolygonData();

    ~PolygonData();

    bool Create();

    bool Load(const std::string& file);

    bool Save(const std::string& file) const;

    bool Validation() const;

    int GetLen() const;

    const Point<int, ll> *GetData() const;

private:
    int n_;
    Point<int, ll> *p;
};

#endif //GINS_DATA_H
