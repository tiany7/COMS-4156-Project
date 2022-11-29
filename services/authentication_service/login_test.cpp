#include "login.h"

#include <gtest/gtest.h>

using namespace testing;
bool allDigits(const char* str) {
  while (*str) {
    if (!isdigit(*str)) return false;
    str++;
  }
  return true;
}

TEST(TestLogin, LogMain) {
  Login login;
  EXPECT_EQ(login.LogIn("admin1", "admin1"), "user not exists");
  login.LogOut("admin");
  login.Register("admin", "admin");
  auto secret = login.LogIn("admin", "admin");
  bool result = allDigits(secret.c_str());
  login.LogOut("admin");
  EXPECT_EQ(result, true);
  EXPECT_EQ(login.IsLegalOperator("admin", secret), true);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}