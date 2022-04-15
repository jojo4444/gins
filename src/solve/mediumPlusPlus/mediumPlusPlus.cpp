//
// Created by jojo on 12.04.2022.
//

#include "mediumPlusPlus.h"

std::tuple<ll, ll, err> MediumPlusPlus::Run(int points, int seed) const {
    PolygonData Polygon;
    auto err = Polygon.Create();
    if (!err) {
        return std::make_tuple(0, 0, errors::Wrap(err, "MediumPlusPlus algo"));
    }

    auto p = Polygon.GetData();
    int n = Polygon.GetLen();

    // https://www.cplusplus.com/doc/tutorial/dynamic/
    // for bad_alloc
    auto tans = new(std::nothrow) double[n - 1];
    if (tans == nullptr) {
        return std::make_tuple(0, 0, errors::NewError("bad alloc (tans)"));
    }

    auto etan = new(std::nothrow) double[n];
    if (etan == nullptr) {
        return std::make_tuple(0, 0, errors::NewError("bad alloc (etz tans)"));
    }

    auto num = new(std::nothrow) int[n];
    if (num == nullptr) {
        return std::make_tuple(0, 0, errors::NewError("bad alloc (etz num)"));
    }

    for (int i = 0; i < n - 1; ++i) {
        auto vec = p[i + 1] - p[0];
        tans[i] = (double) vec.y / vec.x;
    }

    int it = 0;
    eytzinger(1, n - 1, it, etan, num, tans);

    PointData Pts(points, seed);

    ll sRes[CNT_BATCH];
    ll cnt[CNT_BATCH];

    auto calculate = [&](int i) -> void {
        ll &s = sRes[i];
        ll &c = cnt[i];
        s = 0;
        c = 0;

        while (true) {
            auto[pt, nxt] = Pts.GetPt(i);
            if (!nxt) {
                break;
            }

            if (p[0] == pt) {
                s = (s * BASE_MOD + 1) % CHECK_MOD;
                continue;
            }

            auto vec = pt - p[0];

            /// left, down or up
            if (pt.x <= p[0].x || LeftRotate(vec, p[1] - p[0]) || LeftRotate(p[n - 1] - p[0], vec)) {
                s = (s * BASE_MOD) % CHECK_MOD;
                continue;
            }

            bool inside = false;

            double t = (double) vec.y / vec.x + 1e-16;

            /// if-else - slow / predication - fast
            /// https://en.wikipedia.org/wiki/Branch_predictor#:~:text=In%20computer%20architecture%2C%20a%20branch,flow%20in%20the%20instruction%20pipeline.
            int k = 1;
            while (k <= n - 1) {
                k = 2 * k + (etan[k] < t);
            }
            k >>= __builtin_ffs(~k);
            k = num[k] + 1;

            inside = InTriangle(p[0], p[k - 1], p[k], pt);

            c += inside;

            s = (s * BASE_MOD + inside) % CHECK_MOD;
        }
    };

    std::thread th[CNT_BATCH];
    for (int i = 0; i < CNT_BATCH; ++i) {
        th[i] = std::thread(calculate, i);
    }

    ll checksum = 0, in = 0;
    for (int i = 0; i < CNT_BATCH; ++i) {
        th[i].join();
        checksum = (checksum + sRes[i]) % CHECK_MOD;
        in += cnt[i];
    }

    delete[] tans;
    delete[] etan;
    delete[] num;

    return std::make_tuple(checksum, in, errors::NIL);
}