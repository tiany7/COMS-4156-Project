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
#include "proto/course_proto/course.grpc.pb.h"

#define BUFFER_SIZE 256

using ::std::string;
// using ::course::GetCourseListRequest;
// using ::course::CourseListResponse;
// using ::course::GetCourseInfoResponse;
// using ::course::CourseInfoResponse;
// using ::course::GetCoursePrereqRequest;
// using ::course::CoursePrereqRequest;

using ::grpc::Server;
using ::grpc::ServerBuilder;
using ::grpc::ServerContext;
using ::grpc::Status;

enum ErrorCode {
    NO_ERROR = 0,
    ERROR = 1,
};


// later needs base DB class
// try using OAT++ next time
class CourseDB {
private:
    sql::Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;
    // sql::PreparedStatement *pstmt;
    sql::ResultSet *res;

public:
    CourseDB() ;
    ~CourseDB() ;

    ErrorCode execute(const std::string& query) ;

    ErrorCode GetCourseInfo(const int32_t cid, const string& semester,CourseInfoResponse* response) ;

    ErrorCode GetCourseList(const string& department, const string& semester, CourseListResponse* response) ;

    ErrorCode GetCoursePrereq(const string& course, CoursePrereqResponse* response) ;

    ErrorCode DeleteCourse(const int32_t cid, const string& semester, DeleteCourseResponse* response) ;
};


class CourseServiceImpl final : public CourseService::Service {
public:
    Status GetCourseInfo(ServerContext* context, const GetCourseInfoRequest* request, CourseInfoResponse* response) ;

    Status GetCourseList(ServerContext* context, GetCourseListRequest* request, CourseListResponse* response) ;

    Status GetCoursePrereq(ServerContext* context, GetCoursePrereqRequest* request, CoursePrereqResponse* response) ;

    Status DeleteCourse(ServerContext* context, DeleteCourseRequest* request, DeleteCourseResponse* response) ;
};