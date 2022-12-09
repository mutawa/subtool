#include "Line.h"
using std::cout;
using std::endl;

Line::Line(int ln, const std::string& ts_from, const std::string& ts_to, const std::string& line_text ) {
    lineNumber = ln;
    from = TimeStamp(ts_from);
    to = TimeStamp(ts_to);
    duration = to - from;
    text = line_text;
}

void Line::Shift(const int& milliSeconds)
{
    from += milliSeconds;
    to = from + duration;
    //cout << "n=" << lineNumber << " f=" << from << " --> " << to << " (" << duration << ")" << endl;
}

std::ostream& operator<<(std::ostream& out, const Line& line) {
    out << line.lineNumber << std::endl;
    out << line.from << " --> " << line.to << std::endl;
    out << line.text << std::endl;
    out << std::endl;
    return out;
}