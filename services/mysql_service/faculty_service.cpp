#ifndef BUILDING_LIBRARY
#define BUILDING_LIBRARY
#include <stdlib.h>
#include <iostream>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <mysql_connection.h>

#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include "proto/mysql_server_proto/faculty.grpc.pb.h"


using namespace std;
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

class DB{
public:
    DB(const string &schema = "faculty") {
        driver = get_driver_instance();
        con = driver->connect("tcp://127.0.0.1:3306", "root", "");
        con->setSchema(schema.c_str());
    }
    sql::Connection* operator->() {
        return con;
    }
    virtual ~DB() {
        if(con) delete con, con = nullptr;
    }
protected:
    sql::Driver *driver;
    sql::Connection *con;
};

class FacultyDBService : public DB{
public:
    FacultyDBService():DB("faculty"){}
    int GetFacultyDept(const string & dept_name, FacultyRsp* reply) {
    try {
        auto stmt = con->createStatement();
        char buffer[105] = {0};
        string sql = "SELECT * FROM faculty WHERE department = '%s'";
        sprintf(buffer, sql.c_str(), dept_name.c_str());
        auto res = stmt->executeQuery(buffer);
        while (res->next()) {
            cout<<string(res->getString(1))<<endl;
            auto faculty = reply->add_faculty();
            //一定要用string封装一层！！！！不然会core！！！
            faculty->set_name(string(res->getString(1)));
            faculty->set_department(string(res->getString(2)));
            faculty->set_uni(string(res->getString(3)));
            faculty->set_country(string(res->getString(4)));
        }
        if(res)delete res, res = nullptr;\
        if(stmt)delete stmt, stmt = nullptr;
    }catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line "
             << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
    return 0;
}
};

class FacultyServiceServiceImpl final: public FacultyService::Service {
    Status GetFaculty(ServerContext* context, const GetFacultyReq* request,
                      FacultyRsp* reply) {
        auto dept = request->department();
        int success = FacultyDBService().GetFacultyDept(dept, reply);
        cout<<"Send Back"<<endl;
        return Status::OK;
    }
};

class MysqlServer{
public:
    void bind_address(string addr, int port) {
        address = addr + ":" + to_string(port);
    }
    void Run() {
        FacultyServiceServiceImpl service;

        grpc::EnableDefaultHealthCheckService(true);
        ServerBuilder builder;
        builder.AddListeningPort(address, grpc::InsecureServerCredentials());
        builder.RegisterService(&service);
        std::unique_ptr<Server> server(builder.BuildAndStart());

        server->Wait();
    }
private:
    string address;
};

int main(void)
{
    MysqlServer server;
    server.bind_address("localhost", 50051);
    server.Run();
    return 0;
}

#endif