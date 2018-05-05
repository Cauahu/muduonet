
#include "gtest/gtest.h"
#include "../include/base/logstream.h"
#include <stdio.h>
#include <iostream>

using namespace muduonet;

TEST(MUDUONET, LogStream) {
    LogStream ls;
    short s = -1;
    unsigned short us = 10;
    int i = -100;
    unsigned int ui = 1000;
    long l = -10000;
    unsigned long ul = 100000;
    long long ll = -1000000;
    unsigned long long ull = 10000000;
    double d = 100000000.123456789;
    const std::string str("huzhuang");
    Fmt fmt("fmt:%d\n", 10);
    
    ls << s << " " << us << " " << i << " " << ui << " " << l << " " << ul << " ";
    ls << ll << " " << ull << " " << d << " " << (void*)&str << " " << str;
    ls << fmt;

    std::cout << ls.buffer().data();
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
