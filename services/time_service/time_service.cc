#include <ctime>

#include "time_service.hh"

int TimeDBService::CheckTime(const string & dept_id, TimeRsp* reply){
    try {
        auto stmt = con->createStatement();
        char buffer[64] = {0};
        string sql = "SELECT * FROM timeslots WHERE deptid = '%s'";
        sprintf(buffer, sql.c_str(), dept_id.c_str());
        auto res = stmt->executeQuery(buffer);
        cout<< "Getting timeslot for " << dept_id <<endl;
        bool found = false;
        auto timenow = std::time(nullptr);
        char timestr[64] = {0};
        std::strftime(timestr, sizeof(timestr), "%Y-%m-%d %H:%M:%S", std::localtime(&timenow));
        auto t = string(timestr);
        while (!found && res->next()) {
            auto t0 = string(res->getString(2));
            auto t1 = string(res->getString(3));
            if(t0<=t && t<=t1){found = true;}
        }
        string yn = (found ? "Yes" : "No");
        reply->set_yn(yn);
        delete res;
        delete stmt;
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

int TimeDBService::InsertTime(const string & dept_id, const string & start_time, const string & end_time){
    try {
        auto stmt = con->createStatement();
        char buffer[128] = {0};
        string sql = "INSERT INTO timeslots VALUES ('%s', '%s', '%s')";
        sprintf(buffer, sql.c_str(), dept_id.c_str(), start_time.c_str(), end_time.c_str());
        stmt->execute(buffer);
        delete stmt;
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

int TimeDBService::ClearTime(const string & dept_id, TimeRsp* reply){
    try {
        auto stmt = con->createStatement();
        char buffer[64] = {0};
        string sql = "DELETE FROM timeslots WHERE deptid = '%s'";
        sprintf(buffer, sql.c_str(), dept_id.c_str());
        cout<< "Clearing timeslots for " << dept_id <<endl;
        stmt->execute(buffer);
        reply->set_yn(string("Yes"));
        delete stmt;
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