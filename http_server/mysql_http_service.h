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

