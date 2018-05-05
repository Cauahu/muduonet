#include "gtest/gtest.h"
#include "../include/base/logging.h"
#include <iostream>
#include <stdio.h>
#include <string>

using namespace muduonet;

TEST(MUDUONET, logging) {
    testing::internal::CaptureStdout();
    LOG_TRACE << "hello";
    std::string output = testing::internal::GetCapturedStdout();
    std::cout << output;

}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
