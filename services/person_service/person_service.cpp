
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

#define BUFFER_SIZE 1024

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
using ::person::Student;
using ::person::Faculty;
using ::person::Administrator;
using ::person::CreatePersonResponse;
using ::person::DeletePersonRequest;
using ::person::DeletePersonResponse;


using ::grpc::ServerBuilder;
using ::grpc::ServerContext;
using ::grpc::Status;
using ::grpc::StatusCode;
using ::grpc::Server;

enum ErrorCode {
    NO_ERROR = 0,
    ERROR = 1,
};


const std::string kReadStudentInfoErrorMessage = "Read student info failed!";
const std::string kSchemaName = "coms4156_db";
const std::string kStudentInfoTable = "student";
const std::string kFacultyInfoTable = "faculty";
const std::string kAdministratorInfoTable = "administrator";

class PersonDB {
public:
    PersonDB(): stmt(nullptr), res(nullptr) {
        try {
            driver = get_driver_instance();
            con = driver->connect("tcp://127.0.0.1:3306", "root", "");
            con->setSchema(kSchemaName);
        } catch (sql::SQLException& e) {
            std::cout << "# ERR: SQLException in " << __FILE__;
            std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
            std::cout << "# ERR: " << e.what();
            std::cout << " (MySQL error code: " << e.getErrorCode();
            std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
            std::cout << "Could not connect to server. Error message: " << e.what() << std::endl;
        }
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

    ErrorCode GetStudentInfo(const std::string& uni, StudentReadResponse* response) {
        char buffer[BUFFER_SIZE] = {0};
        string sql = "SELECT * from " + kStudentInfoTable + " WHERE uni='%s'";
        sprintf(buffer, sql.c_str(), uni.c_str());
        try {
            stmt = con->createStatement();
            res = stmt->executeQuery(buffer);
            if (res->next()) {
                Student* student = response->mutable_student();
                student->set_uni(string(res->getString(1)));
                student->set_name(string(res->getString(2)));
                student->set_email(string(res->getString(3)));
                student->set_affiliation(string(res->getString(4)));
                student->set_school(string(res->getString(5)));
                student->set_advisor(string(res->getString(6)));
            }
        } catch (sql::SQLException &e) {
            std::cout << "# ERR: SQLException in " << __FILE__;
            std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
            std::cout << "# ERR: " << e.what();
            std::cout << " (MySQL error code: " << e.getErrorCode();
            std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
            response->set_message("ERROR");
            return ErrorCode::ERROR;
        }
        response->set_message("OK");
        return ErrorCode::NO_ERROR;
    }

    ErrorCode GetFacultyInfo(const std::string& uni, FacultyReadResponse* response) {
        char buffer[BUFFER_SIZE] = {0};
        string sql = "SELECT * from " + kFacultyInfoTable + " WHERE uni='%s'";
        sprintf(buffer, sql.c_str(), uni.c_str());
        try {
            stmt = con->createStatement();
            res = stmt->executeQuery(buffer);
            if (res->next()) {
                Faculty* faculty = response->mutable_faculty();
                faculty->set_uni(string(res->getString(1)));
                faculty->set_name(string(res->getString(2)));
                faculty->set_email(string(res->getString(3)));
                faculty->set_school(string(res->getString(4)));
            }
        } catch (sql::SQLException &e) {
            std::cout << "# ERR: SQLException in " << __FILE__;
            std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
            std::cout << "# ERR: " << e.what();
            std::cout << " (MySQL error code: " << e.getErrorCode();
            std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
            response->set_message("ERROR");
            return ErrorCode::ERROR;
        }
        
        response->set_message("OK");
        return ErrorCode::NO_ERROR;
    }

    ErrorCode GetAdministratorInfo(const std::string& uni, AdministratorReadResponse* response) {
        char buffer[BUFFER_SIZE] = {0};
        string sql = "SELECT * from " + kAdministratorInfoTable + " WHERE uni='%s'";
        sprintf(buffer, sql.c_str(), uni.c_str());
        try {
            stmt = con->createStatement();
            res = stmt->executeQuery(buffer);
            if (res->next()) {
                Administrator* administrator = response->mutable_administrator();
                administrator->set_uni(string(res->getString(1)));
                administrator->set_name(string(res->getString(2)));
                administrator->set_email(string(res->getString(3)));
            }
        } catch (sql::SQLException &e) {
            std::cout << "# ERR: SQLException in " << __FILE__;
            std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
            std::cout << "# ERR: " << e.what();
            std::cout << " (MySQL error code: " << e.getErrorCode();
            std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
            response->set_message("ERROR");
            return ErrorCode::ERROR;
        }
        
        response->set_message("OK");
        return ErrorCode::NO_ERROR;
    }

    ErrorCode UpdateEmail(const std::string& uni, const std::string& email, UpdateEmailResponse* response) {
        char buffer[BUFFER_SIZE] = {0};
        string sql = "UPDATE " + kStudentInfoTable + " SET email='%s' WHERE uni='%s'";
        sprintf(buffer, sql.c_str(), email.c_str(), uni.c_str());
        try {
            stmt = con->createStatement();
            stmt->execute(buffer);
        } catch (sql::SQLException &e) {
            std::cout << "# ERR: SQLException in " << __FILE__;
            std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
            std::cout << "# ERR: " << e.what();
            std::cout << " (MySQL error code: " << e.getErrorCode();
            std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
            response->set_message("ERROR");
            return ErrorCode::ERROR;
        }

        response->set_message("OK");
        return ErrorCode::NO_ERROR;
    }
    
    ErrorCode CreateStudent(const Student* request) {
        char buffer[BUFFER_SIZE] = {0};
        string sql = "insert into " + kStudentInfoTable + "(uni, name) values('%s', '%s')";
        std::string uni = request->uni(), name = request->name();
        sprintf(buffer, sql.c_str(), uni.c_str(), name.c_str());
        try {
            stmt = con->createStatement();
            stmt->execute(buffer);
        } catch (sql::SQLException &e) {
            std::cout << "# ERR: SQLException in " << __FILE__;
            std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
            std::cout << "# ERR: " << e.what();
            std::cout << " (MySQL error code: " << e.getErrorCode();
            std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
            return ErrorCode::ERROR;
        }
        return ErrorCode::NO_ERROR;
    }

    ErrorCode CreateAdministrator(const Administrator* request, CreatePersonResponse* response) {
        char buffer[BUFFER_SIZE] = {0};
        string sql = "insert into " + kAdministratorInfoTable + " values('%s', '%s', '%s')";
        std::string uni = request->uni(), name = request->name(), email = request->email();
        sprintf(buffer, sql.c_str(), uni.c_str(), name.c_str(), email.c_str());
        try {
            stmt = con->createStatement();
            stmt->execute(buffer);
        } catch (sql::SQLException &e) {
            std::cout << "# ERR: SQLException in " << __FILE__;
            std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
            std::cout << "# ERR: " << e.what();
            std::cout << " (MySQL error code: " << e.getErrorCode();
            std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
            response->set_message("ERROR");
            return ErrorCode::ERROR;
        }
        response->set_message("OK");
        return ErrorCode::NO_ERROR;
    }

    ErrorCode DeleteStudent(const std::string& uni, DeletePersonResponse* response) {
        char buffer[BUFFER_SIZE] = {0};
        string sql = "delete from " + kStudentInfoTable + " where uni='%s'";
        sprintf(buffer, sql.c_str(), uni.c_str());
        try {
            stmt = con->createStatement();
            stmt->execute(string(buffer));
        } catch (sql::SQLException &e) {
            std::cout << "# ERR: SQLException in " << __FILE__;
            std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
            std::cout << "# ERR: " << e.what();
            std::cout << " (MySQL error code: " << e.getErrorCode();
            std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
            response->set_message("ERROR");
            return ErrorCode::ERROR;
        }
        response->set_message("OK");
        return ErrorCode::NO_ERROR;
    }

private:
    sql::Driver* driver;
    sql::Connection* con;
    sql::Statement* stmt;
    sql::ResultSet* res;
};

class PersonServiceImpl final : public PersonService::Service {
    Status ReadStudentInfo(ServerContext* context, const StudentReadRequest* request, StudentReadResponse* response) override {
        ErrorCode error_code = PersonDB().GetStudentInfo(request->uni(), response);
        if (error_code == ErrorCode::ERROR) {
            return Status(StatusCode::CANCELLED, kReadStudentInfoErrorMessage);
        }
        return Status(StatusCode::OK, response->message());
    }

