#pragma once

#include <cstdlib>
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
    DB(const string & schema);
    virtual ~DB();
protected:
    sql::Driver *driver;
    sql::Connection *con;
};
