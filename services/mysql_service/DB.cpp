
#include "DB.h"
#include <string>
DB::DB(const std::string &schema = "coms4156_db"){
    std::cout<<schema<<std::endl;
    try{
        driver = get_driver_instance();
        con = driver->connect("tcp://127.0.0.1:3306", "root", "");
        con->setSchema(schema.c_str());
    }catch(sql::SQLException &e){
        std::cout << "# ERR: SQLException in " << __FILE__;
        std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
        std::cout << "# ERR: " << e.what();
        std::cout << " (MySQL error code: " << e.getErrorCode();
    }
    std::cout<<schema<<std::endl;
}

DB::~DB() {
    if(con) delete con, con = nullptr;
}