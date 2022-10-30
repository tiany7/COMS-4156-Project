#! /bin/bash

cd ./services/mysql_service/
bazel test :faculty_service_test
cd ../am_service/
bazel test :am_service_test
cd ../epoch_service/
bazel test :time_service_test
cd ../../unit_test/person_service_test
bazel test :person_service_test