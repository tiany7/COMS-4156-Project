#pragma once

#include <cstdlib>
#include <iostream>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include "mysql_connection.h"

#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>

#include "proto/time_proto/time.grpc.pb.h"
#include "time_service.hh"

using std::string;
using std::cout;
using std::endl;
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

class TimeServiceImpl final: public TimeService::Service {
    Status CheckTime(ServerContext* context, const GetTimeArg* request, TimeRsp* reply) {
        auto dept = request->deptid();
        int success = TimeDBService().CheckTime(dept, reply);
        return Status::OK;
    }

    Status ClearTime(ServerContext* context, const GetTimeArg* request, TimeRsp* reply) {
        auto dept = request->deptid();
        int success = TimeDBService().ClearTime(dept, reply);
        return Status::OK;
    }

    Status InsertTime(ServerContext* context, const Timeslot* request, TimeRsp* reply)
    {
        auto dept = request->deptid();
        auto start_time = request->start();
        auto end_time = request->end();

        int success = TimeDBService().InsertTime(dept, start_time, end_time);
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
