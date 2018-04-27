#include <iostream>

#include "gtest/gtest.h"
#include "../include/base/timestamp.h"
using namespace muduonet;

TEST(TIMESTAMP, now) {
    Timestamp ts = Timestamp::now();
    std::cout << ts.toFormattedString(0) << std::endl;
    std::cout << ts.toString() << std::endl;
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
