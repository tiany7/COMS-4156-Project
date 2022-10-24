#include "course_service.h"


CourseDB::CourseDB() {
    driver = get_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "root", "");
    con->setSchema("enrollment"); // change schema name
}

ErrorCode CourseDB::execute(const std::string& query) {
    try {
        stmt = con->createStatement();
        res = stmt->executeQuery(query);
    } catch(sql::SQLException &e) {
        return ErrorCode::ERROR;
    }

    return ErrorCode::NO_ERROR;
}

ErrorCode CourseDB::GetCourseInfo(const int32_t cid, const string& semester,CourseInfoResponse* response) {
    char buffer[BUFFER_SIZE] = {0};
    string sql = "SELECT * from course WHERE uni= %d and semester = '%s'";
    sprintf(buffer, sql.c_str(), cid, semester.c_str());
    ErrorCode sql_error_code = execute(string(buffer));
    if (sql_error_code == ErrorCode::ERROR) {
        return sql_error_code;
    }

    while (res->next()) {
        CourseInfo* temp;
        string s ;
        s = string(res->getString(1));
        temp->set_allocated_department(&s);
        s = string(res->getString(2));
        temp->set_allocated_course(&s);
        s = string(res->getString(3));
        temp->set_allocated_course_title(&s);
        s = string(res->getString(4));
        temp->set_allocated_semester(&s);
        s = string(res->getString(5));
        temp->set_allocated_course_id(&s);
        s = string(res->getString(6));
        temp->set_allocated_faculty_name(&s);
        s = string(res->getString(7));
        temp->set_allocated_faculty_uni(&s);
        s = string(res->getString(12));
        temp->set_allocated_prereq1(&s);
        s = string(res->getString(13));
        temp->set_allocated_prereq2(&s);
        s = string(res->getString(14));
        temp->set_allocated_prereq3(&s);
        response->set_allocated_course(temp);
    }
    return ErrorCode::NO_ERROR;
}

ErrorCode CourseDB::GetCourseList(const string& department, const string& semester, CourseListResponse* response) {
    char buffer[BUFFER_SIZE] = {0};
    string sql = "SELECT * from course WHERE department='%s' and semester = '%s";
    sprintf(buffer, sql.c_str(), department.c_str(), semester.c_str());
    ErrorCode sql_error_code = execute(string(buffer));
    if (sql_error_code == ErrorCode::ERROR) {
        return sql_error_code;
    }

    while (res->next()) {
        CourseInfo* temp = response->add_course();

        string s ;
        s = string(res->getString(1));
        temp->set_allocated_department(&s);
        s = string(res->getString(2));
        temp->set_allocated_course(&s);
        s = string(res->getString(3));
        temp->set_allocated_course_title(&s);
        s = string(res->getString(4));
        temp->set_allocated_semester(&s);
        s = string(res->getString(5));
        temp->set_allocated_course_id(&s);
        s = string(res->getString(6));
        temp->set_allocated_faculty_name(&s);
        s = string(res->getString(7));
        temp->set_allocated_faculty_uni(&s);
        s = string(res->getString(12));
        temp->set_allocated_prereq1(&s);
        s = string(res->getString(13));
        temp->set_allocated_prereq2(&s);
        s = string(res->getString(14));
        temp->set_allocated_prereq3(&s);
        
    }
    return ErrorCode::NO_ERROR;
}

ErrorCode CourseDB::GetCoursePrereq(const string& course, CoursePrereqResponse* response) {
    char buffer[BUFFER_SIZE] = {0};
    string sql = "SELECT prereq1, prereq2, prereq3 from course WHERE course='%s'";
    sprintf(buffer, sql.c_str(), course.c_str());
    ErrorCode sql_error_code = execute(string(buffer));
    if (sql_error_code == ErrorCode::ERROR) {
        return sql_error_code;
    }
    int i = 0;
    while (res->next()) {
        // response->set_course(string(res->getString(1)));
        response->set_course(i,string(res->getString(1)));
        ++i;
    }
    return ErrorCode::NO_ERROR;
}

ErrorCode CourseDB::DeleteCourse(const int32_t cid, const string& semester, DeleteCourseResponse* response) {
    char buffer[BUFFER_SIZE] = {0};
    string sql = "Delete from course WHERE cid = %d and semester ='%s'";
    sprintf(buffer, sql.c_str(), cid, semester.c_str());
    ErrorCode sql_error_code = execute(string(buffer));
    if (sql_error_code == ErrorCode::ERROR) {
        response->set_message("DELETE FAILED!");
        return sql_error_code;
    }
    response->set_message("DELETE SUCCESS!");
    return ErrorCode::NO_ERROR;
}

CourseDB::~CourseDB() {
    if (con) {
        delete con;
        con = nullptr;
    }
    if (stmt) {
        delete stmt;
        stmt = nullptr;
    }
    // if (pstmt) {
    //     delete pstmt;
    //     pstmt = nullptr;
    // }
    if (res) {
        delete res;
        res = nullptr;
    }
}




Status CourseServiceImpl::GetCourseInfo(ServerContext* context, const GetCourseInfoRequest* request, CourseInfoResponse* response) {
    ErrorCode error_code = CourseDB().GetCourseInfo(request->cid(), request->semester(), response);//
    if (error_code == ErrorCode::ERROR) {
        return Status::CANCELLED;
    }
    return Status::OK;
}

Status CourseServiceImpl::GetCourseList(ServerContext* context, GetCourseListRequest* request, CourseListResponse* response) {
    ErrorCode error_code = CourseDB().GetCourseList(request->department(), request->semester(), response);//
    if (error_code == ErrorCode::ERROR) {
        return Status::CANCELLED;
    }
    return Status::OK;
}

Status CourseServiceImpl::GetCoursePrereq(ServerContext* context, GetCoursePrereqRequest* request, CoursePrereqResponse* response) {
    ErrorCode error_code = CourseDB().GetCoursePrereq(request->course(), response);//
    if (error_code == ErrorCode::ERROR) {
        return Status::CANCELLED;
    }
    return Status::OK;
}

Status CourseServiceImpl::DeleteCourse(ServerContext* context, DeleteCourseRequest* request, DeleteCourseResponse* response) {
    ErrorCode error_code = CourseDB().DeleteCourse(request->cid(),request->semester(), response);//
    if (error_code == ErrorCode::ERROR) {
        return Status::CANCELLED;
    }
    return Status::OK;
}


void RunServer() {
    std::string server_address("0.0.0.0:50052");
    CourseServiceImpl service;

    grpc::EnableDefaultHealthCheckService(true);
    ServerBuilder builder;
    // Listen on the given address without any authentication mechanism.
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    // Register "service" as the instance through which we'll communicate with
    // clients. In this case it corresponds to an *synchronous* service.
    builder.RegisterService(&service);
    // Finally assemble the server.
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;

    // Wait for the server to shutdown. Note that some other thread must be
    // responsible for shutting down the server for this call to ever return.
    server->Wait();
}

int main(int argc, char** argv) {
    RunServer();
    return 0;
}
