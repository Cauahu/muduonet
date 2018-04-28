
#include "gtest/gtest.h"
#include "../include/base/stringpiece.h"
#include <stdio.h>
#include <iostream>

using namespace muduonet;

TEST(MUDUONET, StringPeice) {
    StringPiece sp("hello world");
    StringPiece sp1("I love you");

    printf("%s:[%d]\n", sp.data(), sp.size());
    printf("%s:[%d]\n", sp1.data(), sp1.size());
    
    EXPECT_FALSE(sp.empty());
    EXPECT_FALSE(sp1.empty());
    
    printf("begin:%s\n", sp.begin());
    printf("begin:%s\n", sp1.begin());

    printf("end:%s\n", sp.end());
    printf("end:%s\n", sp1.end());

    sp.remove_prefix(6);

    sp1 = sp;

    EXPECT_TRUE(sp == sp1);

    std::cout << sp1.as_string() << std::endl;
    std::cout << sp << std::endl;
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
