#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "random_generator.h"
#include <iostream>

using namespace testing;

TEST(RandomGeneratorTest, Randomness) {
    RandomGenerator random_generator;
    for(int i = 1; i <= 1000; ++i){
        EXPECT_NE((random_generator.GenerateToken()), (random_generator.GenerateToken()));
        EXPECT_NE((random_generator.GenerateToken()), (random_generator.GenerateToken()));
        EXPECT_NE((random_generator.GenerateToken()), (random_generator.GenerateToken()));
    }
}

TEST(RandomGeneratorTest, RandomnessReq) {
    RandomGenerator random_generator;
    EXPECT_NE((random_generator.GenerateToken()).length(), 4);
}

TEST(RandomGeneratorTest, RandomnessReq2) {
    RandomGenerator random_generator;
    EXPECT_NE((random_generator.GenerateToken()).length(), 0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}