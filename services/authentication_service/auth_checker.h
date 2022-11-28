#include <grpcpp/grpcpp.h>

#include "proto/authentication_proto/login.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

class AuthServiceClient {
public:
    AuthServiceClient(std::shared_ptr<Channel> channel)
            : stub_(AuthService::NewStub(channel)) {}

    bool CheckSecret(const std::string &username, const std::string &secret)
    {
        CheckValidRequest request;
        CheckValidResponse response;
        ClientContext context;
        request.mutable_user()->set_username(username);
        request.mutable_user()->set_token(secret);
        Status status = stub_->CheckValid(&context, request, &response);
        if (status.ok()) {
            return response.valid();
        } else {
            std::cout << status.error_code() << ": " << status.error_message()
                      << std::endl;
            return false;
        }
    }

    bool IsLoggedIn(const std::string &username)
    {
        CheckValidRequest request;
        CheckValidResponse response;
        ClientContext context;
        request.mutable_user()->set_username(username);
        Status status = stub_->IsLoggedIn(&context, request, &response);
        if (status.ok()) {
            return response.valid();
        } else {
            std::cout << status.error_code() << ": " << status.error_message()
                      << std::endl;
            return false;
        }
    }

private:
    std::unique_ptr<AuthService::Stub> stub_;
};