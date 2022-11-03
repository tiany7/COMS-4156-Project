#include "mysql_server.hh"

void MysqlServer::Run()
{
    TimeServiceImpl service;

    grpc::EnableDefaultHealthCheckService(true);
    ServerBuilder builder;
    builder.AddListeningPort(address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<Server> server(builder.BuildAndStart());

    server->Wait();
}