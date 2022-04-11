//
// Created by jojo on 03.04.2022.
//

#include "Low.h"

std::tuple<ll, ll, err> Low::Run(int points, int seed) const {
    PolygonData Polygon;
    auto err = Polygon.Create();
    if (!err) {
        return std::make_tuple(0, 0, errors::Wrap(err, "low algo"));
    }

    ll checksum = 0, in = 0;

    auto p = Polygon.GetData();
    int n = Polygon.GetLen();

    PointData Pts(points, seed);

    for (int i = 0; i < CNT_BATCH; ++i) {
        ll s = 0;
        while (true) {
            auto[pt, nxt] = Pts.GetPt(i);
            if (!nxt) {
                break;
            }

            bool inside = false;
            for (int j = 1; j + 1 < n; ++j) {
                if (InTriangle(p[0], p[j], p[j + 1], pt)) {
                    inside = true;
                    ++in;
                    break;
                }
            }

            s = (s * BASE_MOD + inside) % CHECK_MOD;
        }
        checksum = (checksum + s) % CHECK_MOD;
    }

    return std::make_tuple(checksum, in, errors::NIL);
}