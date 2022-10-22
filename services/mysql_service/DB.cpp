
#include "DB.h"
#include <string>
DB::DB(const std::string &schema = "faculty"){
    driver = get_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "root", "");
    con->setSchema(schema.c_str());
}

DB::~DB() {
    if(con) delete con, con = nullptr;
}