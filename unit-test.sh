#! /bin/bash

cd ./services/mysql_service/
bazel test :faculty_service_test
cd ../am_service/
bazel test :am_service_test
