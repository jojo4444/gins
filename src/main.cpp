#include "solve/algo.h"

#include "solve/low/Low.h"
#include "solve/lowPlus/LowPlus.h"
#include "solve/medium/medium.h"

#include <iomanip>



int main() {
    /*
    while (true) {
        auto[type, points]
    }
     */
    
    Low l1;
    LowPlus l2;
    Medium m1;

    int points = 15;

    auto[checksum1, in1, tm1, err1] = calculateAlgo(l1, points, 1);
    auto[checksum2, in2, tm2, err2] = calculateAlgo(l2, points, 1);
    auto[checksum3, in3, tm3, err3] = calculateAlgo(m1, points, 1);

    if (!err1) {
        err1.log();
        return 0;
    }
    if (!err2) {
        err2.log();
        return 0;
    }
    if (!err3) {
        err2.log();
        return 0;
    }

    std::cout << std::setprecision(9) << std::fixed;

    std::cout << tm1 << "s " << checksum1 << " " << in1 << "\n";
    std::cout << tm2 << "s " << checksum2 << " " << in2 << "\n";
    std::cout << tm3 << "s " << checksum3 << " " << in3 << "\n";

    return 0;
}
