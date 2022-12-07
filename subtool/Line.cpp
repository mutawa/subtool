#include "Line.h"

Line::Line(int ln, const std::string& ts_from, const std::string& ts_to, const std::string& line_text ) {
    lineNumber = ln;
    from = TimeStamp(ts_from);
    to = TimeStamp(ts_to);
    text = line_text;
}

void Line::Shift(int milliSeconds)
{
    from += milliSeconds;
    to += milliSeconds;
}

std::ostream& operator<<(std::ostream& out, const Line& line) {
    out << line.lineNumber << std::endl;
    out << line.from << " --> " << line.to << std::endl;
    out << line.text << std::endl;
    out << std::endl;
    return out;
}