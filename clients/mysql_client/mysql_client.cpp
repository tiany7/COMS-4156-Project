

#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>

#include "proto/mysql_server_proto/faculty.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using namespace std;
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
    std::string target_str;
    std::string arg_str("--target");
    if (argc > 1) {
        std::string arg_val = argv[1];
        size_t start_pos = arg_val.find(arg_str);
        if (start_pos != std::string::npos) {
            start_pos += arg_str.size();
            if (arg_val[start_pos] == '=') {
                target_str = arg_val.substr(start_pos + 1);
            } else {
                std::cout << "The only correct argument syntax is --target="
                          << std::endl;
                return 0;
            }
        } else {
            std::cout << "The only acceptable argument is --target=" << std::endl;
            return 0;
        }
    } else {
        target_str = "localhost:50051";
    }
    FacultyServiceClient mysqlsvc(
            grpc::CreateChannel(target_str, grpc::InsecureChannelCredentials()));
    auto v = mysqlsvc.GetFaculty("CS");
    for(auto it : v){
        cout<<it.name()<<"|"<<it.department()<<"|"<<it.uni()<<"|"<<it.country()<<endl;
    }

    return 0;
}