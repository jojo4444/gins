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