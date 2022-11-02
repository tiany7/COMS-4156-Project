#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>
#include "httplib.h"
#include "proto/mysql_server_proto/faculty.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using std::vector;
using std::string;
class FacultyServiceClient {
public:
    FacultyServiceClient(std::shared_ptr<Channel> channel)
            : stub_(FacultyService::NewStub(channel)) {}

    vector<Faculty> GetFaculty(string dept) {
        GetFacultyReq request;
        request.set_department(dept);

        FacultyRsp reply;

        ClientContext context;

        Status status = stub_->GetFaculty(&context, request, &reply);

        if (status.ok()) {
            vector<Faculty>v;
            for(auto it : *reply.mutable_faculty()){
                v.push_back(it);
            }
            return v;
        } else {
            std::cout << status.error_code() << ": " << status.error_message()
                      << std::endl;
            return {};
        }
    }
    vector<Faculty> GetFacultyByUni(const string &uni) {
        GetFacultyReq request;
        request.set_uni(uni);

        FacultyRsp reply;

        ClientContext context;
        Status status = stub_->GetFacultyByUni(&context, request, &reply);

        if (status.ok()) {
            vector<Faculty>v;
            for(auto it : *reply.mutable_faculty()){
                v.push_back(it);
            }
            return v;
        } else {
            std::cout << status.error_code() << ": " << status.error_message()
                      << std::endl;
            return {};
        }
    }
    int InsertFaculty(const string &name, const string &dept, const string &uni, const string & country) {
        Faculty f;
        f.set_name(name);
        f.set_department(dept);
        f.set_uni(uni);
        f.set_country(country);

        Faculty reply;

        ClientContext context;

        Status status = stub_->InsertFaculty(&context, f, &reply);

        if (status.ok()) {
            return 0;
        } else {
            std::cout << status.error_code() << ": " << status.error_message()
                      << std::endl;
            return -1;
        }
    }
private:
    std::unique_ptr<FacultyService::Stub> stub_;
};

int main(int argc, char** argv) {
    FacultyServiceClient facultyServiceClient(grpc::CreateChannel(
            "localhost:50051", grpc::InsecureChannelCredentials()));

    httplib::Server svr;
    svr.Get("/search_dept", [&](const httplib::Request & req, httplib::Response &res) {
        auto param = req.get_param_value("department");
        vector<Faculty> v = facultyServiceClient.GetFaculty(param);
        std::ostringstream os;
        for(auto it : v){
            os << it.name()<<" | "<< it.department()<< " | "<<it.uni()<<" | "<<it.country()<< std::endl;
        }
        res.set_content(os.str().c_str(), "text/plain");
    });
    svr.Get("/search_uni", [&](const httplib::Request & req, httplib::Response &res) {
        auto body = req.get_param_value("uni");
        vector<Faculty> v = facultyServiceClient.GetFacultyByUni(body);
        std::ostringstream os;
        for(auto it : v){
            os << it.name()<<" | "<< it.department()<< " | "<<it.uni()<<" | "<<it.country()<< std::endl;
        }
        res.set_content(os.str().c_str(), "text/plain");
    });

    svr.Post("/add_instructor", [&](const httplib::Request & req, httplib::Response &res) {
        auto name = req.get_param_value("name");
        auto dept = req.get_param_value("dept");
        auto uni = req.get_param_value("uni");
        auto country = req.get_param_value("country");
        auto ret = facultyServiceClient.InsertFaculty(name, dept, uni, country);
        std::ostringstream os;
        os<<"Status: "<<ret<<std::endl;
        res.set_content(os.str().c_str(), "text/plain");
    });

    std::cout << "Server started" << std::endl;
    svr.listen("0.0.0.0", 8080);
    return 0;
}