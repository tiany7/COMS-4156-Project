#ifndef MYSQL_SERVER_H
#define MYSQL_SERVER_H
#include <stdlib.h>
#include <iostream>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include "mysql_connection.h"

#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>

#include "proto/mysql_server_proto/faculty.grpc.pb.h"
#include "faculty_service.h"

using std::string;
using std::cout;
using std::endl;
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

class FacultyServiceServiceImpl final: public FacultyService::Service {
    Status GetFaculty(ServerContext* context, const GetFacultyReq* request,
                      FacultyRsp* reply) {
        auto dept = request->department();
        int success = FacultyDBService().GetFacultyDept(dept, reply);
        return Status::OK;
    }
};

class MysqlServer{
public:
    void bind_address(string addr, int port) {
        address = addr + ":" + std::to_string(port);
    }
    void Run();
private:
    string address;
};


#endif