#include <gtest/gtest.h>
#include "proto/mysql_server_proto/faculty_mock.grpc.pb.h"
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <string>
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using namespace testing;
using std::string;
TEST(HelloTest, PP) {
    // Expect two strings not to be equal.
    EXPECT_STRNE("hello", "world");
    // Expect equality.
    EXPECT_EQ(7 * 6, 42);
}

TEST(TestMysqlClient, CanSearch) {
    MockFacultyServiceStub stub;
    GetFacultyReq request;
    FacultyRsp reply;
    ClientContext context;
    auto f = [](::grpc::ClientContext* context, const ::GetFacultyReq& request, ::FacultyRsp* response){
        for(int i = 4; i--;){
            auto it = response->add_faculty();
            it->set_name("Yuanhan");
            it->set_department("CS");
            it->set_uni("yt2825");
            it->set_country("China");
        }
        return Status::OK;
    };
    EXPECT_CALL(stub, GetFaculty)
    .WillRepeatedly(DoAll(Invoke(f), Return(Status::OK)));
    stub.GetFaculty(&context, request, &reply);
    EXPECT_EQ(reply.faculty_size(), 4);
    for(auto it : *reply.mutable_faculty()){
        EXPECT_EQ(it.name(), "Yuanhan");
        EXPECT_EQ(it.department(), "CS");
        EXPECT_EQ(it.uni(), "yt2825");
        EXPECT_EQ(it.country(), "China");
    }

}

TEST(TestMySQLServer, ErrorCodeCheck) {
    MockFacultyServiceStub stub;
    GetFacultyReq request;
    FacultyRsp reply;
    ClientContext context;
    stub.GetFaculty(&context, request, &reply);
    auto ret = stub.GetFaculty(&context, request, &reply);
    EXPECT_EQ(ret.error_code(), grpc::StatusCode::OK);
}



int main(int argc, char** argv) {
    // The following line must be executed to initialize Google Mock
    // (and Google Test) before running the tests.
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}