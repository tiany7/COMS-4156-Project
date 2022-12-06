#pragma once
#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>
#include <nlohmann/json.hpp>

#include "httplib.h"
#include "proto/mysql_server_proto/faculty.grpc.pb.h"
#include "services/authentication_service/auth_checker.h"


using json = nlohmann::json;

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using std::vector;
using std::string;
class FacultyServiceClient {
private:
    std::unique_ptr<FacultyService::Stub> stub_;

public:
    FacultyServiceClient(std::shared_ptr<Channel> channel)
            : stub_(FacultyService::NewStub(channel)) {}
    vector<Faculty> GetFaculty(string dept);
    vector<Faculty> GetFacultyByUni(const string &uni);
    vector<Profpost> GetPost(const string &uni);
    int InsertFaculty(const string &name, const string &dept, const string &uni, const string & country);
    int InsertPost(const string &uni, const string &content, const string &status, const string & postid);
    int ModifyPost(const string & postid, const string &uni, const string &content, const string &status);
    int DeletePost(const string & postid);
};

    FacultyServiceClient facultyServiceClient(grpc::CreateChannel(
            "localhost:50051", grpc::InsecureChannelCredentials()));

    httplib::Server svr;
    AuthServiceClient auth_checker(
            grpc::CreateChannel("localhost:95955", grpc::InsecureChannelCredentials()));

    svr.Options("/(.*)",
              [&](const httplib::Request & /*req*/, httplib::Response &res) {
                  res.set_header("Access-Control-Allow-Methods", " POST, GET, OPTIONS");
                  res.set_header("Content-Type", "text/html; charset=utf-8");
                  res.set_header("Access-Control-Allow-Headers", "X-Requested-With, Content-Type, Accept");
                  res.set_header("Access-Control-Allow-Origin", "*");
                  res.set_header("Connection", "close");
              });
    
    svr.Get("/search_dept", [&](const httplib::Request & req, httplib::Response &res) {
        auto param = req.get_param_value("department");
        vector<Faculty> v = facultyServiceClient.GetFaculty(param);
        std::ostringstream os;
        for(auto it : v){
            os << it.name()<<" | "<< it.department()<< " | "<<it.uni()<<" | "<<it.country()<< std::endl;
        }
        res.set_header("Access-Control-Allow-Credentials", "true");
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
        res.set_header("Access-Control-Allow-Methods", "POST GET OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "x-requested-with,Content-Type,X-CSRF-Token");
        res.set_content(os.str().c_str(), "text/plain");
    });

    svr.Get("/search_uni", [&](const httplib::Request & req, httplib::Response &res) {
        auto body = req.get_param_value("uni");
        vector<Faculty> v = facultyServiceClient.GetFacultyByUni(body);
        std::ostringstream os;
        for(auto it : v){
            os << it.name()<<" | "<< it.department()<< " | "<<it.uni()<<" | "<<it.country()<< std::endl;
        }
        res.set_header("Access-Control-Allow-Credentials", "true");
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
        res.set_header("Access-Control-Allow-Methods", "POST GET OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "x-requested-with,Content-Type,X-CSRF-Token");
        res.set_content(os.str().c_str(), "text/plain");
    });

    svr.Post("/add_instructor", [&](const httplib::Request & req, httplib::Response &res) {
        auto js = json::parse(req.body);
        auto name = js["name"];
        auto dept = js["department"];
        auto uni = js["uni"];
        auto country = js["country"];
        auto access_token = js["access_token"];
        auto username = js["username"];
        json j;
        if (!auth_checker.IsLoggedIn(username)){
            j["status"] = "error";
            j["message"] = "not logged in";
            res.set_content(j.dump(), "application/json");
            return;
        }
        if (!auth_checker.CheckSecret(username, access_token)){
            j["status"] = "error";
            j["message"] = "invalid access token";
            res.set_content(j.dump(), "application/json");
            return;
        }

        auto ret = facultyServiceClient.InsertFaculty(name, dept, uni, country);
        j["status"] = ret;

        res.set_header("Access-Control-Allow-Credentials", "true");
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
        res.set_header("Access-Control-Allow-Methods", "POST GET OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "x-requested-with,Content-Type,X-CSRF-Token");
        res.set_content(j.dump(), "application/json");
    });

    svr.Post("/add_profpost", [&](const httplib::Request & req, httplib::Response &res) {
        auto js = json::parse(req.body);
        auto uni = js["uni"];
        auto content = js["content"];
        auto status = js["status"];
        auto postid = js["postid"];
        auto access_token = js["access_token"];
        auto username = js["username"];
        json j;
        if (!auth_checker.IsLoggedIn(username)){
            j["status"] = "error";
            j["message"] = "not logged in";
            res.set_content(j.dump(), "application/json");
            return;
        }
        if (!auth_checker.CheckSecret(username, access_token)){
            j["status"] = "error";
            j["message"] = "invalid access token";
            res.set_content(j.dump(), "application/json");
            return;
        }

        auto ret = facultyServiceClient.InsertPost(uni, content, status, postid);
        j["status"] = ret;

        res.set_header("Access-Control-Allow-Credentials", "true");
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
        res.set_header("Access-Control-Allow-Methods", "POST GET OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "x-requested-with,Content-Type,X-CSRF-Token");
        res.set_content(j.dump(), "application/json");
    });

    svr.Post("/mod_profpost", [&](const httplib::Request & req, httplib::Response &res) {
        auto js = json::parse(req.body);
        auto uni = js["uni"];
        auto content = js["content"];
        auto status = js["status"];
        auto postid = js["postid"];
        auto access_token = js["access_token"];
        auto username = js["username"];
        json j;
        if (!auth_checker.IsLoggedIn(username)){
            j["status"] = "error";
            j["message"] = "not logged in";
            res.set_content(j.dump(), "application/json");
            return;
        }
        if (!auth_checker.CheckSecret(username, access_token)){
            j["status"] = "error";
            j["message"] = "invalid access token";
            res.set_content(j.dump(), "application/json");
            return;
        }

        auto ret = facultyServiceClient.ModifyPost(postid, uni, content, status);
        j["status"] = ret;

        res.set_header("Access-Control-Allow-Credentials", "true");
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
        res.set_header("Access-Control-Allow-Methods", "POST GET OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "x-requested-with,Content-Type,X-CSRF-Token");
        res.set_content(j.dump(), "application/json");
    });

    svr.Get("/search_post", [&](const httplib::Request & req, httplib::Response &res) {
        auto body = req.get_param_value("uni");
        auto v = facultyServiceClient.GetPost(body);
        std::ostringstream os;
        for(auto it : v){
            os << it.postid()<<" | "<< it.uni()<< " | "<<it.content()<<" | "<<it.status()<< std::endl;
        }
        res.set_header("Access-Control-Allow-Credentials", "true");
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
        res.set_header("Access-Control-Allow-Methods", "POST GET OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "x-requested-with,Content-Type,X-CSRF-Token");
        res.set_content(os.str().c_str(), "text/plain");
    });

    std::cout << "Server started" << std::endl;
    svr.listen("0.0.0.0", 8080);
    return 0;
}