#include <stdlib.h>
#include <iostream>

#include "cppconn/driver.h"
#include "cppconn/exception.h"
#include "cppconn/resultset.h"
#include "cppconn/statement.h"
#include "mysql_connection.h"

void InitMySQL() {
    try {
        auto driver = get_driver_instance();
        auto con = driver->connect("tcp://localhost:3306", "root", "");
        auto stmt = con->createStatement();
        stmt->execute("CREATE DATABASE IF NOT EXISTS `coms4156_db`"); // could be changed to "ssol" or sth. like that
        stmt->execute("USE `coms4156_db`"); // same above
        stmt->execute("DROP TABLE IF EXISTS `faculty`");
        stmt->execute("CREATE TABLE IF NOT EXISTS `faculty` ("
                            "`uni` VARCHAR(45) NOT NULL,"
                            "`name` VARCHAR(45),"
                            "`email` VARCHAR(45),"
                            "`school` VARCHAR(45),"
                            "`department` VARCHAR(45) NOT NULL,"
                            "`country` VARCHAR(45) NOT NULL,"
                            "PRIMARY KEY (`uni`))");
    } catch (sql::SQLException &e) {
        std::cout << "# ERR: SQLException in " << __FILE__;
        std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
        std::cout << "# ERR: " << e.what();
        std::cout << " (MySQL error code: " << e.getErrorCode();
        std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
    }
}

void InitMySqlV2(){
    try {
        auto driver = get_driver_instance();
        auto con = driver->connect("tcp://localhost:3306", "root", "");
        auto stmt = con->createStatement();
        stmt->execute("CREATE DATABASE IF NOT EXISTS `coms4156_db`"); // could be changed to "ssol" or sth. like that
        stmt->execute("USE `coms4156_db`"); // same above
        stmt->execute("DROP TABLE IF EXISTS `bidding`");
        stmt->execute("CREATE TABLE IF NOT EXISTS `bidding` ("
                      "`uni` VARCHAR(16) NOT NULL,"
                      "`course` VARCHAR(16) NOT NULL,"
                      "`quote` INT UNSIGNED NOT NULL,"
                      "PRIMARY KEY (`uni`,`course`))");
        stmt->execute("INSERT IGNORE INTO bidding VALUES"
                      "('fg1121', 'COMS4156', 100),"
                      "('fg1121', 'CSOR4231', 100),"
                      "('fg2546', 'COMS4156', 200)"
                      );
        stmt->execute("DROP TABLE IF EXISTS `profpost`");
        stmt->execute("CREATE TABLE IF NOT EXISTS `profpost` ("
                      "`uni` VARCHAR(45) NOT NULL,"
                      "`content` VARCHAR(256) NOT NULL,"
                      "`status` VARCHAR(16) NOT NULL,"
                      "`postid` VARCHAR(45) NOT NULL,"
                      "PRIMARY KEY (`postid`))");
        stmt->execute("INSERT IGNORE INTO profpost VALUES"
                      "('fg1121', 'Hello world', 'Active', 'fg221122')"
                      );
        stmt->execute("CREATE TABLE IF NOT EXISTS `timeslots` ("
                      "`deptid` VARCHAR(10) NOT NULL,"
                      "`start` DATETIME NOT NULL,"
                      "`end` DATETIME NOT NULL,"
                      "PRIMARY KEY (`deptid`))");
        stmt->execute("DROP TABLE IF EXISTS `student`");            
        stmt->execute("CREATE TABLE IF NOT EXISTS `student` ("
                      "`uni` VARCHAR(45) NOT NULL,"
                      "`name` VARCHAR(45),"
                      "`email` VARCHAR(45),"
                      "`affiliation` VARCHAR(45),"
                      "`school` VARCHAR(45),"
                      "`advisor` VARCHAR(45),"
                      "PRIMARY KEY (`uni`))");
        stmt->execute("DROP TABLE IF EXISTS `administrator`");
        stmt->execute("CREATE TABLE IF NOT EXISTS `administrator` ("
                      "`uni` VARCHAR(45) NOT NULL,"
                      "`name` VARCHAR(45),"
                      "`email` VARCHAR(45),"
                      "PRIMARY KEY (`uni`))");
    } catch (sql::SQLException &e) {
        std::cout << "# ERR: SQLException in " << __FILE__;
        std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
        std::cout << "# ERR: " << e.what();
        std::cout << " (MySQL error code: " << e.getErrorCode();
        std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
    }
}

void InitMySQLV3(){
    try {
        auto driver = get_driver_instance();
        auto con = driver->connect("tcp://localhost:3306", "root", "");
        auto stmt = con->createStatement();
        stmt->execute("CREATE DATABASE IF NOT EXISTS `coms4156_db`"); // could be changed to "ssol" or sth. like that
        stmt->execute("USE `coms4156_db`"); // same above
        stmt->execute("CREATE TABLE IF NOT EXISTS course(  \n"
                      "    -- id int NOT NULL PRIMARY KEY AUTO_INCREMENT COMMENT 'Primary Key',\n"
                      "    -- create_time DATETIME COMMENT 'Create Time',\n"
                      "    department VARCHAR(50),\n"
                      "    course VARCHAR(20),\n"
                      "    course_title VARCHAR(50),\n"
                      "    semester VARCHAR(20),\n"
                      "    course_id INT,\n"
                      "    faculty_name VARCHAR(50),\n"
                      "    faculty_uni VARCHAR(20),\n"
                      "    prereq1 VARCHAR(20),\n"
                      "    prereq2 VARCHAR(20),\n"
                      "    prereq3 VARCHAR(20),\n"
                      "    UNIQUE KEY (semester, course)\n"
                      ") COMMENT 'raw course table'");
        stmt->execute("INSERT IGNORE INTO course (department,course,course_title,semester,course_id,faculty_name,faculty_uni,prereq1,prereq2,prereq3)\n"
                      "VALUES\n"
                      "    ('CS','cs4156','Software','2022Fall','1111','Abby Smith','as1111','cs3000',NULL,NULL),\n"
                      "    ('CS','cs4111','Database','2022Fall','1112','Bob Smith','bs1111','cs3000','cs3200',NULL),\n"
                      "    ('CS','cs4118','Operating System','2022Fall','1113','Cathy Smith','cs1111','cs3000','cs3200','cs3500'),\n"
                      "    ('DS','ds4777','Core Data Science','2022Spring','0111','David Smith','ds1111',NULL,NULL,NULL)");
    } catch (sql::SQLException &e) {
        std::cout << "# ERR: SQLException in " << __FILE__;
        std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
        std::cout << "# ERR: " << e.what();
        std::cout << " (MySQL error code: " << e.getErrorCode();
        std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
    }
}

void InitMySQLV4() {
    try {
        auto driver = get_driver_instance();
        auto con = driver->connect("tcp://localhost:3306", "root", "");
        auto stmt = con->createStatement();
        stmt->execute("CREATE DATABASE IF NOT EXISTS `coms4156_db`"); // could be changed to "ssol" or sth. like that
        stmt->execute("USE `coms4156_db`"); // same above
        stmt->execute("DROP TABLE IF EXISTS `rating`");
        stmt->execute("CREATE TABLE IF NOT EXISTS `rating` ("
                      "`uni` VARCHAR(45) NOT NULL,"
                      "`name` VARCHAR(45),"
                      "`score` TINYINT NOT NULL,"
                      "`comment` VARCHAR(512))");
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
    InitMySqlV2();
    InitMySQLV3();
    InitMySQLV4();
    return 0;
}
