//
// Created by jojo on 11.04.2022.
//

#include "medium.h"

std::tuple<ll, ll, err> Medium::Run(int points, int seed) const {
    PolygonData Polygon;
    auto err = Polygon.Create();
    if (!err) {
        return std::make_tuple(0, 0, errors::Wrap(err, "medium algo"));
    }

    auto p = Polygon.GetData();
    int n = Polygon.GetLen();

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

            /// left, down or up
            if (pt.x <= p[0].x || LeftRotate(pt - p[0], p[1] - p[0]) || LeftRotate(p[n - 1] - p[0], pt - p[0])) {
                s = (s * BASE_MOD) % CHECK_MOD;
                continue;
            }


            bool inside = false;

            int l = 1, r = n; /// [l; r)
            while (l + 1 < r) {
                int m = (l + r) >> 1;
                if (RightRotate(p[m] - p[0], pt - p[0])) {
                    r = m;
                } else {
                    l = m;
                }
            }

            inside = InTriangle(p[0], p[l], p[l + 1], pt);
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

    return std::make_tuple(checksum, in, errors::NIL);
}
