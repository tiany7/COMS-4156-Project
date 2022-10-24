#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>
#include "proto/person_proto/person.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
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

enum ErrorCode {
    NO_ERROR = 0,
    ERROR = 1,
};

class PersonServiceClient {
public:
    PersonServiceClient(std::shared_ptr<Channel> channel)
            : stub_(PersonService::NewStub(channel)) {}

    ErrorCode ReadStudentInfo(const std::string& table, const std::string &uni, Student& student) {
        StudentReadRequest request;
        request.set_table(table);
        request.set_uni(uni);

        StudentReadResponse response;
        ClientContext context;
        Status status = stub_->ReadStudentInfo(&context, request, &response);

        if (status.ok() && response.has_student()) {
            student = response.student();
        }

        return ErrorCode::NO_ERROR;
    }
    
    ErrorCode ReadFacultyInfo(const std::string& table, const std::string& uni, Faculty& faculty) {
        FacultyReadRequest request;
        request.set_table(table);
        request.set_uni(uni);

        FacultyReadResponse response;
        ClientContext context;
        Status status = stub_->ReadFacultyInfo(&context, request, &response);

        if (status.ok() && response.has_faculty()) {
            faculty = response.faculty();
        }

        return ErrorCode::NO_ERROR;
    }

    ErrorCode ReadAdministratorInfo(const std::string& table, const std::string& uni, Administrator& administrator) {
        AdministratorReadRequest request;
        request.set_table(table);
        request.set_uni(uni);

        AdministratorReadResponse response;
        ClientContext context;
        Status status = stub_->ReadAdministratorInfo(&context, request, &response);

        if (status.ok() && response.has_administrator()) {
            administrator = response.administrator();
        }

        return ErrorCode::NO_ERROR;
    }

    ErrorCode UpdateEmail(const std::string& table, const std::string& uni, const std::string& email) {
        UpdateEmailRequest request;
        request.set_table(table);
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
    std::string target_str("localhost:50052");
    PersonServiceClient client(grpc::CreateChannel(target_str, grpc::InsecureChannelCredentials()));
    return 0;
}