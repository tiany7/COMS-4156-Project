#include "redis_client.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <iostream>

using namespace testing;

TEST(RedisClientTest, TestRedisClient) {
  RedisClient client;
  client.Connect();

  auto ret = client.Set("test", "test");
  client.Commit();
  EXPECT_EQ(ret, 0);

  auto ret1 = client.CompareIfEqual("test", "test");
  EXPECT_EQ(ret1, true);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
  //    return 0;
}
