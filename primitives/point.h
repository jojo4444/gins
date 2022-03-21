//
// Created by jojo on 21.03.2022.
//

#ifndef GINS_POINT_H
#define GINS_POINT_H

#include <cmath>
#include <type_traits>

using ll = long long;

// T: type coordinate
// R: type result in operations
//
// p1 * p2 - vector product
// p1 % p2 - scalar product
//
// eps for check p1 == p2
// ---- if R is int or ll -> eps ignored (using is_same)

template<typename T, typename R, R eps = 0>
struct Point {
    T x, y;

    Point();

    Point(T x_, T y_);

    R len2() const;

    long double len() const;

    // rotate pi/2 to left
    Point<T, R, eps> ort() const;

    Point<T, R, eps> rotate(long double angle) const;

    Point<T, R, eps> operator+(const Point<T, R, eps> &P) const;

    Point<T, R, eps> operator-(const Point<T, R, eps> &P) const;

    Point<T, R, eps> operator*(R t) const;

    Point<T, R, eps> operator/(R t) const;

    bool operator==(const Point<T, R, eps> &P) const;

    bool operator!=(const Point<T, R, eps> &P) const;

    // vector product
    R operator*(const Point &P) const;

    // scalar product
    R operator%(const Point &P) const;
};

template<typename T, typename R, R eps>
Point<T, R, eps>::Point() {
    x = y = 0;
}

template<typename T, typename R, R eps>
Point<T, R, eps>::Point(T x_, T y_) {
    x = x_;
    y = y_;
}

template<typename T, typename R, R eps>
R Point<T, R, eps>::len2() const {
    return *this % *this;
}

template<typename T, typename R, R eps>
long double Point<T, R, eps>::len() const {
    return (R) sqrt(*this % *this);
}

template<typename T, typename R, R eps>
Point<T, R, eps> Point<T, R, eps>::ort() const {
    return Point<T, R, eps>(-y, x);
}

template<typename T, typename R, R eps>
Point<T, R, eps> Point<T,R,eps>::rotate(long double angle) const {
    return *this * cosl(angle) + ort() * sinl(angle);
}

template<typename T, typename R, R eps>
Point<T, R, eps> Point<T, R, eps>::operator+(const Point<T, R, eps> &P) const {
    return Point<T, R, eps>(x + P.x, y + P.y);
}

template<typename T, typename R, R eps>
Point<T, R, eps> Point<T, R, eps>::operator-(const Point<T, R, eps> &P) const {
    return Point<T, R, eps>(x - P.x, y - P.y);
}

template<typename T, typename R, R eps>
Point<T, R, eps> Point<T, R, eps>::operator*(R t) const {
    return Point<T, R, eps>(x * t, y * t);
}

template<typename T, typename R, R eps>
Point<T, R, eps> Point<T, R, eps>::operator/(R t) const {
    return *this * (R) (1. / t);
}

template<typename T, typename R, R eps>
R Point<T, R, eps>::operator*(const Point<T, R, eps> &P) const {
    return x * P.y - y * P.x;
}

template<typename T, typename R, R eps>
bool Point<T, R, eps>::operator==(const Point<T, R, eps> &P) const {
    if (std::is_same<T, int>() || std::is_same<T, ll>()) {
        return x == P.x && y == P.y;
    }
    return abs(x - P.x) < eps && abs(y - P.y) < eps;
}

template<typename T, typename R, R eps>
bool Point<T, R, eps>::operator!=(const Point<T, R, eps> &P) const {
    if (std::is_same<T, int>() || std::is_same<T, ll>()) {
        return x != P.x || y != P.y;
    }
    return abs(x - P.x) >= eps || abs(y - P.y) >= eps;
}

template<typename T, typename R, R eps>
R Point<T, R, eps>::operator%(const Point<T, R, eps> &P) const {
    return x * P.x + y * P.y;
}

template<typename T, typename R, R eps>
bool LeftRotate(const Point<T, R, eps>& P1, const Point<T, R, eps>& P2) {
    return P1 * P2 > 0;
}

#endif //GINS_POINT_H
