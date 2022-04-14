//
// Created by jojo on 14.04.2022.
//

#include "HardPlus.h"

int iffs[16][16];

std::tuple<ll, ll, err> HardPlus::Run(int points, int seed) const {
    PolygonData Polygon;
    auto err = Polygon.Create();
    if (!err) {
        return std::make_tuple(0, 0, errors::Wrap(err, "HardPlus algo"));
    }

    auto p = Polygon.GetData();
    int n = Polygon.GetLen();

    // https://www.cplusplus.com/doc/tutorial/dynamic/
    // for bad_alloc
    auto tans = new(std::nothrow) double[n];
    if (tans == nullptr) {
        return std::make_tuple(0, 0, errors::NewError("bad alloc (tans)"));
    }

    int blocks = (n + B - 1) / B;

    int P = (1 << 21);
    int T = (64 * blocks + P - 1) / P * P;

    /// https://man7.org/linux/man-pages/man2/madvise.2.html
    /// madvise

    auto btree = (double *) aligned_alloc(P, T);
    if (btree == nullptr) {
        return std::make_tuple(0, 0, errors::NewError("bad alloc (btree)"));
    }
    madvise(btree, T, MADV_HUGEPAGE);

    auto num = (int *) aligned_alloc(P, T);
    if (num == nullptr) {
        return std::make_tuple(0, 0, errors::NewError("bad alloc (btree num)"));
    }
    madvise(num, T, MADV_HUGEPAGE);

    for (int i = 0; i < n - 1; ++i) {
        auto vec = p[i + 1] - p[0];
        tans[i] = (double) vec.y / vec.x;
    }
    tans[n - 1] = INF_TAN; /// +oo

    int it = 0;
    build(0, it, n, blocks, btree, num, tans);

    PointData Pts(points, seed);

    ll sRes[CNT_BATCH];
    ll cnt[CNT_BATCH];

    for (int i = 0; i < 16; ++i) {
        for (int j = 0; j < 16; ++j) {
            iffs[i][j] = __builtin_ffs(~(i + 16 * j)) - 1;
            __builtin_prefetch(&iffs[i][j], 0, 3);
        }
    }

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

            double t = (double) vec.y / vec.x + 1e-16;

            int k = 0, id = 0, j;
            __m256d x = _mm256_set1_pd(t);
            while (k < blocks) {
                j = iffs[cmp(x, &btree[k << 3])][cmp(x, &btree[(k << 3) + 4])];
                id = ((j < B) ? (k << 3) + j : id);
                k += (k << 3) + j + 1;
            }
            id = num[id] + 1;

            bool inside = InTriangle(p[0], p[id - 1], p[id], pt);
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
    free(btree);
    free(num);

    return std::make_tuple(checksum, in, errors::NIL);
}

int go(int k, int i) {
    return k * (B + 1) + i + 1;
}

void build(int k, int &t, int n, int blocks, double *__restrict__ btree, int *__restrict__ num,
           const double *__restrict__ a) {
    if (k < blocks) {
        for (int i = 0; i < B; i++) {
            build(go(k, i), t, n, blocks, btree, num, a);
            num[k * B + i] = t;
            btree[k * B + i] = (t < n ? a[t++] : INF_TAN);
        }
        build(go(k, B), t, n, blocks, btree, num, a);
    }
}

// load: 1 cache line (else -> throw)
// loadu: >= 1 cache line
// ptr aligned 64 * t
int cmp(const __m256d &x, const double *ptr) {
    /// load 4 double
    __m256d y = _mm256_load_pd(ptr);

    /// compare all (x_i > y_i)
    __m256d mask = _mm256_cmp_pd(x, y, _CMP_GT_OS);

    /// create mask_int from mask_vec
    return _mm256_movemask_pd(mask);
}