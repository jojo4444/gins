//
// Created by jojo on 03.04.2022.
//

#include "Low.h"

std::tuple<ll, err> Low::Test(bool check) const {
    PolygonData Polygon;
    auto err = Polygon.Create();
    if (!err) {
        return std::make_tuple(0, errors::Wrap(err, "low algo"));
    }

    ll checksum = 0;

    auto p = Polygon.GetData();
    int n = Polygon.GetLen();

    PointData Pts(check);

    for (int i = 0; i < CNT_BATCH; ++i) {
        ll s = 0;
        while (true) {
            auto [pt, nxt] = Pts.GetPt(i);
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
        checksum = (checksum + s) % CHECK_MOD;
    }

    return std::make_tuple(checksum, errors::NIL);
}