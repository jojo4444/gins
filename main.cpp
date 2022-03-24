#include <iostream>

#include "primitives/point.h"

int main() {
    Point p1(1, 0);
    Point p2(0, 1);

    std::cout << LeftRotate(p1, p2) << "\n";

    return 0;
}
