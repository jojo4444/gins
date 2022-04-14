//
// Created by jojo on 13.04.2022.
//

#include "Hard.h"

std::tuple<ll, ll, err> Hard::Run(int points, int seed) const {
    PolygonData Polygon;
    auto err = Polygon.Create();
    if (!err) {
        return std::make_tuple(0, 0, errors::Wrap(err, "Hard algo"));
    }

    auto p = Polygon.GetData();
    int n = Polygon.GetLen();
    int lg = std::max(0, std::__lg(n - 1) - 1);

    // https://www.cplusplus.com/doc/tutorial/dynamic/
    // for bad_alloc
    auto tans = new(std::nothrow) double[n - 1];
    if (tans == nullptr) {
        return std::make_tuple(0, 0, errors::NewError("bad alloc (tans)"));
    }

    // https://medium.com/software-design/why-software-developers-should-care-about-cpu-caches-8da04355bb8a#:~:text=A%20cache%20line%20is%20the,region%20is%20read%20or%20written.
    // https://en.cppreference.com/w/c/memory/aligned_alloc
    auto etan = (double *) aligned_alloc(64, (sizeof(double)) * (n + 1));
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

            int k = 1;
            // 1 cache line -> prefetch

            for (int j = 0; j < lg; ++j) {
                __builtin_prefetch(etan + (k << 3));
                k = (k << 1) + (etan[k] < t);
            }

            while (k <= n - 1) {
                __builtin_prefetch(etan + (k << 3));
                k = (k << 1) + (etan[k] < t);
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
    free(etan);
    delete[] num;

    return std::make_tuple(checksum, in, errors::NIL);
}