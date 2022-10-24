#! /bin/shell
# 杀死进程

base_dir=/home/azureuser/COMS-4156-Project/bazel-bin

PORT=50051

PROCESS=echo | lsof  -i TCP:$PORT | grep LISTEN | awk '{print $2}' | xargs sudo kill 9
echo $PROCESS

PORT2=8080
PROCESS2=echo | lsof  -i TCP:$PORT2 | grep LISTEN | awk '{print $2}'| xargs sudo kill 9

cd $base_dir/services/mysql_service/
./db_server & fork
cd $base_dir/http_server/
./mysql_http_server & fork
# 启动服务