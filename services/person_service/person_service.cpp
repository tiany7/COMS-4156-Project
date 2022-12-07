#include "person_service.h"

#define BUFFER_SIZE 105

const std::string kReadStudentInfoErrorMessage = "Read student info failed!";
const std::string kSchemaName = "coms4156_db";
const std::string kStudentInfoTable = "student";
const std::string kFacultyInfoTable = "faculty";
const std::string kAdministratorInfoTable = "administrator";
const std::string kRatingInfoTable = "rating";
const uint32 kMinScore = 1;
const uint32 kMaxScore = 5;

PersonDB::PersonDB() : stmt(nullptr), res(nullptr), prep_stmt(nullptr) {
  try {
    driver = get_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "root", "");
    con->setSchema("coms4156_db");
  } catch (sql::SQLException& e) {
    std::cout << "# ERR: SQLException in " << __FILE__;
    std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
    std::cout << "# ERR: " << e.what();
    std::cout << " (MySQL error code: " << e.getErrorCode();
    std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
    std::cout << "Could not connect to server. Error message: " << e.what()
              << std::endl;
  }
}

PersonDB::~PersonDB() {
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
  if (prep_stmt) {
    delete prep_stmt;
    prep_stmt = nullptr;
  }
}

ErrorCode PersonDB::GetStudentInfo(const std::string& uni,
                          StudentReadResponse* response) {
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
  } catch (sql::SQLException& e) {
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

ErrorCode PersonDB::GetFacultyInfo(const std::string& uni,
                          FacultyReadResponse* response) {
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
  } catch (sql::SQLException& e) {
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

ErrorCode PersonDB::GetAdministratorInfo(const std::string& uni,
                                AdministratorReadResponse* response) {
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
  } catch (sql::SQLException& e) {
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

ErrorCode PersonDB::UpdateEmail(const std::string& uni, const std::string& email,
                      UpdateEmailResponse* response) {
  char buffer[BUFFER_SIZE] = {0};
  string sql =
      "UPDATE " + kStudentInfoTable + " SET email='%s' WHERE uni='%s'";
  sprintf(buffer, sql.c_str(), email.c_str(), uni.c_str());
  try {
    stmt = con->createStatement();
    stmt->execute(buffer);
  } catch (sql::SQLException& e) {
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

ErrorCode PersonDB::CreateStudent(const Student* request) {
  char buffer[BUFFER_SIZE] = {0};
  string sql =
      "insert into " + kStudentInfoTable + "(uni, name) values('%s', '%s')";
  std::string uni = request->uni(), name = request->name();
  sprintf(buffer, sql.c_str(), uni.c_str(), name.c_str());
  try {
    stmt = con->createStatement();
    stmt->execute(buffer);
  } catch (sql::SQLException& e) {
    std::cout << "# ERR: SQLException in " << __FILE__;
    std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
    std::cout << "# ERR: " << e.what();
    std::cout << " (MySQL error code: " << e.getErrorCode();
    std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
    return ErrorCode::ERROR;
  } catch (...) {
    std::cout << "Unknown exception" << std::endl;
  }
  return ErrorCode::NO_ERROR;
}

ErrorCode PersonDB::CreateAdministrator(const Administrator* request,
                              CreatePersonResponse* response) {
  char buffer[BUFFER_SIZE] = {0};
  string sql =
      "insert into " + kAdministratorInfoTable + " values('%s', '%s', '%s')";
  std::string uni = request->uni(), name = request->name(),
              email = request->email();
  sprintf(buffer, sql.c_str(), uni.c_str(), name.c_str(), email.c_str());
  try {
    stmt = con->createStatement();
    stmt->execute(buffer);
  } catch (sql::SQLException& e) {
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

ErrorCode PersonDB::DeleteStudent(const std::string& uni,
                        DeletePersonResponse* response) {
  char buffer[BUFFER_SIZE] = {0};
  string sql = "delete from " + kStudentInfoTable + " where uni='%s'";
  sprintf(buffer, sql.c_str(), uni.c_str());
  try {
    stmt = con->createStatement();
    stmt->execute(buffer);
  } catch (sql::SQLException& e) {
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

ErrorCode PersonDB::CreateFacultyRating(const CreateFacultyRatingRequest* request,
                              CreateFacultyRatingResponse* response) {
  uint32 score = request->score();
  if (score < kMinScore || score > kMaxScore) {
    response->set_message("rating can only be in range of 1-5!");
    return ErrorCode::ERROR;
  }
  try {
    prep_stmt =
        con->prepareStatement("INSERT INTO rating VALUES (?, ?, ?, ?)");
    prep_stmt->setString(1, request->uni());
    prep_stmt->setString(2, request->name());
    prep_stmt->setInt(3, score);
    prep_stmt->setString(4, request->comment());
    prep_stmt->execute();
  } catch (sql::SQLException& e) {
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

ErrorCode PersonDB::GetFacultyRating(const GetFacultyRatingRequest* request,
                            GetFacultyRatingResponse* response) {
  std::string uni = request->uni();
  char buffer[BUFFER_SIZE] = {0};
  char buffer2[BUFFER_SIZE] = {0};
  std::string sql = "SELECT comment FROM rating WHERE uni='%s' LIMIT 10";
  sprintf(buffer, sql.c_str(), uni.c_str());
  std::string sql2 =
      "SELECT AVG(score) FROM rating WHERE uni='%s' GROUP BY uni";
  sprintf(buffer2, sql2.c_str(), uni.c_str());
  try {
    stmt = con->createStatement();
    res = stmt->executeQuery(buffer);
    while (res->next()) {
      response->add_comments(std::string(res->getString(1)));
    }
    res = stmt->executeQuery(buffer2);
    if (res->next()) {
      response->set_score(std::stod(res->getString(1)));
    }
  } catch (sql::SQLException& e) {
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


Status PersonServiceImpl::ReadStudentInfo(ServerContext* context,
                        const StudentReadRequest* request,
                        StudentReadResponse* response) {
  ErrorCode error_code = PersonDB().GetStudentInfo(request->uni(), response);
  if (error_code == ErrorCode::ERROR) {
    return Status(StatusCode::CANCELLED, kReadStudentInfoErrorMessage);
  }
  return Status(StatusCode::OK, response->message());
}

Status PersonServiceImpl::ReadFacultyInfo(ServerContext* context,
                        const FacultyReadRequest* request,
                        FacultyReadResponse* response) {
  ErrorCode error_code = PersonDB().GetFacultyInfo(request->uni(), response);
  if (error_code == ErrorCode::ERROR) {
    return Status(StatusCode::CANCELLED, "Read faculty info failed!");
  }
  return Status::OK;
}

Status PersonServiceImpl::ReadAdministratorInfo(ServerContext* context,
                              const AdministratorReadRequest* request,
                              AdministratorReadResponse* response) {
  ErrorCode error_code =
      PersonDB().GetAdministratorInfo(request->uni(), response);
  if (error_code == ErrorCode::ERROR) {
    return Status(StatusCode::CANCELLED, "Read administrator info failed!");
  }
  return Status::OK;
}

Status PersonServiceImpl::UpdateEmail(ServerContext* context, const UpdateEmailRequest* request,
                    UpdateEmailResponse* response) {
  ErrorCode error_code =
      PersonDB().UpdateEmail(request->uni(), request->email(), response);
  if (error_code == ErrorCode::ERROR) {
    return Status(StatusCode::CANCELLED, "Update email failed!");
  }
  return Status::OK;
}

Status PersonServiceImpl::CreateStudent(ServerContext* context, const Student* request,
                      CreatePersonResponse* response) {
  ErrorCode error_code = PersonDB().CreateStudent(request);
  if (error_code == ErrorCode::ERROR) {
    response->set_message("ERROR");
    return Status(StatusCode::CANCELLED, "Create student failed!");
  }
  response->set_message("OK");
  return Status::OK;
}

Status PersonServiceImpl::CreateAdministrator(ServerContext* context,
                            const Administrator* request,
                            CreatePersonResponse* response) {
  ErrorCode error_code = PersonDB().CreateAdministrator(request, response);
  if (error_code == ErrorCode::ERROR) {
    return Status(StatusCode::CANCELLED, "Create student failed!");
  }
  return Status::OK;
}

Status PersonServiceImpl::DeleteStudent(ServerContext* context,
                      const DeletePersonRequest* request,
                      DeletePersonResponse* response) {
  ErrorCode error_code = PersonDB().DeleteStudent(request->uni(), response);
  if (error_code == ErrorCode::ERROR) {
    return Status(StatusCode::CANCELLED, "Create student failed!");
  }
  return Status::OK;
}

Status PersonServiceImpl::CreateFacultyRating(ServerContext* context,
                            const CreateFacultyRatingRequest* request,
                            CreateFacultyRatingResponse* response) {
  ErrorCode error_code = PersonDB().CreateFacultyRating(request, response);
  if (error_code == ErrorCode::ERROR) {
    return Status(StatusCode::CANCELLED, response->message());
  }
  return Status::OK;
}

Status PersonServiceImpl::GetFacultyRating(ServerContext* context,
                        const GetFacultyRatingRequest* request,
                        GetFacultyRatingResponse* response) {
  ErrorCode error_code = PersonDB().GetFacultyRating(request, response);
  if (error_code == ErrorCode::ERROR) {
    return Status(StatusCode::CANCELLED, response->message());
  }
  return Status::OK;
}

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