    Status ReadFacultyInfo(ServerContext* context, const FacultyReadRequest* request, FacultyReadResponse* response) override {
        ErrorCode error_code = PersonDB().GetFacultyInfo(request->uni(), response);
        if (error_code == ErrorCode::ERROR) {
            return Status(StatusCode::CANCELLED, "Read faculty info failed!");
        }
        return Status::OK;
    }

    Status ReadAdministratorInfo(ServerContext* context, const AdministratorReadRequest* request, AdministratorReadResponse* response) override {
        ErrorCode error_code = PersonDB().GetAdministratorInfo(request->uni(), response);
        if (error_code == ErrorCode::ERROR) {
            return Status(StatusCode::CANCELLED, "Read administrator info failed!");
        }
        return Status::OK;
    }

    Status UpdateEmail(ServerContext* context, const UpdateEmailRequest* request, UpdateEmailResponse* response) override {
        ErrorCode error_code = PersonDB().UpdateEmail(request->uni(), request->email(),response);
        if (error_code == ErrorCode::ERROR) {
            return Status(StatusCode::CANCELLED, "Update email failed!");
        }
        return Status::OK;
    }

    Status CreateStudent(ServerContext* context, const Student* request, CreatePersonResponse* response) {
        ErrorCode error_code = PersonDB().CreateStudent(request);
        if (error_code == ErrorCode::ERROR) {
            response->set_message("ERROR");
            return Status(StatusCode::CANCELLED, "Create student failed!");
        }
        response->set_message("OK");
        return Status::OK;
    }

    Status CreateAdministrator(ServerContext* context, const Administrator* request, CreatePersonResponse* response) {
        ErrorCode error_code = PersonDB().CreateAdministrator(request, response);
        if (error_code == ErrorCode::ERROR) {
            return Status(StatusCode::CANCELLED, "Create student failed!");
        }
        return Status::OK;
    }

    Status DeleteStudent(ServerContext* context, const DeletePersonRequest* request, DeletePersonResponse* response) {
        ErrorCode error_code = PersonDB().DeleteStudent(request->uni(), response);
        if (error_code == ErrorCode::ERROR) {
            return Status(StatusCode::CANCELLED, "Create student failed!");
        }
        return Status::OK;
    }

};

void RunServer() {
    std::string server_address("0.0.0.0:50053");
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



