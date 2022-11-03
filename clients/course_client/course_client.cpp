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

    int GetCoursePrereq(const string& course) {
        GetCoursePrereqRequest request;
        request.set_course(course);
        CoursePrereqResponse reply;
        ClientContext context;
        Status status = stub_->GetCoursePrereq(&context, request, &reply);
        
        if (status.ok()) {
            std::cout << "OK in line 97\n";
            std::cout << reply.pre1() << std::endl;
            std::cout << reply.pre2() << std::endl;
            std::cout << reply.pre3() << std::endl;
            return 1;
        } else {
            std::cout << " Got error here in 34\n";
            std::cout << status.error_code() << ": " << status.error_message()
                      << std::endl;
            return -1;
        }
    }

    void InsertCourse(const string& course, const string& semester, const string& course_title,
            const int32_t cid){
        InsertCourseRequest request;
        request.set_course(course);
        request.set_semester(semester);
        request.set_course_title(course_title);
        request.set_cid(cid);
        CRUDCourseResponse reply;
        ClientContext context;
        std::cout << "Insert enter 120\n";
        Status status = stub_->InsertCourse(&context, request, &reply);
        // db success but status fail !
        std::cout << reply.message() << std::endl;
        if (status.ok()) {
            std::cout << "OK in line 82\n";
            return;
        } else {
            std::cout << " Got error here in 34***\n"; // 
            std::cout << status.error_code() << ": " << status.error_message()
                      << std::endl;
            return;
        }
    }

    void UpdateCourse(const string& course, const string& semester, const string& course_title,
            const string& faculty_name, const string& faculty_uni){
        UpdateCourseRequest request;
        request.set_course(course);
        request.set_semester(semester);
        request.set_course_title(course_title);
        request.set_faculty_name(faculty_name);
        request.set_faculty_uni(faculty_uni);
        CRUDCourseResponse reply;
        ClientContext context;
        Status status = stub_->UpdateCourse(&context, request, &reply);
        std::cout << reply.message() << std::endl;
        if (status.ok()) {
            std::cout << "OK in line 82\n";
            return;
        } else {
            std::cout << " Got error here in 34\n"; // 
            std::cout << status.error_code() << ": " << status.error_message()
                      << std::endl;
            return;
        }
    }

    void DeleteCourse(const int32_t cid, const string& semester){
        DeleteCourseRequest request;
        request.set_cid(cid);
        request.set_semester(semester);
        CRUDCourseResponse reply;
        ClientContext context;
        Status status = stub_->DeleteCourse(&context, request, &reply);
        std::cout << reply.message() << std::endl;
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


    // auto title = mysqlsvc.GetTitle("cs4156", "2022Fall");
    // std::cout  << title << std::endl;


    auto coursetitle = mysqlsvc.GetCourse(1111, "2022Fall");
    if (coursetitle == "Adv Software Eng") {
        cout << "Success" << endl;
    } else {
        cout << "Fail" << endl;
    }

    // auto num = mysqlsvc.GetCourseList("CS","2022Fall");
    // std::cout << num << std::endl;

    // these two will be further implemented
    // auto num = mysqlsvc.GetCoursePrereq("cs4156");
    // std::cout << num << std::endl;

    // insert try
    mysqlsvc.InsertCourse("cs7000","2022Fall","Ultra Software",777);

    // update try
    mysqlsvc.UpdateCourse("cs4156","2022Fall","Adv Software III","Jojo Smith","js1234");

    // 删掉了但会有 segmentation fault
    // mysqlsvc.DeleteCourse(111,"2022Spring");

    return 0;
}
