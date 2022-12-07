#include "TimeStamp.h"


int TimeStamp::operator - (const TimeStamp& other) {
    //TimeStamp temp(value - other.value);
    //temp.CalculateFromValue();
    //return temp;
    return value - other.value;
}

TimeStamp TimeStamp::operator + (const TimeStamp& other) {
    TimeStamp temp(value + other.value);
    temp.CalculateFromValue();
    return temp;
}

void TimeStamp::operator += (int milli) {
    value += milli;
    CalculateFromValue();
}

std::ostream& operator<<(std::ostream& os, TimeStamp ts) {
    
    //os << std::setw(10) << std::setfill('-') << ts.val();
    os << ts.time();

    return os;
}
void TimeStamp::CalculateValue() {
    value = nn + (1000 * ss) + (60 * 1000 * mm) + (60 * 60 * 1000 * hh);
}

void TimeStamp::CalculateFromValue() {
    int s = value;               // s = 3660002
    
    nn = s % 1000;           // 2
    s = (s - nn) / 1000;     // 3660
    ss = s % 60;             // 0 
    s = (s - ss) / 60;       // 61
    mm = s % 60;             // 1
    hh = (s - mm) / 60;      // 1
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

    CalculateValue();
    
}
TimeStamp::TimeStamp(int h, int m, int s, int n) {
    hh = h;
    mm = m;
    ss = s;
    nn = n;

    CalculateValue();

}
TimeStamp::TimeStamp(int s) {
    value = s;               // s = 3660002
    CalculateFromValue();
    
    // nn = s % 1000;           // 2
    // s = (s - nn) / 1000;     // 3660
    // ss = s % 60;             // 0 
    // s = (s - ss) / 60;       // 61
    // mm = s % 60;             // 1
    // hh = (s - mm) / 60;      // 1

    
    
}

std::string TimeStamp::time() {
    
    std::stringstream buff;
    
    buff << std::setw(2) << std::setfill('0') << hh;
    buff << ":" << std::setw(2) << std::setfill('0') << mm;
    buff << ":" << std::setw(2) << std::setfill('0') << ss;

    buff << "," << std::setw(3) << std::setfill('0') << nn;

    return buff.str();
}

int TimeStamp::val() {
    return value;
}