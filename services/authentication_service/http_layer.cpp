#include "httplib.h"
#include "login.h"
#include <string>
using namespace httplib;

int main() {
  Server svr;
  Login login;
  svr.Get("/Hello", [&](const Request& req, Response& res) {
    res.set_content("Hello World!", "text/plain");
  });
  svr.Post("/Register", [&](const Request & req, Response &res) {
    //json
    auto username = req.get_param_value("username");
    auto password = req.get_param_value("password");

    auto result = login.Register(username, password);
    std::string response = std::string("") + "{\"Success\":\""+ (result ? "ok" : "user already exists") +"\"}";
    res.set_content(response.c_str(), "application/json");
  });

  svr.Post("/login", [&](const Request & req, Response &res) {
    //json
    std::cout<<req.body<<" "<<req.get_param_value("username")<<std::endl;
    auto username = req.get_param_value("username");
    auto password = req.get_param_value("password");

    auto result = login.LogIn(username, password);
    std::string response = std::string("") + "{\"access_token\":\""+ result +"\"}";
    if (result == "user not exists")
    {
        response = std::string("") + "{\"Error\":\""+ result +"\"}";
    }
    if (result == "Already logged in")
    {
        response = std::string("") + "{\"Error\":\""+ result +"\"}";
    }
    res.set_content(response.c_str(), "application/json");
  });
  svr.Post("/logout", [&](const Request & req, Response &res) {
    //json
    auto username = req.get_param_value("username");

    login.LogOut(username);
    std::string response = std::string("") + "{\"log out\":\""+ "ok" +"\"}";
    res.set_content(response.c_str(), "application/json");
  });
  svr.listen("localhost", 8080);
}