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

err PolygonData::Create(int cnt) {
    if (cnt < 3 || cnt > MAX_POINT) {
        return errors::NewErrorf("incorrect cnt points, want [3, %d], have %d", MAX_POINT, cnt);
    }

    n_ = cnt;
    delete[] p;

    /// https://www.cplusplus.com/doc/tutorial/dynamic/
    /// for bad_alloc
    p = new(std::nothrow) Point<int, ll>[n_];
    if (p == nullptr) {
        return errors::NewError("bad alloc (points)");
    }


    /**
     * circle generation (precision: MAX_POINT <= 2^17)
    */

    Point<ld, ld> v(-CORD_MAX, 0);
    for (int i = 0; i < n_; ++i) {
        Point<ld, ld> rot = v.rotate(i * 2 * PI / n_);
        p[i].x = (int)rot.x;
        p[i].y = (int)rot.y;
    }

    return Validation();
}

/// no exception default
/// http://www.cplusplus.com/reference/ios/ios/exceptions/
err PolygonData::Load(const std::string &file) {
    std::ifstream in;
    in.open("../src/polygon/" + file);
    // RAII -> destructor -> close()

    if (!in.is_open()) {
        return errors::NewError("file not open");
    }

    delete[] p;

    in >> n_;

    // https://www.cplusplus.com/doc/tutorial/dynamic/
    // for bad_alloc
    p = new(std::nothrow) Point<int, ll>[n_];
    if (p == nullptr) {
        return errors::NewError("bad alloc (points)");
    }

    for (int i = 0; i < n_; ++i) {
        in >> p[i].x >> p[i].y;
    }
    return Validation();
}

/// no exception default
/// http://www.cplusplus.com/reference/ios/ios/exceptions/
err PolygonData::Save(const std::string &file) const {
    std::ofstream out;
    out.open("../src/polygon/" + file);
    // RAII -> destructor -> close()

    if (!out.is_open()) {
        return errors::NewError("file not open");
    }

    out << n_ << "\n";
    for (int i = 0; i < n_; ++i) {
        out << p[i].x << " " << p[i].y << "\n";
    }
    return errors::NIL;
}

/// only LeftRotate
/// p[0] is left-down
/// [x, y] in [-CORD_MAX; CORD_MAX]
err PolygonData::Validation() const {
    using namespace errors;

    if (n_ < 3 || n_ > MAX_POINT) {
        return NewErrorf("incorrect cnt points, want [3, %d], have %d", MAX_POINT, n_);
    }

    int xm = CORD_MAX;
    int ym = CORD_MAX;

    for (int i = 0; i < n_; ++i) {
        if (std::abs(p[i].x) > CORD_MAX || std::abs(p[i].y) > CORD_MAX) {
            return NewErrorf("incorrect point, want cord in [%d, %d], have x = %d, y = %d", -CORD_MAX, CORD_MAX, p[i].x, p[i].y);
        }
        if (p[i].x < xm || (p[i].x == xm && p[i].y < ym)) {
            xm = p[i].x;
            ym = p[i].y;
        }
    }

    if (p[0] != Point(xm, ym)) {
        return NewErrorf("start point is not first, p[0] = (%d, %d)", p[0].x, p[0].y);
    }

    for (int i = 0; i < n_; ++i) {
        int j = (i + 1) % n_;
        int k = (i + 2) % n_;
        if (!LeftRotate(p[j] - p[i], p[k] - p[j])) {
            return NewErrorf("polygon non-convex: p[%d], p[%d], p[%d] is (%d, %d), (%d, %d), (%d, %d)",
                             i, j, k, p[i].x, p[i].y, p[j].x, p[j].y, p[k].x, p[k].y);
        }
    }

    return NIL;
}

int PolygonData::GetLen() const {
    return n_;
}

const Point<int, ll> *PolygonData::GetData() const {
    return p;
}