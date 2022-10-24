#ifndef BUILDING_LIBRARY
#define BUILDING_LIBRARY
#include <stdlib.h>
#include <string>
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
#include "DB.h"

using std::cout;
using std::endl;
using std::string;
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

class FacultyDBService : public DB{
public:
    FacultyDBService();
    int GetFacultyDept(const string & dept_name, FacultyRsp* reply);
    virtual ~FacultyDBService();
};


#endif