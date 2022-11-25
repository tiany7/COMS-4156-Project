#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <utility>

#include "mysql_connection.h"
#include "cppconn/driver.h"
#include "cppconn/exception.h"
#include "cppconn/resultset.h"
#include "cppconn/statement.h"

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

    ErrorCode execute(const std::string& query, const int mode) ;

    ErrorCode _GetCourseTitle(const string& course, const string& semester,CourseTitleResponse* response) ;

    ErrorCode _GetCourseInfo(const int32_t cid, const string& semester,CourseInfoResponse* response) ;

    ErrorCode _GetCourseList(const string& department, const string& semester, CourseListResponse* response) ;

    ErrorCode _GetCoursePrereq(const string& course, CoursePrereqResponse* response) ;

    ErrorCode _InsertCourse(const string& course, const string& semester, const string& course_title,
    const int32_t cid, CRUDCourseResponse* response);

    ErrorCode _UpdateCourse(const string& course, const string& semester, const string& course_title,
            const string& faculty_name, const string& faculty_uni, CRUDCourseResponse* response);
    
    ErrorCode _DeleteCourse(const int32_t cid, const string& semester, CRUDCourseResponse* response) ;
};


class CourseServiceImpl final : public CourseService::Service {
public:
    Status GetCourseTitle(ServerContext* context, const GetCourseTitleRequest* request, CourseTitleResponse* response);

    Status GetCourseInfo(ServerContext* context, const GetCourseInfoRequest* request, CourseInfoResponse* response) ;

    Status GetCourseList(ServerContext* context, const GetCourseListRequest* request, CourseListResponse* response) ;

    Status GetCoursePrereq(ServerContext* context, const GetCoursePrereqRequest* request, CoursePrereqResponse* response) ;

    Status InsertCourse(ServerContext* context, const InsertCourseRequest* request, CRUDCourseResponse* response);
    Status UpdateCourse(ServerContext* context, const UpdateCourseRequest* request, CRUDCourseResponse* response);
    Status DeleteCourse(ServerContext* context, const DeleteCourseRequest* request, CRUDCourseResponse* response) ;
};