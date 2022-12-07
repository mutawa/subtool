#pragma once
#include <iostream>
#include <iomanip>
#include <sstream>

class TimeStamp {
public:
    TimeStamp();
    TimeStamp(int millis);
    TimeStamp(int h, int m, int s, int n);
    TimeStamp(std::string time);
    friend std::ostream& operator<<(std::ostream& os, TimeStamp ts);
    int operator - (const TimeStamp& other);
    TimeStamp operator + (const TimeStamp& other);
    void operator += (int milli);
    std::string time();
    int val();
private:
    void CalculateValue();
    void CalculateFromValue();
    int hh;
    int mm;
    int ss;
    int nn;
    int value;

};