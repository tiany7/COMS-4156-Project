#ifndef DAL_H
#define DAL_H

#include <stdlib.h>
#include <iostream>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include "mysql_connection.h"

#include "proto/mysql_server_proto/faculty.grpc.pb.h"
class dal{
public:
    dal();

    int GetFacultyDept(const string & dept_name, FacultyRsp* reply);
    virtual ~dal();
private:
    sql::Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;
    sql::ResultSet *res;
};
#endif //DAL_H