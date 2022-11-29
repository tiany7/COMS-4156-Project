# COMS-4156-Project

## Introduction

### What will the server do?

Our project is a student/faculty management system system. The system will provide the service to both the students and the faculties. On the student’s side, the server will support searching courses, browsing course information, adding courses to the shopping cart, checking the fulfillment of prerequisites, enrolling the waitlists and acquiring enrollment-related information. On the faculty’s side, the server will support posting courses, modifying the course information(capacity, date and time, instructor info…), and enrolling students from waitlists. 


### Who or what will be its users?

Its users have two types. One type is student, and the other is administrator (e.g. instructor). 


### What kind of data will your service create or accumulate? What will the data be used for?
Course information (e.g. call number, points, day & time, location, enrollment, instructor): students and instructors can check course information and related enrollment status (e.g. the number of enrolled students, max capacity of the course). Instructors can also insert and modify their own course information.

Student information (e.g. UNI, name, grade, enrollment status): students can check and update their own enrollment status. And administrators can look for all students' information and update enrollment status of students.

Administrator information (e.g. UNI, name): support read, modification, insertion and update of their personal information.

## Installation & Running the Server

Install Bazel and its dependencies(Please refer to the link below, please choose the 4.0.0 version in order to successfully compile our work)

`https://bazel.build/install/ubuntu `

Install google-rpc and its dependencies

`https://grpc.io/blog/installation/ `

### Alternative

Taking advantage of bazel's online compilation functionality(i.e. http_archive and git_repositories ), we can include grpc as a library link instead of downloading the whole stuff. MySQL C++ drivers are also included in the git set up of WORKSPACE page.

`See /WORKSPACE`

Remote MySQL repository link: 
`https://github.com/tiany7/mysql_dependencies`

#Install the MySQL libraries. 

`sudo apt-get update && sudo apt-get install libmysqlclient-dev`

#install the MySQL and boot up the MySQL server on the same machine which you are using.

Follow this link.

`https://dev.mysql.com/doc/refman/8.0/en/linux-installation.html`


After this step, try to compile a simple MySQL rpc-http client

## Compilation

`cd services/mysql_service/`

Edit your RPC server IP and port in `db_server_main.cpp`  


```cpp

#include "mysql_server.h"


int main(void){
    MysqlServer server;
    server.bind_address("<YOUR IP>", PORT);
    server.Run();
    return 0;
}
```

Then start to build the server 

`bazel build :mysql_server` or 
`bazel-4.0.0 build :mysql_server`

This step builds the rpc server. You can find the built server in `bazel-bin/` folder with same diretory/subdirectory name.

Then build the HTTP server

`cd http_server`

`bazel build :mysql_http_server`

Then enter the `bazel-bin` to execute the binary executables in the order of rpc server -> http server.

## Testing the server

### Unit Testing

Execute `./unit-test.sh`

Then you will see the output of the test result on the screen.

```bash
INFO: Elapsed time: 16.344s, Critical Path: 4.39s
INFO: 415 processes: 267 internal, 148 linux-sandbox.
INFO: Build completed successfully, 415 total actions
//services/mysql_service:hello_test                                      PASSED in 0.2s

INFO: Build completed successfully, 415 total actions

```

### API Testing

You can enter the `<IP>:<PORT>/query_sql`

Or

Use commandline or other api testing tools(We used jetbrain native http client tool to test it)

`curl <IP>:<PORT>/query_sql`

Remember to open the port of the port which you are deploying service at.

`sudo ufw allow <PORT>`

#Example 

```Perl
GET http://34.162.75.2:8080/query_sql

HTTP/1.1 200 OK
Content-Length: 140
Content-Type: text/plain
Keep-Alive: timeout=5, max=5

Frank Tian | CS | xx | CHINA
Frank Tian | CS | xx | CHINA
Frank Tian | CS | xx | CHINA
Frank Tian | CS | xx | CHINA


Response code: 200 (OK); Time: 193ms; Content length: 140 bytes
```

All referencees are mentioned in the previous paragraphs

# Make Life Easier

When booting up the service, you can use the bootstrap.sh to boot up mysql_service and its http server. It restarts the server.

`sh bootstrap.sh`

## Table Schema

# Initializing the tables
We are working on the local databases, but we consider to migrate to RDS later on.

To init the tables, you need to have the mysql server running on port 3306 localhost. The server name is 'root' and password is empty. 

You can enter `util/` directory of base dir.

And execute 

`bazel build :all`

Then go to `bazel-bin/util`

Execute the binary

`./db_init_tables`

Then the environment set up is complete!

### Table definition

```mysql
CREATE TABLE faculty (
        name VARCHAR(50), 
        department VARCHAR(50), 
        uni(VARCHAR(50), 
        country VARCHAR(50)
));
```

# Second Iteration

## Client app

Github repository: https://github.com/zchen565/4156_FE/tree/main/demo01

### Build and run

Readme: https://github.com/zchen565/4156_FE/blob/main/demo01/README.md

Third-party could develop and run their own client that uses our server by building a redis-server and mysql-server on their own and changing the configuration.

## CI reports

Add continuous integration (CI) to your main github repository, where your server's codebase resides, so that all your build, analysis and testing tools are automatically run for every commit.  Integrate CI with your repository, e.g., using github actions Links to an external site.or github apps Links to an external site.. Include the CI reports in your repository and explain where to find them in your README (or include a clearly marked link in the README to where your CI reports reside).  If the CI reports include any or all of the other reports mentioned below, you do not need to also include them separately, but please explain what is and is not included with the CI reports in your README. 

## Testing and coverage reports

You should use a branch coverage tool together with your unit, integration and system testing during CI.  Try to achieve at least 85% branch coverage. Include your testing and coverage reports in your server repository. Try to fix most of the bugs found by the tests.

## Static analysis reports

You should also use a static analysis bug finder tool on your entire server codebase.  The static analyzer should run automatically during CI.  Include the static analysis reports in your server repository.  Try to fix most of the bugs found by the analyzer.

## End-to-end tests checklist

Implement end-to-end tests where your client exercises as much functionality of your server as possible.  Although ideally automated, it's ok to run end-to-end tests manually.  Document any manual tests with a checklist or some other mechanism to make sure you can re-run the exact same set of tests as needed, e.g., after fixing a bug.

## Style checker reports

Your entire server codebase, including test cases and even trivial code, should be compliant with a style checker appropriate for your language/platform.  Include some reports from your style checker in your repository.  If it does not generate files, use redirection of output to a file, screenshots, or some other means to produce files.

## Operational entry points

If certain entry points must be called in certain orders or never called in certain orders, make sure to say so.

## Third-party code

If any third-party code is included in either your server or client codebase, also document exactly which code this is, where it resides in your repository, and where you got it from (e.g., download url).
