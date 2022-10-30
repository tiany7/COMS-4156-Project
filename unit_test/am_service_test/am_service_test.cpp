#include <gtest/gtest.h>
#include "proto/am_proto/am_mock.grpc.pb.h"
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using namespace testing;

class FakeClient {
public:
    explicit FakeClient(IdentityService::StubInterface* stub) : stub_(stub) {}

    void DoGetIdentity() {
        ClientContext context;
        GetIdentityReq request;
        IdentityRsp reply;
        request.set_uni("hn2387");
        request.set_password("123456");
        Status status = stub_->GetIdentity(&context, request, &reply);
        EXPECT_TRUE(status.ok());
        EXPECT_EQ(reply.identity(), Student);
    }

private:
    IdentityService::StubInterface* stub_;
};

TEST(MockIdentityService, CheckGetIdentity) {
    MockIdentityServiceStub stub;
    IdentityRsp reply;
    reply.set_identity(Student);
    EXPECT_CALL(stub, GetIdentity(_, _, _)).Times(1).WillOnce(DoAll(SetArgumentPointee<2>(reply), Return(Status::OK)));
    FakeClient client(&stub);
    client.DoGetIdentity();
}

int main(int argc, char** argv) {
    // The following line must be executed to initialize Google Mock
    // (and Google Test) before running the tests.
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}