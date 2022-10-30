#include "time_service.hh"

void TimeDB::addAppt(string start, string finish){
    stringstream ss0(start), ss1(finish);
    tm t0, t1;
    try{
        ss0 >> get_time(&t0, "%Y-%m-%d %H:%M:%S");
        ss1 >> get_time(&t1, "%Y-%m-%d %H:%M:%S");
    }
    catch(const std::exception& e){
        cerr << "Incorrect time format\n" << e.what() << '\n';
    }
    auto begin = system_clock::from_time_t(mktime(&t0));
    auto end = system_clock::from_time_t(mktime(&t1));
    appts.push_back({begin,end});
}

void TimeDB::resetAppt(){
    appts.clear();
}

bool TimeDB::checkTime()const{
    auto now = system_clock::now();
    for(auto &[begin, end]:appts){
        if(begin<=now && now<=end){
            return true;
        }
    }
    return false;
}
