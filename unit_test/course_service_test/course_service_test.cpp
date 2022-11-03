#include <gtest/gtest.h>
#include "proto/course_proto/course_mock.grpc.pb.h"
#include "proto/course_proto/course.grpc.pb.h"
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


class FakeClient {
public:
    explicit FakeClient(CourseService::StubInterface* stub) : stub_(stub) {}

    void DoGetCourseInfo() {
        ClientContext context;
        GetCourseInfoRequest request;
        CourseInfoResponse reply;

        request.set_cid(1111);
        request.set_semester("2022Fall");

        Status status = stub_->GetCourseInfo(&context, request, &reply);
        EXPECT_TRUE(status.ok());
        EXPECT_EQ(reply.course().course_title(), "Adv Software");
    }

private:
    CourseService::StubInterface* stub_;
};

TEST(MockCourseService, CheckGetCourseInfo) {
    MockCourseServiceStub stub;
    // GetCourseInfoRequest request;
    CourseInfoResponse response;
    // ClientContext context;
    CourseInfo* cs4156 = response.mutable_course();
    // reply.set_identity(Course4156);
    cs4156->set_course("cs4156");
    cs4156->set_course_id("1111");
    cs4156->set_course_title("Adv Software");
    cs4156->set_department("CS");
    cs4156->set_faculty_name("BOB");
    cs4156->set_faculty_uni("bb1111");
    cs4156->set_prereq1("CS2000");
    // cs4156->set_prereq2("");
    // cs4156->set_prereq3();
    cs4156->set_semester("2022Fall");
    
    EXPECT_CALL(stub, GetCourseInfo(_,_,_)).Times(1).WillOnce(DoAll(SetArgumentPointee<2>(response), Return(Status::OK)));
    FakeClient client(&stub);
    client.DoGetCourseInfo();

}

// TEST(TestMySQLServer, ErrorCodeCheck) {
//     MockIdentityServiceStub stub;
//     GetIdentityReq request;
//     IdentityRsp reply;
//     ClientContext context;
//     stub.GetIdentity(&context, request, &reply);
//     auto ret = stub.GetIdentity(&context, request, &reply);
//     EXPECT_EQ(ret.error_code(), grpc::StatusCode::OK);
// }



int main(int argc, char** argv) {
    // The following line must be executed to initialize Google Mock
    // (and Google Test) before running the tests.
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}