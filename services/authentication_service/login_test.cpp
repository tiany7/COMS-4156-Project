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
  login.LogOut("admin2");
  login.Register("admin", "admin");
  login.Register("admin2", "admin2");
  auto secret = login.LogIn("admin", "admin");
  bool result = allDigits(secret.c_str());
  login.LogOut("admin");
  EXPECT_EQ(result, true);
  EXPECT_EQ(login.IsLegalOperator("admin", secret), true);
  EXPECT_EQ(login.IsLegalOperator("admin", "123"), false);
  EXPECT_EQ(login.IsLegalOperator("admin2", secret), false);
  EXPECT_EQ(login.IsLegalOperator("admin2", "123"), false);
  auto secret2 = login.LogIn("admin2", "admin2");
  EXPECT_EQ(login.IsLegalOperator("admin2", secret2), true);
  EXPECT_EQ(login.IsLegalOperator("admin2", "123"), false);
  EXPECT_EQ(login.IsLegalOperator("admin", secret2), false);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}