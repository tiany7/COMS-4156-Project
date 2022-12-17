#include "faculty_service.h"

FacultyDBService::FacultyDBService() :DB("coms4156_db")
{

}


FacultyDBService::~FacultyDBService()
{

}

int FacultyDBService::GetFacultyDept( string dept_name, FacultyRsp* reply)
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

int FacultyDBService::GetFacultyUni( string uni, FacultyRsp* reply)
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

int FacultyDBService::GetPost(string uni, ProfpostRsp* reply)
{
    try {
        auto stmt = con->createStatement();
        char buffer[128] = {0};
        string sql = "SELECT * FROM profpost WHERE uni = '%s'";
        sprintf(buffer, sql.c_str(), uni.c_str());
        auto res = stmt->executeQuery(string(buffer));
        while (res->next()) {
            auto profpost = reply->add_profpost();
            profpost->set_uni(string(res->getString(1)));
            profpost->set_content(string(res->getString(2)));
            profpost->set_status(string(res->getString(3)));
            profpost->set_postid(string(res->getString(4)));
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

int FacultyDBService::GetBid(string course, uint32_t capacity, BiddingRsp* reply)
{
    try {
        auto stmt = con->createStatement();
        char buffer[128] = {0};
        string sql = "SELECT * FROM bidding WHERE course = '%s' ORDER BY quote DESC";
        if(capacity){
            sql += " LIMIT %u";
            sprintf(buffer, sql.c_str(), course.c_str(), capacity);}
        else{
            sprintf(buffer, sql.c_str(), course.c_str());
        }
        auto res = stmt->executeQuery(string(buffer));
        while (res->next()) {
            auto bidding = reply->add_bidding();
            bidding->set_uni(string(res->getString(1)));
            bidding->set_course(string(res->getString(2)));
            bidding->set_quote(res->getInt(3));
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

int FacultyDBService::InsertFaculty( string name,  string dept,  string uni,  string  country)
{
    try {
        auto stmt = con->createStatement();
        char buffer[256] = {0};
        std::cout<<"insert faculty"<<" "<<name<<" "<<dept<<" "<<uni<<" "<<country<<std::endl;
        string sql = "INSERT INTO faculty(name, uni, department, country) VALUES ('%s', '%s', '%s', '%s')";
        sprintf(buffer, sql.c_str(), name.c_str(), dept.c_str(),uni.c_str(),  country.c_str());
        std::cout<<buffer<<std::endl;
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

int FacultyDBService::InsertPost(string uni, string content, string status, string postid)
{
    try {
        auto stmt = con->prepareStatement("INSERT INTO profpost(uni, content, status, postid) VALUES (?, ?, ?, ?) ON DUPLICATE KEY UPDATE uni=?, content=?, status=?");
        stmt->setString(1, uni);
        stmt->setString(2, content);
        stmt->setString(3, status);
        stmt->setString(4, postid);
        stmt->setString(5, uni);
        stmt->setString(6, content);
        stmt->setString(7, status);
        stmt->execute();
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

int FacultyDBService::InsertBid(string uni, string course, uint32_t quote)
{
    try {
        if(quote){
            auto stmt = con->prepareStatement("SELECT SUM(quote) FROM bidding WHERE uni=? AND course <> '?'");
            stmt->setString(1, uni);
            stmt->setString(2, course);
            auto res = stmt->executeQuery();
            while(res->next()){
                auto balance = res->getInt(1);
                if(balance + quote > 1000){
                    cout << "Balance insufficient! Current remaining quota: " << (1000-balance) << endl;
                    if(res)delete res, res = nullptr;
                    if(stmt)delete stmt, stmt = nullptr;
                    return 0;
                }
            }
            if(res)delete res, res = nullptr;
            if(stmt)delete stmt, stmt = nullptr;

            stmt = con->prepareStatement("INSERT INTO bidding(uni, course, quote) VALUES (?, ?, ?) ON DUPLICATE KEY UPDATE quote=?");
            stmt->setString(1, uni);
            stmt->setString(2, course);
            stmt->setInt(3, quote);
            stmt->setInt(4, quote);
            stmt->execute();
            if(stmt)delete stmt, stmt = nullptr;
        }else{
            auto stmt = con->prepareStatement("DELETE FROM bidding WHERE uni=?, course=?");
            stmt->setString(1, uni);
            stmt->setString(2, course);
            stmt->execute();
            if(stmt)delete stmt, stmt = nullptr;
        }
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

int FacultyDBService::DelPost(string postid)
{
    try {
        auto stmt = con->createStatement();
        char buffer[150] = {0};
        string sql = "DELETE FROM profpost WHERE postid='%s'";
        sprintf(buffer, sql.c_str(), postid.c_str());
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

int FacultyDBService::Print()
{
    return 1;
}

int FacultyDBService::CalculateSomething(int a, int b){
    return a + b;
}