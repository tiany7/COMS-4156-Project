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

    string GetTitle(const string& course, const string& semester){ // check whether & is ok
        GetCourseTitleRequest request;
        request.set_course(course);
        request.set_semester(semester);

        CourseTitleResponse reply;

        ClientContext context;

        Status status = stub_->GetCourseTitle(&context, request, &reply); // error here

        std::cout << " get the func back in server\n";
        if (status.ok()) {
            std::cout << "OK in line 30\n";
            auto coursetitle = reply.course_title();
            return coursetitle;
        } else {
            std::cout << " Got error here in 34\n";
            std::cout << status.error_code() << ": " << status.error_message()
                      << std::endl;
            return nullptr;
        }
    }
    string GetCourse(const int32_t cid, const string& semester) {
        GetCourseInfoRequest request;
        request.set_cid(cid);
        request.set_semester(semester);

        CourseInfoResponse reply;
        ClientContext context;

        Status status = stub_->GetCourseInfo(&context, request, &reply);

        std::cout << " get the func back in server\n";
        if (status.ok()) {
            std::cout << "OK in line 30\n";
            auto coursetitle = reply.course().course_title();
            // std::cout << reply.course().semester()<< std::endl;
            // std::cout << reply.course().course()<< std::endl;
            // std::cout << reply.course().course_title()<< std::endl;
            // std::cout << reply.course().course_id()<< std::endl;
            // std::cout << reply.course().faculty_name()<< std::endl;
            // std::cout << reply.course().prereq1()<< std::endl;
            // std::cout << reply.course().prereq2()<< std::endl;
            // std::cout << reply.course().prereq3()<< std::endl;
            return coursetitle;
        } else {
            std::cout << " Got error here in 34\n";
            std::cout << status.error_code() << ": " << status.error_message()
                      << std::endl;
            return nullptr;
        }
    }

    int GetCourseList(const string& department, const string& semester) {
        GetCourseListRequest request;
        request.set_department(department);
        request.set_semester(semester);
        CourseListResponse reply;
        ClientContext context;
        Status status = stub_->GetCourseList(&context, request, &reply);
        if (status.ok()) {
            std::cout << "OK in line 82\n";
            return reply.course_size();
        } else {
            std::cout << " Got error here in 34\n";
            std::cout << status.error_code() << ": " << status.error_message()
                      << std::endl;
            return -1;
        }
    }

    // int GetCoursePrereq(const string& course) {
    //     GetCoursePrereqRequest request;
    //     request.set_course(course);
    //     CoursePrereqResponse reply;
    //     ClientContext context;
    //     Status status = stub_->GetCoursePrereq(&context, request, &reply);
    //     if (status.ok()) {
    //         std::cout << "OK in line 97\n";
    //         std::cout << reply.course_size() << std::endl;
    //         std::cout << reply.course()[0] << std::endl;
    //         std::cout << reply.course()[1] << std::endl;
    //         std::cout << reply.course()[2] << std::endl;
    //         // use for instead in real application
    //         return reply.course_size();
    //     } else {
    //         std::cout << " Got error here in 34\n";
    //         std::cout << status.error_code() << ": " << status.error_message()
    //                   << std::endl;
    //         return -1;
    //     }
    // }

    void DeleteCourse(const int32_t cid, const string& semester){
        DeleteCourseRequest request;
        request.set_cid(cid);
        request.set_semester(semester);
        DeleteCourseResponse reply;
        ClientContext context;
        Status status = stub_->DeleteCourse(&context, request, &reply);
        if (status.ok()) {
            std::cout << "OK in line 82\n";
            return;
        } else {
            std::cout << " Got error here in 34\n";
            std::cout << status.error_code() << ": " << status.error_message()
                      << std::endl;
            return;
        }

    }

private:
    std::unique_ptr<CourseService::Stub> stub_;
};

int main(int argc, char** argv) {
    CourseServiceClient mysqlsvc(
            grpc::CreateChannel("localhost:50053", grpc::InsecureChannelCredentials()));
    std::cout << "client enter line 46\n";
    auto title = mysqlsvc.GetTitle("cs4156", "2022Fall");
    std::cout  << title << std::endl;
    auto coursetitle = mysqlsvc.GetCourse(1111, "2022Fall");
    if (coursetitle == "Adv Software") {
        cout << "Success" << endl;
    } else {
        cout << "Fail" << endl;
    }

    auto num = mysqlsvc.GetCourseList("CS","2022Fall");
    std::cout << num << std::endl;

    // these two will be further implemented
    // auto num = mysqlsvc.GetCoursePrereq("cs4156");
    // mysqlsvc.DeleteCourse(111,"2022Spring");

    return 0;
}
