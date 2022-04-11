//
// Created by jojo on 03.04.2022.
//

#include "gtest/gtest.h"
#include "../src/primitives/point.h"

TEST(PtInTriangle, Board) {
    Point p1(0, 0);
    Point p2(20, 0);
    Point p3(0, 20);

    Point<int, ll> ta[] = {
            Point(10, 10),
            Point(0, 5),
            Point(13, 7),
            Point(20, 0),
            Point(0, 20),
    };

    for (const auto &p: ta) {
        EXPECT_EQ(InTriangle(p1, p2, p3, p), true);
    }
}

TEST(PtInTriangle, Inside) {
    Point p1(5, 5);
    Point p2(-10, 10);
    Point p3(5, 15);

    Point<int, ll> ta[] = {
            Point(4, 10),
            Point(3, 10),
            Point(2, 10),
            Point(1, 10),
            Point(0, 10),
            Point(-2, 10),
            Point(-5, 10),
            Point(-9, 10),
    };

    for (const auto &p: ta) {
        EXPECT_EQ(InTriangle(p1, p2, p3, p), true);
    }
}

TEST(PtOutTriangle, out) {
    Point p1(5, 5);
    Point p2(10, 10);
    Point p3(7, 12);

    Point<int, ll> ta[] = {
            Point(0, 1),
            Point(4, 5),
            Point(11, 10),
            Point(4444, 4444),
            Point(-1000000000, 1000000000),
            Point(10, 9),
            Point(7, 13),
            Point(6, 13),
    };

    for (const auto &p: ta) {
        EXPECT_EQ(InTriangle(p1, p2, p3, p), false);
    }
}