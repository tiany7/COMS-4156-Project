#pragma once
#include "random_generator.h"
#include "redis_client.h"
class Login {
 public:
  Login();
  ~Login();

  std::string LogIn(const std::string& username, const std::string& password);
  bool Register(const std::string& username, const std::string& password);
  bool IsLoggedIn(const std::string& username);
  void LogOut(const std::string& username);
  bool IsLegalOperator(const std::string& username, const std::string& secret);

 private:
  RedisClient* redis_client_;
  std::string getRedisKey(const std::string& username);
  std::string getRedisLogKey(const std::string& username);
  RandomGenerator* random_generator_;
};