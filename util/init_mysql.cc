#pragma once
#include <stdlib.h>
#include <iostream>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include "mysql_connection.h"

void InitMySQL() {
    try {
        auto driver = get_driver_instance();
        auto con = driver->connect("tcp://localhost:3306", "root", "");
        auto stmt = con->createStatement();
        stmt->execute("CREATE DATABASE IF NOT EXISTS `faculty`"); // could be changed to "ssol" or sth. like that
        stmt->execute("USE `faculty`"); // same above
        stmt->execute("CREATE TABLE IF NOT EXISTS `faculty` ("
                            "`name` VARCHAR(45),"
                            "`uni` VARCHAR(45) NOT NULL,"
                            "`department` VARCHAR(45) NOT NULL,"
                            "`country` VARCHAR(45) NOT NULL,"
                            "PRIMARY KEY (`uni`))");
        stmt->execute("CREATE TABLE IF NOT EXISTS `timeslots` ("
                            "`deptid` VARCHAR(10) NOT NULL,"
                            "`start` DATETIME NOT NULL,"
                            "`end` DATETIME NOT NULL,"
                            "PRIMARY KEY (`deptid`))");
    } catch (sql::SQLException &e) {
        std::cout << "# ERR: SQLException in " << __FILE__;
        std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
        std::cout << "# ERR: " << e.what();
        std::cout << " (MySQL error code: " << e.getErrorCode();
        std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
    }
}

int main() {
    InitMySQL();
    return 0;
}
