//
// Created by jojo on 21.03.2022.
//

#include "data.h"

PolygonData::PolygonData() {
    p = nullptr;
    n_ = 0;
}

PolygonData::~PolygonData() {
    delete[] p;
}

bool PolygonData::Create() {
    std::mt19937 eng(clock());

    n_ = (int) eng() % (MAX_POINT - 2) + 3;
    delete[] p;

    // https://www.cplusplus.com/doc/tutorial/dynamic/
    // for bad_alloc
    p = new(std::nothrow) Point<int, ll>[n_];
    if (p == nullptr) {
        return false;
    }

    Point<ld, ld> v(-CORD_MAX / 2. + 1, 0);
    Point shift(CORD_MAX / 2, CORD_MAX / 2);

    ld phi = 2 * PI / n_;
    for (int i = 0; i < n_; ++i) {
        p[i].x = (int) v.x;
        p[i].y = (int) v.y;
        p[i] = p[i] + shift;
        v = v.rotate(phi);
    }

    return Validation();
}

// no exception default
// http://www.cplusplus.com/reference/ios/ios/exceptions/
bool PolygonData::Load(const std::string &file) {
    std::ifstream in;
    in.open(file);
    // RAII -> destructor -> close()

    if (!in.is_open()) {
        return false;
    }

    delete[] p;

    in >> n_;

    // https://www.cplusplus.com/doc/tutorial/dynamic/
    // for bad_alloc
    p = new(std::nothrow) Point<int, ll>[n_];
    if (p == nullptr) {
        return false;
    }

    for (int i = 0; i < n_; ++i) {
        in >> p[i].x >> p[i].y;
    }
    return true;
}

// no exception default
// http://www.cplusplus.com/reference/ios/ios/exceptions/
bool PolygonData::Save(const std::string &file) const {
    std::ofstream out;
    out.open("../src/polygon/" + file);
    // RAII -> destructor -> close()

    if (!out.is_open()) {
        return false;
    }

    out << n_ << "\n";
    for (int i = 0; i < n_; ++i) {
        out << p[i].x << " " << p[i].y << "\n";
    }
    return true;
}

// only LeftRotate and [x, y] in [0; CORD_MAX]
bool PolygonData::Validation() const {
    if (n_ < 3) {
        return false;
    }

    bool flag = true;
    for (int i = 0; i < n_ && flag; ++i) {
        flag = (p[i].x >= 0 && p[i].y >= 0 && p[i].x <= CORD_MAX && p[i].y <= CORD_MAX);
    }
    for (int i = 1; i + 1 < n_ && flag; ++i) {
        flag = LeftRotate(p[i] - p[0], p[i + 1] - p[0]);
    }
    return flag;
}

int PolygonData::GetLen() const {
    return n_;
}

const Point<int, ll> *PolygonData::GetData() const {
    return p;
}