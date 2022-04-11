//
// Created by jojo on 03.04.2022.
//

#include "gtest/gtest.h"
#include "../src/primitives/point.h"

TEST(PtInTriangle, Board) {
    Point p1(0, 0);
    Point p2(20, 0);
    Point p3(0, 20);
    Point A(10, 10);
    EXPECT_EQ(InTriangle(p1, p2, p3, A), true);
}