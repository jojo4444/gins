//
// Created by jojo on 21.03.2022.
//

#ifndef GINS_DATA_H
#define GINS_DATA_H

#include <tuple>
#include <fstream>
#include <iostream>
#include <string>
#include <new>
#include <random>

#include "../primitives/point.h"
#include "../errors/errors.h"

using err = errors::error;

const int MAX_POINT = 1 << 24;
const int CORD_MAX = 1 << 30;

class PolygonData {
public:
    PolygonData();

    ~PolygonData();

    err Create(int cnt = MAX_POINT);

    err Load(const std::string &file);

    err Save(const std::string &file) const;

    err Validation() const;

    [[nodiscard]] int GetLen() const;

    [[nodiscard]] const Point<int, ll> *GetData() const;

private:
    int n_;
    Point<int, ll> *p;
};

const int CNT_BATCH = 6; /// threads

class PointData {
public:
    explicit PointData(int points = 4, int seed = 4);

    std::tuple<Point<>, bool> GetPt(int id);

private:
    /// https://en.wikipedia.org/wiki/Mersenne_Twister
    std::mt19937 rnd[CNT_BATCH];
    int cnt[CNT_BATCH];
};

#endif //GINS_DATA_H
