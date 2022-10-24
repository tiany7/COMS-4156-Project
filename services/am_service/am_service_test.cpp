#include <gtest/gtest.h>
#include "proto/am_proto/am_mock.grpc.pb.h"
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
    MockIdentityServiceStub stub;
    GetIdentityReq request;
    IdentityRsp reply;
    ClientContext context;
    auto f = [](::grpc::ClientContext* context, const ::GetIdentityReq& request, ::IdentityRsp* response){
        response->set_identity(Faculty);
        return Status::OK;
    };
    EXPECT_CALL(stub, GetIdentity)
    .WillRepeatedly(DoAll(Invoke(f), Return(Status::OK)));
    stub.GetIdentity(&context, request, &reply);
    EXPECT_EQ(reply.identity(), Faculty);

}

TEST(TestMySQLServer, ErrorCodeCheck) {
    MockIdentityServiceStub stub;
    GetIdentityReq request;
    IdentityRsp reply;
    ClientContext context;
    stub.GetIdentity(&context, request, &reply);
    auto ret = stub.GetIdentity(&context, request, &reply);
    EXPECT_EQ(ret.error_code(), grpc::StatusCode::OK);
}



int main(int argc, char** argv) {
    // The following line must be executed to initialize Google Mock
    // (and Google Test) before running the tests.
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}