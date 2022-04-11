//
// Created by jojo on 11.04.2022.
//

#include "LowPlus.h"

std::tuple<ll, err> LowPlus::Run(bool check) const {
    PolygonData Polygon;
    auto err = Polygon.Create();
    if (!err) {
        return std::make_tuple(0, errors::Wrap(err, "low-plus algo"));
    }

    ll checksum = 0;

    auto p = Polygon.GetData();
    int n = Polygon.GetLen();

    PointData Pts(check);

    ll sRes[CNT_BATCH];

    auto calculate = [&](int i) -> void {
        ll& s = sRes[i];
        s = 0;

        while (true) {
            auto[pt, nxt] = Pts.GetPt(i);
            if (!nxt) {
                break;
            }

            bool inside = false;
            for (int j = 1; j + 1 < n; ++j) {
                if (InTriangle(p[0], p[j], p[j + 1], pt)) {
                    inside = true;
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

    for (int i = 0; i < CNT_BATCH; ++i) {
        th[i].join();
        checksum = (checksum + sRes[i]) % CHECK_MOD;
    }

    return std::make_tuple(checksum, errors::NIL);
}
