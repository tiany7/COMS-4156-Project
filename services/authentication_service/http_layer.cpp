#include "httplib.h"
#include "login.h"
#include <string>
#include <nlohmann/json.hpp>
using json = nlohmann::json;
using namespace httplib;

int main() {
  Server svr;
  Login login;
  svr.Get("/Hello", [&](const Request& req, Response& res) {
    res.set_content("Hello World!", "text/plain");
  });
  svr.Post("/Register", [&](const Request & req, Response &res) {
    auto valueMap = json::parse(req.body);
    std::string username = valueMap["username"];
    std::string password = valueMap["password"];

    json j;
    auto result = login.Register(username, password);
    std::cout<<username<<std::endl;
    std::cout<<password<<std::endl;
    if (result) {
      j["status"] = "success";
    }
    else {
      j["status"] = "duplicated user";
    }
    res.set_content(j.dump(), "application/json");

  });

  svr.Post("/login", [&](const Request & req, Response &res) {
    //json
      auto valueMap = json::parse(req.body);
      std::string username = valueMap["username"];
      std::string password = valueMap["password"];

    auto result = login.LogIn(username, password);
    json j;
    j["access_token"] = result;
    if (result == "user not exists")
    {
        j["error"] = "user not exists";
    }
    if (result == "Already logged in")
    {
        j["error"] = "Already logged in";
    }
    if (result.empty())
    {
        j["error"] = "wrong password";
    }

    res.set_content(j.dump(), "application/json");
  });
  svr.Post("/logout", [&](const Request & req, Response &res) {
    //json

      auto valueMap = json::parse(req.body);
      std::string username = valueMap["username"];
      login.LogOut(username);
      json j;
      j["logout"] = "success";
    res.set_content(j.dump(), "application/json");
  });
  svr.listen("localhost", 8080);
}