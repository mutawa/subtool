#pragma once
#include <iostream>

class TimeStamp {
public:
    TimeStamp();
    TimeStamp(int millis);
    TimeStamp(int h, int m, int s, int n);
    TimeStamp(std::string time);
    friend std::ostream& operator<<(std::ostream& os, const TimeStamp ts);
private:
    void Calculate();
    int hh;
    int mm;
    int ss;
    int nn;
    int value;

};