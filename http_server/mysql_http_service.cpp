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

private:
    std::unique_ptr<FacultyService::Stub> stub_;
};

int main(int argc, char** argv) {
    FacultyServiceClient facultyServiceClient(grpc::CreateChannel(
            "localhost:50051", grpc::InsecureChannelCredentials()));
    vector<Faculty> v = facultyServiceClient.GetFaculty("CS");
    std::ostringstream os;
    for(int i = 1; i <= 4; ++i){
        for(auto it : v){
            std::cout << it.name() << std::endl;
            os << it.name()<<" | "<< it.department()<< " | "<<it.uni()<<" | "<<it.country()<< std::endl;
        }
    }
    httplib::Server svr;
    svr.Get("/query_sql", [&](const httplib::Request & /*req*/, httplib::Response &res) {
        res.set_content(os.str().c_str(), "text/plain");
    });
    svr.Post("/query_sql", [&](const httplib::Request & req, httplib::Response &res) {
        auto body = req.get_param_value("person");
        os<< body<<std::endl;
        res.set_content(os.str().c_str(), "text/plain");
    });
    std::cout << "Server started" << std::endl;
    svr.listen("0.0.0.0", 8080);
    return 0;
}