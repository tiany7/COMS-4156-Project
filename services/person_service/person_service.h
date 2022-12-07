#ifndef _PERSON_SERVICE_H_
#define _PERSON_SERVICE_H_

#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#include <iostream>
#include <memory>
#include <string>
#include <utility>

#include "cppconn/driver.h"
#include "cppconn/exception.h"
#include "cppconn/prepared_statement.h"
#include "cppconn/resultset.h"
#include "cppconn/statement.h"
#include "mysql_connection.h"
#include "proto/person_proto/person.grpc.pb.h"

using ::person::Administrator;
using ::person::AdministratorReadRequest;
using ::person::AdministratorReadResponse;
using ::person::CreateFacultyRatingRequest;
using ::person::CreateFacultyRatingResponse;
using ::person::CreatePersonResponse;
using ::person::DeletePersonRequest;
using ::person::DeletePersonResponse;
using ::person::Faculty;
using ::person::FacultyReadRequest;
using ::person::FacultyReadResponse;
using ::person::GetFacultyRatingRequest;
using ::person::GetFacultyRatingResponse;
using ::person::PersonService;
using ::person::Student;
using ::person::StudentReadRequest;
using ::person::StudentReadResponse;
using ::person::UpdateEmailRequest;
using ::person::UpdateEmailResponse;
using ::std::string;

using ::google::protobuf::uint32;
using ::grpc::Server;
using ::grpc::ServerBuilder;
using ::grpc::ServerContext;
using ::grpc::Status;
using ::grpc::StatusCode;

enum ErrorCode {
  NO_ERROR = 0,
  ERROR = 1,
};

class PersonDB {
 public:
  PersonDB();

  ~PersonDB();

  ErrorCode GetStudentInfo(const std::string& uni,
                           StudentReadResponse* response);

  ErrorCode GetFacultyInfo(const std::string& uni,
                           FacultyReadResponse* response);

  ErrorCode GetAdministratorInfo(const std::string& uni,
                                 AdministratorReadResponse* response);

  ErrorCode UpdateEmail(const std::string& uni, const std::string& email,
                        UpdateEmailResponse* response);

  ErrorCode CreateStudent(const Student* request);

  ErrorCode CreateAdministrator(const Administrator* request,
                                CreatePersonResponse* response);

  ErrorCode DeleteStudent(const std::string& uni,
                          DeletePersonResponse* response);

  ErrorCode CreateFacultyRating(const CreateFacultyRatingRequest* request,
                                CreateFacultyRatingResponse* response);

  ErrorCode GetFacultyRating(const GetFacultyRatingRequest* request, GetFacultyRatingResponse* response);

 private:
  sql::Driver* driver;
  sql::Connection* con;
  sql::Statement* stmt;
  sql::ResultSet* res;
  sql::PreparedStatement* prep_stmt;
};


class PersonServiceImpl final : public PersonService::Service {
public:
  Status ReadStudentInfo(ServerContext* context,
                         const StudentReadRequest* request,
                         StudentReadResponse* response) override;

  Status ReadFacultyInfo(ServerContext* context,
                         const FacultyReadRequest* request,
                         FacultyReadResponse* response) override;

  Status ReadAdministratorInfo(ServerContext* context,
                               const AdministratorReadRequest* request,
                               AdministratorReadResponse* response) override;

  Status UpdateEmail(ServerContext* context, const UpdateEmailRequest* request,
                     UpdateEmailResponse* response);

  Status CreateStudent(ServerContext* context, const Student* request,
                       CreatePersonResponse* response) override;

  Status CreateAdministrator(ServerContext* context,
                             const Administrator* request,
                             CreatePersonResponse* response) override;

  Status DeleteStudent(ServerContext* context,
                       const DeletePersonRequest* request,
                       DeletePersonResponse* response) override;

  Status CreateFacultyRating(ServerContext* context,
                             const CreateFacultyRatingRequest* request,
                             CreateFacultyRatingResponse* response) override;

  Status GetFacultyRating(ServerContext* context,
                          const GetFacultyRatingRequest* request,
                          GetFacultyRatingResponse* response) override;
};

#endif