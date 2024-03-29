//
// Created by jojo on 11.04.2022.
//

#include "LowPlus.h"

std::tuple<ll, ll, err> LowPlus::Run(int points, int seed) const {
    PolygonData Polygon;
    auto err = Polygon.Create();
    if (!err) {
        return std::make_tuple(0, 0, errors::Wrap(err, "low-plus algo"));
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

            bool inside = false;
            for (int j = 1; j + 1 < n; ++j) {
                if (InTriangle(p[0], p[j], p[j + 1], pt)) {
                    inside = true;
                    ++c;
                    break;
                }
            }

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
