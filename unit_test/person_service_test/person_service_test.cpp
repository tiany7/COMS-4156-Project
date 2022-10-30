#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>

#include "proto/person_proto/person_mock.grpc.pb.h"
#include "proto/person_proto/person.grpc.pb.h"

using ::testing::_;
using ::testing::AtLeast;
using ::testing::DoAll;
using ::testing::Return;
using ::testing::SaveArg;
using ::testing::SetArgPointee;
using ::testing::SetArgumentPointee;
using ::testing::WithArg;
using ::grpc::Status;
using ::grpc::ClientContext;
using grpc::Channel;

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
using ::person::MockPersonServiceStub;

class FakeClient {
public:
    explicit FakeClient(PersonService::StubInterface* stub) : stub_(stub) {}

    void DoReadStudentInfo() {
        ClientContext context;
        StudentReadRequest request;
        StudentReadResponse response;
        request.set_table("student");
        request.set_uni("qw1234");
        Status status = stub_->ReadStudentInfo(&context, request, &response);
        EXPECT_TRUE(status.ok());
        EXPECT_TRUE(response.has_student());
        const Student& student = response.student();
        EXPECT_EQ(student.uni(), "qw1234");
        EXPECT_EQ(student.name(), "Alex");
        EXPECT_EQ(student.email(), "qw1234@columbia.edu");
        EXPECT_EQ(student.affiliation(), "Computer Science");
        EXPECT_EQ(student.school(), "SEAS");
        EXPECT_EQ(student.advisor(), "None on file");
    }
    
    void DoReadStudentInfoFailed() {
        ClientContext context;
        StudentReadRequest request;
        StudentReadResponse response;
        request.set_table("student");
        request.set_uni("qw1234");
        Status status = stub_->ReadStudentInfo(&context, request, &response);
        EXPECT_FALSE(response.has_student());
        EXPECT_EQ(response.message(), "ERROR");
        EXPECT_EQ(status.error_code(), grpc::StatusCode::OK);
        EXPECT_EQ(status.error_message(), "Read student info failed!");
    }

    void DoReadFacultyInfo() {
        ClientContext context;
        FacultyReadRequest request;
        FacultyReadResponse response;
        request.set_table("faculty");
        request.set_uni("as1234");
        Status status = stub_->ReadFacultyInfo(&context, request, &response);
        EXPECT_TRUE(status.ok());
        EXPECT_TRUE(response.has_faculty());
        const Faculty& faculty = response.faculty();
        EXPECT_EQ(faculty.uni(), "as1234");
        EXPECT_EQ(faculty.name(), "Bob");
        EXPECT_EQ(faculty.email(), "as1234@columbia.edu");
        EXPECT_EQ(faculty.school(), "SEAS");
    }

    void DoReadAdministratorInfo() {
        ClientContext context;
        AdministratorReadRequest request;
        AdministratorReadResponse response;
        request.set_table("administrator");
        request.set_uni("zx1234");
        Status status = stub_->ReadAdministratorInfo(&context, request, &response);
        EXPECT_TRUE(status.ok());
        EXPECT_TRUE(response.has_administrator());
        const Administrator& administrator = response.administrator();
        EXPECT_EQ(administrator.uni(), "zx1234");
        EXPECT_EQ(administrator.name(), "Mat");
        EXPECT_EQ(administrator.email(), "zx1234@columbia.edu");
    }

    void DoUpdateEmail() {
        ClientContext context;
        UpdateEmailRequest request;
        UpdateEmailResponse response;
        request.set_table("student");
        request.set_uni("qw1234");
        request.set_email("qw5678@columbia.edu");
        Status status = stub_->UpdateEmail(&context, request, &response);
        EXPECT_TRUE(status.ok());
        EXPECT_EQ(request.email(), response.email());
    }

private:
    PersonService::StubInterface* stub_;
};

TEST(MockPersonService, CheckReadStudentInfo) {
    MockPersonServiceStub stub;
    StudentReadResponse response;
    Student* student = response.mutable_student();
    student->set_uni("qw1234");
    student->set_name("Alex");
    student->set_email("qw1234@columbia.edu");
    student->set_affiliation("Computer Science");
    student->set_school("SEAS");
    student->set_advisor("None on file");
    EXPECT_CALL(stub, ReadStudentInfo(_, _, _)).Times(1).WillOnce(DoAll(SetArgumentPointee<2>(response), Return(Status::OK)));
    FakeClient client(&stub);
    client.DoReadStudentInfo();
}


TEST(MockPersonService, CheckReadStudentInfoFailed) {
    MockPersonServiceStub stub;
    StudentReadResponse response;
    response.set_message("ERROR");
    EXPECT_CALL(stub, ReadStudentInfo(_, _, _)).Times(1).WillOnce(DoAll(SetArgumentPointee<2>(response), Return(Status::OK)));
    FakeClient client(&stub);
    client.DoReadStudentInfoFailed();
}

TEST(MockPersonService, CheckReadFacultyInfo) {
    MockPersonServiceStub stub;
    FacultyReadResponse response;
    Faculty* faculty = response.mutable_faculty();
    faculty->set_uni("as1234");
    faculty->set_name("Bob");
    faculty->set_email("as1234@columbia.edu");
    faculty->set_school("SEAS");
    EXPECT_CALL(stub, ReadFacultyInfo(_, _, _)).Times(1).WillOnce(DoAll(SetArgumentPointee<2>(response), Return(Status::OK)));
    FakeClient client(&stub);
    client.DoReadFacultyInfo();
}

TEST(MockPersonService, CheckReadAdministratorInfo) {
    MockPersonServiceStub stub;
    AdministratorReadResponse response;
    Administrator* administrator = response.mutable_administrator();
    administrator->set_uni("zx1234");
    administrator->set_name("Mat");
    administrator->set_email("zx1234@columbia.edu");
    EXPECT_CALL(stub, ReadAdministratorInfo(_, _, _)).Times(1).WillOnce(DoAll(SetArgumentPointee<2>(response), Return(Status::OK)));
    FakeClient client(&stub);
    client.DoReadAdministratorInfo();
}

TEST(MockPersonService, CheckUpdateEmail) {
    MockPersonServiceStub stub;
    UpdateEmailResponse response;
    response.set_email("qw5678@columbia.edu");
    EXPECT_CALL(stub, UpdateEmail(_, _, _)).Times(1).WillOnce(DoAll(SetArgumentPointee<2>(response), Return(Status::OK)));
    FakeClient client(&stub);
    client.DoUpdateEmail();
}

int main(int argc, char** argv) {
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}




