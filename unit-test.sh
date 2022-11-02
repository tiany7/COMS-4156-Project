#! /bin/bash

cd ./services/mysql_service/
bazel test :faculty_service_test
cd ../../unit_test/am_service_test/
bazel test :am_service_test
cd ../course_service_test/
bazel test :course_service_test
cd ../person_service_test/
bazel test :person_service_test