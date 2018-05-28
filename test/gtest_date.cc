#include "gtest/gtest.h"
#include "../include/base/date.h"
#include <iostream>

using namespace muduonet;

TEST(MUDUONET, date) {
    Date d1(2018, 5, 21);
    std::cout << d1.toString() << std::endl;

    Date d2(2018, 5, 20);
    std::cout << d2.toString() << std::endl;

    std::cout << (d1<d2) << std::endl;
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


