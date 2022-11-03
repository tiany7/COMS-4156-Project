#! /bin/shell

work_dir=/home/azureuser/COMS-4156-Project/services/time_service/

cd $work_dir
bazel build :db_server

http_dir=/home/azureuser/COMS-4156-Project/http_server/
cd $http_dir
bazel build :mysql_http_server

base_dir=/home/azureuser/COMS-4156-Project/bazel-bin

PORT=50051

PROCESS=echo | lsof  -i TCP:$PORT | grep LISTEN | awk '{print $2}' | xargs sudo kill 9
echo $PROCESS

PORT2=8080
PROCESS2=echo | lsof  -i TCP:$PORT2 | grep LISTEN | awk '{print $2}'| xargs sudo kill 9

cd $base_dir/services/time_service/
./db_server & fork
cd $base_dir/http_server/
./mysql_http_server & fork