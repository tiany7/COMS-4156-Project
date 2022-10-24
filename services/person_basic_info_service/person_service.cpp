
#include <iostream>
#include <memory>
#include <string>
#include <utility>

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#include "proto/person_proto/person.grpc.pb.h"

#define BUFFER_SIZE 256

using ::std::string;
using ::person::PersonService;
using ::person::StudentReadRequest;
using ::person::StudentReadResponse;
using ::person::FacultyReadRequest;
using ::person::FacultyReadResponse;
using ::person::AdministratorReadRequest;
using ::person::AdministratorReadResponse;
using ::person::UpdateEmailRequest;
using ::person::UpdateEmailResponse;

using ::grpc::ServerBuilder;
using ::grpc::ServerContext;
using ::grpc::Status;

enum ErrorCode {
    NO_ERROR = 0,
    ERROR = 1,
};

class PersonDB {
public:
    PersonDB() {
        driver = get_driver_instance();
        con = driver->connect("tcp://127.0.0.1:3306", "root", "");
        con->setSchema("enrollment"); // change schema name
    }

    ErrorCode execute(const std::string& query) {
        try {
            stmt = con->createStatement();
            res = stmt->executeQuery(query);
        } catch(sql::SQLException &e) {
            return ErrorCode::ERROR;
        }

        return ErrorCode::NO_ERROR;
    }

    ErrorCode GetStudentInfo(const std::string &table, const std::string& uni, StudentReadResponse* response) {
        char buffer[BUFFER_SIZE] = {0};
        string sql = "SELECT * from " + table + " WHERE uni='%s'";
        sprintf(buffer, sql.c_str(), uni.c_str());
        ErrorCode sql_error_code = execute(string(buffer));
        if (sql_error_code == ErrorCode::ERROR) {
            return sql_error_code;
        }

        while (res->next()) {
            response->set_uni(string(res->getString(1)));
            response->set_name(string(res->getString(2)));
            response->set_email(string(res->getString(3)));
            response->set_affiliation(string(res->getString(4)));
            response->set_school(string(res->getString(5)));
            response->set_advisor(string(res->getString(6)));
        }
        return ErrorCode::NO_ERROR;
    }

    ErrorCode GetFacultyInfo(const std::string& table, const std::string& uni, FacultyReadResponse* response) {
        char buffer[BUFFER_SIZE] = {0};
        string sql = "SELECT * from " + table + " WHERE uni='%s'";
        sprintf(buffer, sql.c_str(), uni.c_str());
        ErrorCode sql_error_code = execute(string(buffer));
        if (sql_error_code == ErrorCode::ERROR) {
            return sql_error_code;
        }

        while (res->next()) {
            response->set_uni(string(res->getString(1)));
            response->set_name(string(res->getString(2)));
            response->set_email(string(res->getString(3)));
            response->set_school(string(res->getString(4)));
        }
        return ErrorCode::NO_ERROR;
    }

    ErrorCode GetAdministratorInfo(const std::string& table, const std::string& uni, AdministratorReadResponse* response) {
        char buffer[BUFFER_SIZE] = {0};
        string sql = "SELECT * from " + table + " WHERE uni='%s'";
        sprintf(buffer, sql.c_str(), uni.c_str());
        ErrorCode sql_error_code = execute(string(buffer));
        if (sql_error_code == ErrorCode::ERROR) {
            return sql_error_code;
        }

        while (res->next()) {
            response->set_uni(string(res->getString(1)));
            response->set_name(string(res->getString(2)));
            response->set_email(string(res->getString(3)));
        }
        return ErrorCode::NO_ERROR;
    }

    ErrorCode UpdateEmail(const std::string& table, const std::string& uni, const std::string& email, UpdateEmailResponse* response) {
        char buffer[BUFFER_SIZE] = {0};
        string sql = "UPDATE " + table + " SET email='%s' WHERE uni='%s'";
        sprintf(buffer, sql.c_str(), email.c_str(), uni.c_str());
        ErrorCode sql_error_code = execute(string(buffer));
        if (sql_error_code == ErrorCode::ERROR) {
            response->set_message("UPDATE FAILED!")
            return sql_error_code;
        }
        response->set_message("UPDATE SUCCESS!")
        return ErrorCode::NO_ERROR;
    }

    ~PersonDB() {
        if (con) {
            delete con;
            con = nullptr;
        }
        if (stmt) {
            delete stmt;
            stmt = nullptr;
        }
        if (res) {
            delete res;
            res = nullptr;
        }
    }

private:
    sql::Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;
    sql::ResultSet *res;
};

class PersonServiceImpl final : public PersonService::Service {
    Status ReadStudentInfo(ServerContext* context, const StudentReadRequest* request, StudentReadResponse* response) override {
        ErrorCode error_code = PersonDB().GetStudentInfo(request->table(), request->uni(), response);
        if (error_code == ErrorCode::ERROR) {
            return Status::UNKNOWN;
        }
        return Status::OK;
    }

    Status ReadFacultyInfo(ServerContext* context, FacultyReadRequest* request, FacultyReadResponse* response) override {
        ErrorCode error_code = PersonDB().GetGetFacultyInfo(request->table(), request->uni(), response);
        if (error_code == ErrorCode::ERROR) {
            return Status::UNKNOWN;
        }
        return Status::OK;
    }

    Status ReadAdministratorInfo(ServerContext* context, AdministratorReadRequest* request, AdministratorReadResponse* response) override {
        ErrorCode error_code = PersonDB().GetAdministratorInfo(request->table(), request->uni(), response);
        if (error_code == ErrorCode::ERROR) {
            return Status::UNKNOWN;
        }
        return Status::OK;
    }

    Status UpdateEmail(ServerContext* context, UpdateEmailRequest* request, UpdateEmailResponse* response) override {
        ErrorCode error_code = PersonDB().UpdateEmail(request->table(), request->uni(), request->email(),response);
        if (error_code == ErrorCode::ERROR) {
            return Status::UNKNOWN;
        }
        return Status::OK;
    }
};

void RunServer() {
    std::string server_address("0.0.0.0:50052");
    PersonServiceImpl service;

    grpc::EnableDefaultHealthCheckService(true);
    ServerBuilder builder;
    // Listen on the given address without any authentication mechanism.
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    // Register "service" as the instance through which we'll communicate with
    // clients. In this case it corresponds to an *synchronous* service.
    builder.RegisterService(&service);
    // Finally assemble the server.
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;

    // Wait for the server to shutdown. Note that some other thread must be
    // responsible for shutting down the server for this call to ever return.
    server->Wait();
}

int main(int argc, char** argv) {
    RunServer();
    return 0;
}



