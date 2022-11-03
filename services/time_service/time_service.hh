#pragma once

#include <cstdlib>
#include <iostream>
#include <string>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include "mysql_connection.h"

#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>

#include "proto/time_proto/time.grpc.pb.h"
#include "DB.hh"

using std::cout;
using std::endl;
using std::string;
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

class TimeDBService : public DB{
public:
    TimeDBService():DB("coms4156_db"){}
    int CheckTime(const string & dept_id, TimeRsp* reply);
    int InsertTime(const string & dept_id, const string & start_time, const string & end_time);
    int ClearTime(const string & dept_id, TimeRsp* reply);
};
