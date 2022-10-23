#ifndef BUILDING_LIBRARY
#define BUILDING_LIBRARY
#include <stdlib.h>
#include <iostream>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include "mysql_connection.h"

#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include "proto/am_proto/am.grpc.pb.h"


using namespace std;
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

map<pair<string, string>, IdentityType> cache;

class dal{
public:
    sql::Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;
    sql::ResultSet *res;
    dal() :stmt(nullptr), res(nullptr) {
        driver = get_driver_instance();
        con = driver->connect("tcp://127.0.0.1:3306", "root", "");
        con->setSchema("coms4156_db");
    }

    void SetIdentity(const string & uni, const string & password, IdentityRsp* reply, IdentityType type) {
        if (res->getString(2) == password) {
            reply->set_identity(type);
            cache[make_pair(uni, password)] = type;
        } else {
            reply->set_identity(Null);
            cout << "Wrong Password!" << endl;
        }
    }

    int GetUserIdentity(const string & uni, const string & password, IdentityRsp* reply) {
        try {
            if (cache.count(make_pair(uni, password)) > 0) {
                reply->set_identity(cache[make_pair(uni, password)]);
                return 0;
            }

            IdentityType type = Administrator;
            stmt = con->createStatement();
            char buffer[100] = {0};
            string sql = "SELECT uni, password FROM administrator WHERE uni = '%s'";
            sprintf(buffer, sql.c_str(), uni.c_str());
            res = stmt->executeQuery(buffer);
            if (res->next()) {
                SetIdentity(uni, password, reply, type);
                return 0;
            }

            type = Faculty;
            stmt = con->createStatement();
            memset(buffer, 0, sizeof(buffer));
            sql = "SELECT uni, password FROM faculty WHERE uni = '%s'";
            sprintf(buffer, sql.c_str(), uni.c_str());
            res = stmt->executeQuery(buffer);
            if (res->next()) {
                SetIdentity(uni, password, reply, type);
                return 0;
            }

            type = Student;
            stmt = con->createStatement();
            memset(buffer, 0, sizeof(buffer));
            sql = "SELECT uni, password FROM student WHERE uni = '%s'";
            sprintf(buffer, sql.c_str(), uni.c_str());
            res = stmt->executeQuery(buffer);
            if (res->next()) {
                SetIdentity(uni, password, reply, type);
                return 0;
            }

            type = Null;
            reply->set_identity(type);

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
    ~dal() {
        if(res) delete res, res = nullptr;
        if(stmt)delete stmt, stmt = nullptr;
        if(con) delete con, con = nullptr;
    }
};
class IdentityServiceServiceImpl final: public IdentityService::Service {
    Status GetIdentity(ServerContext* context, const GetIdentityReq* request,
                      IdentityRsp* reply) {
        // const auto clientMetadata = context->client_metadata();
        // for (auto x : clientMetadata) {
        //     cout << x.first << ": " << x.second << endl;
        // }
        auto uni = request->uni();
        cout<<uni<<endl;
        auto password = request->password();
        int success = dal().GetUserIdentity(uni, password, reply);
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
        IdentityServiceServiceImpl service;

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
    server.bind_address("localhost", 10086);
    server.Run();
    return 0;
}

#endif