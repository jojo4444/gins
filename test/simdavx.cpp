//
// Created by jojo on 14.04.2022.
//

#pragma GCC target("avx2")

#include "gtest/gtest.h"
#include <x86intrin.h>

int maskGreaterAvx(const std::vector<double> &xv, const std::vector<double> &yv) {
    __m256d x = _mm256_set_pd(xv[0], xv[1], xv[2], xv[3]);
    __m256d y = _mm256_set_pd(yv[0], yv[1], yv[2], yv[3]);
    __m256d cmp = _mm256_cmp_pd(x, y, _CMP_GT_OS);
    int mask = _mm256_movemask_pd(cmp);
    return mask;
}

int maskGreater(const std::vector<double> &xv, const std::vector<double> &yv) {
    int mask = 0;
    for (int i = 0; i < 4; ++i) {
        mask = (mask << 1) + (xv[i] > yv[i]);
    }
    return mask;
}

TEST(CompareDouble256, Greater) {
    std::vector<std::pair<std::vector<double>, std::vector<double> > > tt = {
            {{3,   14,  8,  2},   {27,  11, 5,   2}},
            {{1,   2,   3,  4},   {4,   3,  2,   1}},
            {{-10, -11, -9, -4},  {4,   5,  5,   0}},
            {{3,   2,   2,  1},   {0,   0,  -1,  -1000}},
            {{4,   0,   4,  0},   {1,   10, 1,   10}},
            {{4,   100, 4,  100}, {100, 1,  100, 1}},
    };

    for (const auto &p: tt) {
        auto &xv = p.first;
        auto &yv = p.second;

        ASSERT_EQ(xv.size(), 4);
        ASSERT_EQ(yv.size(), 4);

        int mask = maskGreaterAvx(xv, yv);
        int want = maskGreater(xv, yv);

        EXPECT_EQ(mask, want);
    }
}

TEST(LoadDouble, loadu) {
    int len = 8 * 4;
    auto *ptr = (double *) malloc(len * (sizeof(double)));

    for (int i = 0; i < len; ++i) {
        ptr[i] = i;
    }

    ASSERT_NE(ptr, nullptr);

    for (int i = 0; i < len; i += 4) {
        __m256d x = _mm256_loadu_pd(ptr + i);

        union {
            __m256d y;
            double y_[4];
        } val{
            x,
        };

        for (int j = 0; j < 4; ++j) {
            EXPECT_EQ(val.y_[j], ptr[i + j]);
        }
    }

    free(ptr);
}