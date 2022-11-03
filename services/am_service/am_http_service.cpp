#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>
#include "httplib.h"
#include "proto/am_proto/am.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using namespace std;

string getIdentityStr(IdentityType identity) {
    if (identity == Administrator) {
        return "Administrator";
    } else if (identity == Faculty) {
        return "Faculty";
    } else if (identity == Student) {
        return "Student";
    } else if (identity == Null) {
        return "Null";
    }
    return "";
}

class IdentityServiceClient {
public:
    IdentityServiceClient(std::shared_ptr<Channel> channel)
            : stub_(IdentityService::NewStub(channel)) {}

   IdentityType GetIdentity(string uni, string password) {
        GetIdentityReq request;
        request.set_uni(uni);
        request.set_password(password);

        IdentityRsp reply;

        ClientContext context;

        Status status = stub_->GetIdentity(&context, request, &reply);

        if (status.ok()) {
            auto identity = reply.identity();
            return identity;
        } else {
            std::cout << status.error_code() << ": " << status.error_message()
                      << std::endl;
            return Null;
        }
    }

private:
    std::unique_ptr<IdentityService::Stub> stub_;
};

int main(int argc, char** argv) {
    IdentityServiceClient mysqlsvc(
            grpc::CreateChannel("localhost:10086", grpc::InsecureChannelCredentials()));
    httplib::Server svr;
    svr.Get("/am", [&](const httplib::Request & req, httplib::Response &res) {
        std::ostringstream os;
        auto uni = req.get_param_value("uni");
        auto password = req.get_param_value("password");
        auto identity = mysqlsvc.GetIdentity(uni, password);
        os << getIdentityStr(identity) << endl;
        res.set_content(os.str().c_str(), "text/plain");
    });
    std::cout << "Server started" << std::endl;
    svr.listen("0.0.0.0", 8080);
    return 0;
}