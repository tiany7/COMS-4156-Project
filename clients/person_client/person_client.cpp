#include <iostream>
#include <memory>
#include <string>

#include "httplib.h"
#include <grpcpp/grpcpp.h>
#include "proto/person_proto/person.pb.h"
#include "proto/person_proto/person.grpc.pb.h"

using ::grpc::Channel;
using ::grpc::ClientContext;
using ::grpc::Status;

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

enum ErrorCode {
    NO_ERROR = 0,
    ERROR = 1,
};

class PersonServiceClient {
public:
    PersonServiceClient(std::shared_ptr<Channel> channel)
            : stub_(PersonService::NewStub(channel)) {}

    ErrorCode ReadStudentInfo(const std::string &uni, Student& student) {
        StudentReadRequest request;
        request.set_uni(uni);

        StudentReadResponse response;
        ClientContext context;
        Status status = stub_->ReadStudentInfo(&context, request, &response);

        if (status.ok() && response.has_student()) {
            student = response.student();
        }

        return ErrorCode::NO_ERROR;
    }
    
    ErrorCode ReadFacultyInfo(const std::string& uni, Faculty& faculty) {
        FacultyReadRequest request;
        request.set_uni(uni);

        FacultyReadResponse response;
        ClientContext context;
        Status status = stub_->ReadFacultyInfo(&context, request, &response);

        if (status.ok() && response.has_faculty()) {
            faculty = response.faculty();
        }

        return ErrorCode::NO_ERROR;
    }

    ErrorCode ReadAdministratorInfo(const std::string& uni, Administrator& administrator) {
        AdministratorReadRequest request;
        request.set_uni(uni);

        AdministratorReadResponse response;
        ClientContext context;
        Status status = stub_->ReadAdministratorInfo(&context, request, &response);

        if (status.ok() && response.has_administrator()) {
            administrator = response.administrator();
        }

        return ErrorCode::NO_ERROR;
    }

    ErrorCode UpdateEmail(const std::string& uni, const std::string& email) {
        UpdateEmailRequest request;
        request.set_uni(uni);
        request.set_email(email);

        UpdateEmailResponse response;
        ClientContext context;
        Status status = stub_->UpdateEmail(&context, request, &response); 
        if (!status.ok()) {
            return ErrorCode::ERROR;
        }

        return ErrorCode::NO_ERROR;
    }

private:
    std::unique_ptr<PersonService::Stub> stub_;
};

int main(int argc, char** argv) {
    std::string target_str("localhost:50053");
    PersonServiceClient person_service_client(grpc::CreateChannel(target_str, grpc::InsecureChannelCredentials()));

    httplib::Server svr;
    svr.Get("/get_student_info", [&](const httplib::Request &req, httplib::Response &res) {
        std::string uni("");
        if (req.has_param("uni")) {
            uni = req.get_param_value("uni");
        }
        Student student;
        ErrorCode error_code = person_service_client.ReadStudentInfo(uni, student);
        if (error_code == ErrorCode::ERROR) {
            if (uni.empty()) {
                res.set_content("Empty UNI", "text/plain");
            } else {
                res.set_content("Internal Error", "text/plain");
            }
        } else {
            std::ostringstream ss;
            ss << "uni | name | email | affiliation | school | advisor" << std::endl;
            ss << student.uni() << " | " << student.name() << " | " << student.email() << " | ";
            ss << student.affiliation() << " | " << student.school() << " | " << student.advisor << std::endl;
            res.set_content(ss.str().c_str(), "text/plain"); 
        }
    });

    svr.Get("/get_faculty_info", [&](const httplib::Request &req, httplib::Response &res) {
        std::string uni("");
        if (req.has_param("uni")) {
            uni = req.get_param_value("uni");
        }
        Faculty faculty;
        ErrorCode error_code = person_service_client.ReadFacultyInfo(uni, faculty);
        if (error_code == ErrorCode::ERROR) {
            if (uni.empty()) {
                res.set_content("Empty UNI", "text/plain");
            } else {
                res.set_content("Internal Error", "text/plain");
            }
        } else {
            std::ostringstream ss;
            ss << "uni | name | email | school" << std::endl;
            ss << faculty.uni() << " | " << faculty.name() << " | " << faculty.email() << " | "  << faculty.school() << std::endl;
            res.set_content(ss.str().c_str(), "text/plain"); 
        }
    });

    svr.Get("/get_administrator_info", [&](const httplib::Request &req, httplib::Response &res) {
        std::string uni("");
        if (req.has_param("uni")) {
            uni = req.get_param_value("uni");
        }
        Administrator administrator;
        ErrorCode error_code = person_service_client.ReadAdministratorInfo(uni, administrator);
        if (error_code == ErrorCode::ERROR) {
            if (uni.empty()) {
                res.set_content("Empty UNI", "text/plain");
            } else {
                res.set_content("Internal Error", "text/plain");
            }
        } else {
            std::ostringstream ss;
            ss << "uni | name | email" << std::endl;
            ss << administrator.uni() << " | " << administrator.name() << " | " << administrator.email() << std::endl;
            res.set_content(ss.str().c_str(), "text/plain"); 
        }
    });

    svr.listen("0.0.0.0", 8083);
    return 0;
}