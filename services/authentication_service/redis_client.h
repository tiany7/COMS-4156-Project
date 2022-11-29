#pragma once

#include <cpp_redis/cpp_redis>
#include <iostream>
#include <string>

class RedisClient {
 public:
  RedisClient();
  ~RedisClient();

  void Connect();
  void Disconnect();

  int Set(const std::string& key, const std::string& value);
  bool CompareIfEqual(const std::string& key, const std::string& secret);
  void Commit();
  bool Exists(const std::string& key);

 private:
  cpp_redis::client client_;
};