
#include "mysql_server.hh"


int main(void){
    MysqlServer server;
    server.bind_address("localhost", 50051);
    server.Run();
    return 0;
}