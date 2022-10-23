#pragma once

#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
using chrono::time_point;
using chrono::system_clock; // utc_clock if c++20 supported

class TimeDB{
private:
    vector<pair<time_point<system_clock>,time_point<system_clock>>> appts;
public:
    void addAppt(string start, string finish);
    void resetAppt();
    bool checkTime()const;
};