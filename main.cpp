#include "solve/low/Low.h"
#include "solve/algo.h"

int main() {
    Low l;
    auto [checksum, err] = l.Test(true);

    if (!err) {
        err.log();
        return 0;
    }

    std::cout << checksum << "\n";

    return 0;
}
