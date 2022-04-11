//
// Created by jojo on 11.04.2022.
//

#include "mediumPlus.h"

std::tuple<ll, ll, err> MediumPlus::Run(int points, int seed) const {
    PolygonData Polygon;
    auto err = Polygon.Create();
    if (!err) {
        return std::make_tuple(0, 0, errors::Wrap(err, "MediumPlus algo"));
    }

    auto p = Polygon.GetData();
    int n = Polygon.GetLen();

    // https://www.cplusplus.com/doc/tutorial/dynamic/
    // for bad_alloc
    auto angles = new(std::nothrow) double[n];
    if (angles == nullptr) {
        return std::make_tuple(0, 0, errors::NewError("bad alloc (angles)"));
    }

    for (int i = 1; i < n; ++i) {
        auto vec = p[i] - p[0];
        angles[i] = atan2(vec.y, vec.x);
    }

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

            auto vec = pt - p[0];

            /// left, down or up
            if (pt.x < p[0].x || LeftRotate(vec, p[1] - p[0]) || LeftRotate(p[n - 1] - p[0], vec)) {
                s = (s * BASE_MOD) % CHECK_MOD;
                continue;
            }

            bool inside = false;

            auto phi = atan2(vec.y, vec.x) + 1e-14;
            int l = 1, r = n; /// [l; r)
            while (l + 1 < r) {
                int m = (l + r) >> 1;
                if (angles[m] > phi) {
                    r = m;
                } else {
                    l = m;
                }
            }

            inside = InTriangle(p[0], p[l], p[l + 1], pt) || (l > 1 && InTriangle(p[0], p[l - 1], p[l], pt));

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

    delete[] angles;

    return std::make_tuple(checksum, in, errors::NIL);
}