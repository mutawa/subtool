#pragma once
#include "TimeStamp.h"
#include <list>

class Line {

public:
    TimeStamp from;
    TimeStamp to;
    int lineNumber;
    std::string text;
    Line(int ln, const std::string& ts_from, const std::string& ts_to, const std::string& line_text );
    friend std::ostream& operator<<(std::ostream& out, const Line& line);
};