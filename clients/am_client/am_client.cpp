

#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>

#include "proto/am_proto/am.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using namespace std;
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
    auto identity = mysqlsvc.GetIdentity("hn2387", "123456");
    if (identity == Administrator) {
        cout << "Administrator" << endl;
    } else if (identity == Faculty) {
        cout << "Faculty" << endl;
    }
    else if (identity == Student) {
        cout << "Student" << endl;
    }
    else if (identity == Null) {
        cout << "Null" << endl;
    }

    identity = mysqlsvc.GetIdentity("hn2387", "swzy");
    if (identity == Administrator) {
        cout << "Administrator" << endl;
    } else if (identity == Faculty) {
        cout << "Faculty" << endl;
    }
    else if (identity == Student) {
        cout << "Student" << endl;
    }
    else if (identity == Null) {
        cout << "Null" << endl;
    }

    identity = mysqlsvc.GetIdentity("hn2387", "123456");
    if (identity == Administrator) {
        cout << "Administrator" << endl;
    } else if (identity == Faculty) {
        cout << "Faculty" << endl;
    }
    else if (identity == Student) {
        cout << "Student" << endl;
    }
    else if (identity == Null) {
        cout << "Null" << endl;
    }

    return 0;
}