//
// Created by jojo on 21.03.2022.
//

#ifndef GINS_POINT_H
#define GINS_POINT_H

#include <cmath>
#include <type_traits>

using ll = long long;
using ld = long double;

const ld PI = M_PIl;
/**
PI = acos(-1)
PI = 4 * atan(1)

1. Critical point
2. https://en.wikipedia.org/wiki/Taylor_series
3. https://en.wikipedia.org/wiki/Remez_algorithm

fast cos(x):
cos(x) = 2 * cos^2(x * 0.5) - 1
x/2 <= pi/2 ~ 3.14/2 = 1.57
---> (x' < 1) ---> (fast series)

T: type coordinate
R: type result in operations

p1 * p2 - vector product
p1 % p2 - scalar product

eps for check p1 == p2
---- if R is int or ll -> eps ignored (using is_same)

https://gcc.gnu.org/git.html
gcc_source/libquadmath/math/acosq.c
*/

const ld EPS = 1e-9;
const int CORD_MAX = 1e9;

template<typename T = int, typename R = ll>
struct Point {
    T x, y;

    Point();

    Point(T x_, T y_);

    R len2() const;

    ld len() const;

    // rotate pi/2 to left
    Point<T, R> ort() const;

    Point<T, R> rotate(ld angle) const;

    Point<T, R> operator+(const Point<T, R> &P) const;

    Point<T, R> operator-(const Point<T, R> &P) const;

    Point<T, R> operator*(R t) const;

    Point<T, R> operator/(R t) const;

    bool operator==(const Point<T, R> &P) const;

    bool operator!=(const Point<T, R> &P) const;

    Point<T, R>& operator= (const Point<T, R> &P);

    // vector product
    R operator*(const Point &P) const;

    // scalar product
    R operator%(const Point &P) const;
};

template<typename T, typename R>
Point<T, R>::Point() {
    x = y = 0;
}

template<typename T, typename R>
Point<T, R>::Point(T x_, T y_) {
    x = x_;
    y = y_;
}

template<typename T, typename R>
R Point<T, R>::len2() const {
    return *this % *this;
}

template<typename T, typename R>
ld Point<T, R>::len() const {
    return (R) sqrt(*this % *this);
}

template<typename T, typename R>
Point<T, R> Point<T, R>::ort() const {
    return Point<T, R>(-y, x);
}

template<typename T, typename R>
Point<T, R> Point<T, R>::rotate(ld angle) const {
    return *this * cosl(angle) + ort() * sinl(angle);
}

template<typename T, typename R>
Point<T, R> Point<T, R>::operator+(const Point<T, R> &P) const {
    return Point<T, R>(x + P.x, y + P.y);
}

template<typename T, typename R>
Point<T, R> Point<T, R>::operator-(const Point<T, R> &P) const {
    return Point<T, R>(x - P.x, y - P.y);
}

template<typename T, typename R>
Point<T, R> Point<T, R>::operator*(R t) const {
    return Point<T, R>(x * t, y * t);
}

template<typename T, typename R>
Point<T, R> Point<T, R>::operator/(R t) const {
    return *this * (R) (1. / t);
}

template<typename T, typename R>
R Point<T, R>::operator*(const Point<T, R> &P) const {
    return x * P.y - y * P.x;
}

template<typename T, typename R>
bool Point<T, R>::operator==(const Point<T, R> &P) const {
    if (std::is_same<T, int>() || std::is_same<T, ll>()) {
        return x == P.x && y == P.y;
    }
    return abs(x - P.x) < EPS && abs(y - P.y) < EPS;
}

template<typename T, typename R>
bool Point<T, R>::operator!=(const Point<T, R> &P) const {
    if (std::is_same<T, int>() || std::is_same<T, ll>()) {
        return x != P.x || y != P.y;
    }
    return abs(x - P.x) >= EPS || abs(y - P.y) >= EPS;
}

template<typename T, typename R>
Point<T, R> &Point<T, R>::operator=(const Point<T, R> &P) {
    x = P.x;
    y = P.y;
    return *this;
}

template<typename T, typename R>
R Point<T, R>::operator%(const Point<T, R> &P) const {
    return x * P.x + y * P.y;
}

template<typename T, typename R>
bool LeftRotate(const Point<T, R>& P1, const Point<T, R>& P2) {
    return P1 * P2 > 0;
}

#endif //GINS_POINT_H
