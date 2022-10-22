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
    // Expect two strings not to be equal.
    MockFacultyServiceStub stub;
    EXPECT_CALL(stub, GetFaculty(_, _, _))
        .Times(1)
        .WillOnce(Invoke([](grpc::ClientContext* context, const GetFacultyReq* request, FacultyRsp* response) {
            int m = 20;
            while (m--) {
                auto faculty = response->add_faculty();
                //一定要用string封装一层！！！！不然会core！！！
                faculty->set_name(string("Yuanhan"));
                faculty->set_department(string("CS"));
                faculty->set_uni(string("BUAA"));
                faculty->set_country(string("China"));
            }
        return Status::OK;
    }));
    GetFacultyReq request;
    FacultyRsp reply;
    ClientContext context;
    Status status = stub.GetFaculty(&context, request, &reply);
    EXPECT_TRUE(status.ok());
    EXPECT_EQ(reply.faculty_size(), 20);
    
}

int main(int argc, char** argv) {
    // The following line must be executed to initialize Google Mock
    // (and Google Test) before running the tests.
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}