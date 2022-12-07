#include "TimeStamp.h"

std::ostream& operator<<(std::ostream& os, const TimeStamp ts) {
    //os << ts.value; return os;

    if(ts.hh < 10) os << "0";
    os << ts.hh;
    os << ":";
    
    if(ts.mm < 10) os << "0";
    os << ts.mm;
    os << ":";

    if(ts.ss < 10) os << "0";
    os << ts.ss;
    os << ",";

    if(ts.nn < 100) os << "0";
    if(ts.nn < 10) os << "0";
    os << ts.nn;
    


    
    return os;
}
void TimeStamp::Calculate() {
    value = nn + (1000 * ss) + (60 * 1000 * mm) + (60 * 60 * 1000 * hh);
}
TimeStamp::TimeStamp() {
    value = 0;
    nn = 0;
    ss = 0;
    mm = 0;
    hh = 0;
}
TimeStamp::TimeStamp(std::string time) {

    std::string h = time.substr(0,2);
    std::string m = time.substr(3,2);
    std::string s = time.substr(6,2);
    std::string n = time.substr(9);

    hh = std::stoi(h);
    mm = std::stoi(m);
    ss = std::stoi(s);
    nn = std::stoi(n);

    Calculate();
    
}
TimeStamp::TimeStamp(int h, int m, int s, int n) {
    hh = h;
    mm = m;
    ss = s;
    nn = n;

    Calculate();

}
TimeStamp::TimeStamp(int s) {
    
    
    nn = s % 1000;
    s = (s - nn) / 1000;
    ss = s % 60;
    s = (s - ss) / 60;
    mm = s % 60;
    hh = (s - mm) / 60;

    value = s;
    
}