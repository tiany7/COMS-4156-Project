#include "course_service.h"

// #include <mysqlx/xdevapi.h>

CourseDB::CourseDB() {
    driver = get_driver_instance();
//    con = driver->connect("host.docker.internal", "root", "Czh19981011");
    con = driver->connect("tcp://localhost:3306", "root", "");
    con->setSchema("coms4156_db"); // change schema name
    std::cout << "I connected to mysql server\n";
}

ErrorCode CourseDB::execute(const std::string& query, const int mode) {
    try {
        stmt = con->createStatement();
        if (mode == 0){
            res = stmt->executeQuery(query);
        } else if (mode == 1){
            int rows = stmt->executeUpdate(query);
        } 
    } catch(sql::SQLException &e) {
        std::cout << "This is where the error is in server line 16\n";
        return ErrorCode::ERROR;
    }

    return ErrorCode::NO_ERROR;
}

ErrorCode CourseDB::_GetCourseTitle(const string& course, const string& semester, CourseTitleResponse* response){
    std::cout << " I am in line 23 Server\n";
    char buffer[BUFFER_SIZE] = {0};
    string sql = "SELECT course_title from course WHERE course= '%s' and semester = '%s' limit 1";
    sprintf(buffer, sql.c_str(), course.c_str(), semester.c_str());
    ErrorCode sql_error_code = execute(string(buffer),0);
    std::cout << "SQL success !!!!!!!!!!!!!!!!!!!!!!\n";
    if (sql_error_code == ErrorCode::ERROR) {
        std::cout <<" Server Line 31 error \n";
        return sql_error_code;
    }

    std::cout << "connection entered in server in line29\n";
    while (res->next()) { // this is an line info
        response->set_course_title(res->getString(1));
    }
    return ErrorCode::NO_ERROR;
}

ErrorCode CourseDB::_GetCourseInfo(const int32_t cid, const string& semester,CourseInfoResponse* response) {
    std::cout << " I am in line 23 Server\n";
    char buffer[BUFFER_SIZE] = {0};
    string sql = "SELECT * from course WHERE course_id= %d and semester = '%s' limit 1";
    sprintf(buffer, sql.c_str(), cid, semester.c_str());
    ErrorCode sql_error_code = execute(string(buffer),0);
    if (sql_error_code == ErrorCode::ERROR) {
        return sql_error_code;
    }

    std::cout << "connection entered in server in line29\n";
    while (res->next()) { // this is an line info
        CourseInfo* c = response->mutable_course();
        c->set_department(string(res->getString(1)));
        c->set_course(string(res->getString(2)));
        c->set_course_title(string(res->getString(3)));
        c->set_semester(string(res->getString(4)));
        c->set_course_id(string(res->getString(5)));
        c->set_faculty_name(string(res->getString(6)));
        c->set_faculty_uni(string(res->getString(7)));
        std::cout << "Reading Success in server in line 41\n";
        c->set_prereq1(string(res->getString(8)));
        c->set_prereq2(string(res->getString(9)));
        c->set_prereq3(string(res->getString(10)));
    }
    return ErrorCode::NO_ERROR;
}

ErrorCode CourseDB::_GetCourseList(const string& department, const string& semester, CourseListResponse* response) {
    char buffer[BUFFER_SIZE] = {0};
    string sql = "SELECT * from course WHERE department='%s' and semester = '%s'";
    sprintf(buffer, sql.c_str(), department.c_str(), semester.c_str());
    ErrorCode sql_error_code = execute(string(buffer),0);
    if (sql_error_code == ErrorCode::ERROR) {
        return sql_error_code;
    }

    std::cout << res->rowsCount() << std::endl;

    while (res->next()) {
        std::cout << "TEsting iterating of rows" << std::endl;
        CourseInfo* c = response->add_course();
        c->set_department(string(res->getString(1)));
        c->set_course(string(res->getString(2)));
        c->set_course_title(string(res->getString(3)));
        c->set_semester(string(res->getString(4)));
        c->set_course_id(string(res->getString(5)));
        c->set_faculty_name(string(res->getString(6)));
        c->set_faculty_uni(string(res->getString(7)));
        c->set_prereq1(string(res->getString(8)));
        c->set_prereq2(string(res->getString(9)));
        c->set_prereq3(string(res->getString(10)));
    }
    return ErrorCode::NO_ERROR;
}

ErrorCode CourseDB::_GetCoursePrereq(const string& course, CoursePrereqResponse* response) {
    char buffer[BUFFER_SIZE] = {0};
    string sql = "SELECT prereq1, prereq2, prereq3 from course WHERE course='%s' limit 1;";
    // this should later be in the collection shit
    // check the student course collection to get the valid response
    
    // use this to check xdevapi

    // there might be the transpose issue !
    sprintf(buffer, sql.c_str(), course.c_str());
    ErrorCode sql_error_code = execute(string(buffer),0);
    if (sql_error_code == ErrorCode::ERROR) {
        return sql_error_code;
    }

    while (res->next()) {
        // response->set_course(string(res->getString(1)));
        response->set_pre1(string(res->getString(1)));
        response->set_pre2(string(res->getString(2)));
        response->set_pre3(string(res->getString(3)));
    }
    
    return ErrorCode::NO_ERROR;
}

