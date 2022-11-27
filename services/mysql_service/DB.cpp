
#include "DB.h"
#include <string>
DB::DB(const std::string &schema = "coms4156_db"){
#ifndef TESTING
    try{
        driver = get_driver_instance();
        con = driver->connect("tcp://127.0.0.1:3306", "root", "");
        con->setSchema(schema.c_str());
    }catch(...){
        std::cout << "# ERR: SQLException in " << __FILE__;
    }
#endif
}

DB::~DB() {
#ifndef TESTING
    if(con) delete con, con = nullptr;
#endif
}