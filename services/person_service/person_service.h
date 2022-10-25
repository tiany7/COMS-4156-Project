#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <utility>

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#include "proto/person_proto/person.grpc.pb.h"

#define BUFFER_SIZE 256

using ::std::string;
using ::person::PersonService;
using ::person::StudentReadRequest;
using ::person::StudentReadResponse;
using ::person::FacultyReadRequest;
using ::person::FacultyReadResponse;
using ::person::AdministratorReadRequest;
using ::person::AdministratorReadResponse;
using ::person::UpdateEmailRequest;
using ::person::UpdateEmailResponse;
using ::person::Student;
using ::person::Faculty;
using ::person::Administrator;

using ::grpc::ServerBuilder;
using ::grpc::ServerContext;
using ::grpc::Status;

enum ErrorCode {
    NO_ERROR = 0,
    ERROR = 1,
};

class PersonDB {
private:
    sql::Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;
    sql::ResultSet *res;

public:
    PersonDB() ;
    ~PersonDB() ;

    ErrorCode execute(const std::string& query) ;

    ErrorCode GetStudentInfo(const std::string &table, const std::string& uni, StudentReadResponse* response) ;

    ErrorCode GetFacultyInfo(const std::string& table, const std::string& uni, FacultyReadResponse* response) ;

    ErrorCode GetAdministratorInfo(const std::string& table, const std::string& uni, AdministratorReadResponse* response) ;

    ErrorCode UpdateEmail(const std::string& table, const std::string& uni, const std::string& email, UpdateEmailResponse* response) ;
};


class PersonServiceImpl final : public PersonService::Service {
public:
    Status ReadStudentInfo(ServerContext* context, const StudentReadRequest* request, StudentReadResponse* response) ;

    Status ReadFacultyInfo(ServerContext* context, FacultyReadRequest* request, FacultyReadResponse* response) ;

    Status ReadAdministratorInfo(ServerContext* context, AdministratorReadRequest* request, AdministratorReadResponse* response) ;

    Status UpdateEmail(ServerContext* context, UpdateEmailRequest* request, UpdateEmailResponse* response) ;
};