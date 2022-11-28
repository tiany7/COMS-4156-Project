// So we first generate a token, then store it into the redis
// database, and then return the token to the client when login
#pragma once
#include <iostream>
#include <chrono>
#include <string>

#include <cstdio>
#include <ctime>
#include <random>
class RandomGenerator {
public:
    RandomGenerator();
    ~RandomGenerator();
    static std::string GenerateToken(const std::string& salt = "basic_salt");
};