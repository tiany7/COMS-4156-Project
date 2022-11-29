#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#include <stdlib.h>

#include <iostream>

#include "login.h"
#include "proto/authentication_proto/login.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

class AuthServiceImpl final : public AuthService::Service {
  Status CheckValid(ServerContext* context, const CheckValidRequest* request,
                    CheckValidResponse* response) override {
    std::cout << "CheckValid" << std::endl;
    Login login;
    auto secret = request->user().token();
    auto username = request->user().username();
    if (login.IsLegalOperator(username, secret)) {
      response->set_valid(true);
    } else {
      response->set_valid(false);
    }
    return Status::OK;
  }

  Status IsLoggedIn(ServerContext* context, const CheckValidRequest* request,
                    CheckValidResponse* response) override {
    std::cout << "CheckValid" << std::endl;
    Login login;
    auto username = request->user().username();
    if (login.IsLoggedIn(username)) {
      response->set_valid(true);
    } else {
      response->set_valid(false);
    }
    return Status::OK;
  }
};

int main(int argc, char** argv) {
  std::string server_address("localhost:95955");
  AuthServiceImpl service;

  grpc::EnableDefaultHealthCheckService(true);
  grpc::reflection::InitProtoReflectionServerBuilderPlugin();
  grpc::ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;
  server->Wait();
  return 0;
}