ErrorCode CourseDB::_InsertCourse(const string& course, const string& semester, const string& course_title,
    const int32_t cid, CRUDCourseResponse* response) {
    char buffer[BUFFER_SIZE] = {0};
    string sql = "insert into course (course, semester, course_title, course_id) "
             " values ( '%s' , '%s' , '%s' , %d) ;";
    sprintf(buffer, sql.c_str(),  course.c_str(), semester.c_str(), course_title.c_str(), cid);
    ErrorCode sql_error_code = execute(string(buffer),1);
    if (sql_error_code == ErrorCode::ERROR) {
        std::cout << "Success Insert!\n";
        response->set_message("Insert FAILED!");
        return sql_error_code;
    }
    response->set_message("Insert SUCCESS!");
    return ErrorCode::NO_ERROR;
}

ErrorCode CourseDB::_UpdateCourse(const string& course, const string& semester, const string& course_title,
            const string& faculty_name, const string& faculty_uni, CRUDCourseResponse* response) {
    char buffer[BUFFER_SIZE] = {0};
    string sql = "Update course  "
             "Set course_title = '%s', faculty_name = '%s', faculty_uni = '%s' "
             "WHERE course = '%s' and semester ='%s' ;";
    sprintf(buffer, sql.c_str(), course_title.c_str(), faculty_name.c_str(),
        faculty_uni.c_str(), course.c_str(), semester.c_str());
    ErrorCode sql_error_code = execute(string(buffer),1);
    if (sql_error_code == ErrorCode::ERROR) {
        std::cout << "Success Update!\n";
        response->set_message("Update FAILED!");
        return sql_error_code;
    }
    response->set_message("Update SUCCESS!");
    return ErrorCode::NO_ERROR;
}


ErrorCode CourseDB::_DeleteCourse(const int32_t cid, const string& semester, CRUDCourseResponse* response) {
    char buffer[BUFFER_SIZE] = {0};
    string sql = "Delete from course WHERE course_id = %d and semester ='%s'";
    sprintf(buffer, sql.c_str(), cid, semester.c_str());
    ErrorCode sql_error_code = execute(string(buffer),1);
    // this will have segmentation fault, no message back to the course_client
    if (sql_error_code == ErrorCode::ERROR) {
        std::cout << "Success Delete!\n";
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

Status CourseServiceImpl::GetCourseTitle(ServerContext* context, const GetCourseTitleRequest* request, CourseTitleResponse* response){
    ErrorCode error_code = CourseDB()._GetCourseTitle(request->course(), request->semester(), response);//
    if (error_code == ErrorCode::ERROR) {
        std::cout << "193 Server Error\n";
        return Status::CANCELLED;
    }
    return Status::OK;
}


Status CourseServiceImpl::GetCourseInfo(ServerContext* context, const GetCourseInfoRequest* request, CourseInfoResponse* response) {
    ErrorCode error_code = CourseDB()._GetCourseInfo(request->cid(), request->semester(), response);//
    if (error_code == ErrorCode::ERROR) {
        return Status::CANCELLED;
    }
    return Status::OK;
}

Status CourseServiceImpl::GetCourseList(ServerContext* context, const GetCourseListRequest* request, CourseListResponse* response) {
    ErrorCode error_code = CourseDB()._GetCourseList(request->department(), request->semester(), response);//
    if (error_code == ErrorCode::ERROR) {
        return Status::CANCELLED;
    }
    return Status::OK;
}

Status CourseServiceImpl::GetCoursePrereq(ServerContext* context, const GetCoursePrereqRequest* request, CoursePrereqResponse* response) {
    ErrorCode error_code = CourseDB()._GetCoursePrereq(request->course(), response);//
    if (error_code == ErrorCode::ERROR) {
        return Status::CANCELLED;
    }
    return Status::OK;
}

Status CourseServiceImpl::InsertCourse(ServerContext* context, const InsertCourseRequest* request, CRUDCourseResponse* response) {
    ErrorCode error_code = CourseDB()._InsertCourse(request->course(),
        request->semester(), 
        request->course_title(),
        request->cid(),
        response);//
    if (error_code == ErrorCode::ERROR) {
        return Status::CANCELLED;
    }
    return Status::OK;
}

Status CourseServiceImpl::UpdateCourse(ServerContext* context, const UpdateCourseRequest* request, CRUDCourseResponse* response) {
    ErrorCode error_code = CourseDB()._UpdateCourse(request->course(),
        request->semester(),
        request->course_title(),
        request->faculty_name(),
        request->faculty_uni(),
        response);//
    if (error_code == ErrorCode::ERROR) {
        return Status::CANCELLED;
    }
    return Status::OK;
}

Status CourseServiceImpl::DeleteCourse(ServerContext* context, const DeleteCourseRequest* request, CRUDCourseResponse* response) {
    ErrorCode error_code = CourseDB()._DeleteCourse(request->cid(),request->semester(), response);//
    if (error_code == ErrorCode::ERROR) {
        return Status::CANCELLED;
    }
    return Status::OK;
}


void RunServer() {
    std::string server_address("0.0.0.0:50053");
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
