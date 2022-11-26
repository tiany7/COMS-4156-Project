#ifndef DAL_H
#define DAL_H

#include <stdlib.h>
#include <iostream>
#include <string>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include "mysql_connection.h"

using std::string;
using std::cout;
using std::endl;
class DB{
public:
    DB(const std::string & schema);
    virtual ~DB();
protected:
    sql::Driver *driver;
    sql::Connection *con;
};
#endif //DAL_H
