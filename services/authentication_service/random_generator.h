// So we first generate a token, then store it into the redis
// database, and then return the token to the client when login
#pragma once
#include <chrono>
#include <cstdio>
#include <ctime>
#include <iostream>
#include <random>
#include <string>
class RandomGenerator {
 public:
  RandomGenerator();
  ~RandomGenerator();
  static std::string GenerateToken(const std::string& salt = "basic_salt");
};