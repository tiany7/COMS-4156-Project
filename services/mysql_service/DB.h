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
class DB{
public:
    DB(const string & schema);
    sql::Connection operator->();
    virtual ~DB();
private:
    sql::Driver *driver;
    sql::Connection *con;
};
#endif //DAL_H