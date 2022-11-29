#include "redis_client.h"

#include <sstream>
RedisClient::RedisClient() {}

RedisClient::~RedisClient() {
  //    if (client_.is_connected()) {
  //        client_.disconnect();
  //    }
}

void RedisClient::Connect() {
  if (!client_.is_connected()) {
    client_.connect("127.0.0.1", 6379,
                    [](const std::string& host, std::size_t port,
                       cpp_redis::client::connect_state status) {
                      if (status == cpp_redis::client::connect_state::dropped) {
                        std::cout << "client disconnected from " << host << ":"
                                  << port << std::endl;
                      }
                    });
  }
}

void RedisClient::Disconnect() {
  //    if (client_.is_connected())
  //    {
  //        client_.disconnect();
  //    }
}

int RedisClient::Set(const std::string& key, const std::string& value) {
  if (!client_.is_connected()) {
    return -1;
  }
  client_.set(key, value, [](cpp_redis::reply& reply) {
    std::cout << "set " << reply << std::endl;
  });
  //    Commit();
  return 0;
}

bool RedisClient::CompareIfEqual(const std::string& key,
                                 const std::string& secret) {
  if (!client_.is_connected()) {
    std::cout << "client is not connected" << std::endl;
    return false;
  }
  std::string value;
  std::string temp;
  bool cmpResult = false;
  auto res = client_.get(key);
  client_.sync_commit();
  std::ostringstream oss;
  oss << res.get();
  temp = oss.str();
  cmpResult = (temp == secret);
  return cmpResult;
}

void RedisClient::Commit() {
  if (client_.is_connected()) {
    client_.sync_commit();
  }
}

bool RedisClient::Exists(const std::string& key) {
  if (!client_.is_connected()) {
    return false;
  }
  bool result = false;
  auto res = client_.exists({key});
  client_.sync_commit();
  std::ostringstream oss;
  oss << res.get();
  std::cout << "here   " << oss.str() << std::endl;
  result = (oss.str() == "1");
  return result;
}
