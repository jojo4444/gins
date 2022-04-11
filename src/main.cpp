#include "solve/low/Low.h"
#include "solve/lowPlus/LowPlus.h"
#include "solve/algo.h"
#include <iomanip>

int main() {
    Low l1;
    LowPlus l2;

    auto[checksum1, tm1, err1] = calcTime(l1, true);
    auto[checksum2, tm2, err2] = calcTime(l2, true);

    if (!err1) {
        err1.log();
        return 0;
    }
    if (!err2) {
        err2.log();
        return 0;
    }

    std::cout << std::setprecision(9) << std::fixed;

    std::cout << tm1 << "s " << checksum1 << "\n";
    std::cout << tm2 << "s " << checksum2 << "\n";

    return 0;
}
