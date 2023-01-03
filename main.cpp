#include <iostream>
#include "fmt/core.h"

int main() {
    std::cout << "Hello World" << std::endl;
    fmt::print("{}", std::numeric_limits<double>::infinity());
    return 0;
}