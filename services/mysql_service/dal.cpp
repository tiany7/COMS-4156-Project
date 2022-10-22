

dal::dal(): stmt(nullptr), res(nullptr) {
    driver = get_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "root", "");
    con->setSchema("faculty");
}

int dal::GetFacultyDept(const string &name, FacultyRsp * reply){
    try {
        stmt = con->createStatement();
        char buffer[55] = {0};
        string sql = "SELECT * FROM faculty WHERE department = '%s'";
        sprintf(buffer, sql.c_str(), dept_name.c_str());
        res = stmt->executeQuery(buffer);
        while (res->next()) {
            cout<<string(res->getString(1))<<endl;
            auto faculty = reply->add_faculty();
            //一定要用string封装一层！！！！不然会core！！！
            faculty->set_name(string(res->getString(1)));
            faculty->set_department(string(res->getString(2)));
            faculty->set_uni(string(res->getString(3)));
            faculty->set_country(string(res->getString(4)));
        }
    }catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line "
             << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }

    return 0;
}

dal::~dal() {
    if(res) delete res, res = nullptr;
    if(stmt)delete stmt, stmt = nullptr;
    if(con) delete con, con = nullptr;
}