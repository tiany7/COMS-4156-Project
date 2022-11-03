#include "faculty_service.h"

FacultyDBService::FacultyDBService() :DB("coms4156_db")
{

}


FacultyDBService::~FacultyDBService()
{

}

int FacultyDBService::GetFacultyDept(const string & dept_name, FacultyRsp* reply)
{
    try {
        auto stmt = con->createStatement();
        char buffer[105] = {0};
        string sql = "SELECT * FROM faculty WHERE department = '%s'";
        sprintf(buffer, sql.c_str(), dept_name.c_str());
        auto res = stmt->executeQuery(buffer);
        while (res->next()) {
            cout<<string(res->getString(1))<<endl;
            auto faculty = reply->add_faculty();
            //一定要用string封装一层！！！！不然会core！！！
            faculty->set_name(string(res->getString(1)));
            faculty->set_department(string(res->getString(2)));
            faculty->set_uni(string(res->getString(3)));
            faculty->set_country(string(res->getString(4)));
        }
        if(res)delete res, res = nullptr;
        if(stmt)delete stmt, stmt = nullptr;
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

int FacultyDBService::GetFacultyUni(const string & uni, FacultyRsp* reply)
{
    try {
        auto stmt = con->createStatement();
        char buffer[105] = {0};
        string sql = "SELECT * FROM faculty WHERE uni = '%s'";
        sprintf(buffer, sql.c_str(), uni.c_str());
        auto res = stmt->executeQuery(string(buffer));
        while (res->next()) {
            auto faculty = reply->add_faculty();
            faculty->set_name(string(res->getString(1)));
            faculty->set_department(string(res->getString(2)));
            faculty->set_uni(string(res->getString(3)));
            faculty->set_country(string(res->getString(4)));
        }
        if(res)delete res, res = nullptr;
        if(stmt)delete stmt, stmt = nullptr;
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
int FacultyDBService::InsertFaculty(const string & name, const string & dept, const string & uni, const string & country)
{
    try {
        auto stmt = con->createStatement();
        char buffer[150] = {0};
        string sql = "INSERT INTO faculty(name, uni, department, country) VALUES ('%s', '%s', '%s', '%s')";
        sprintf(buffer, sql.c_str(), name.c_str(), dept.c_str(),uni.c_str(),  country.c_str());
        stmt->execute(string(buffer));
        if(stmt)delete stmt, stmt = nullptr;
    }catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line "
             << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }catch (...) {
        cout << "other exception" << endl;
    }
    return 0;
}