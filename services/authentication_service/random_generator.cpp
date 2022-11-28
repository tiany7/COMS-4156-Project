
#include "random_generator.h"

RandomGenerator::RandomGenerator() {

}

RandomGenerator::~RandomGenerator()
{

}

std::string RandomGenerator::GenerateToken(const std::string & salt)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::string token;
    unsigned long long hash = 0;
    for (int i = 0; i < salt.length(); i++)
    {
        hash *= 26ull;
        hash += salt[i] - 'a';
    }

    std::uniform_int_distribution<int> distrib(1, 100000);
    auto now = std::chrono::system_clock::now();
    auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
    auto value = now_ms.time_since_epoch();
    auto duration = value.count();
    token = std::to_string(duration) + std::to_string(distrib(gen)) + std::to_string(hash);
    return token;
}