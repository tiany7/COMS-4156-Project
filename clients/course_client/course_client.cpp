


#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>

#include "proto/course_proto/course.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using namespace std;
class CourseServiceClient {
public:
    CourseServiceClient(std::shared_ptr<Channel> channel)
            : stub_(CourseService::NewStub(channel)) {}

    string GetCourse(const int32_t cid, const string semester) {
        GetCourseInfoRequest request;
        request.set_cid(cid);
        request.set_semester(semester);

        CourseInfoResponse reply;

        ClientContext context;

        Status status = stub_->GetCourseInfo(&context, request, &reply);

        if (status.ok()) {
            auto coursetitle = reply.course().course_title();
            return coursetitle;
        } else {
            std::cout << status.error_code() << ": " << status.error_message()
                      << std::endl;
            return nullptr;
        }
    }

private:
    std::unique_ptr<CourseService::Stub> stub_;
};

int main(int argc, char** argv) {
    CourseServiceClient mysqlsvc(
            grpc::CreateChannel("localhost:10086", grpc::InsecureChannelCredentials()));
    auto coursetitle = mysqlsvc.GetCourse(12397, "2022Fall");

    if (coursetitle == "Adv Software Engineering") {
        cout << "Success" << endl;
    } else {
        cout << "Fail" << endl;
    }

    return 0;
}
