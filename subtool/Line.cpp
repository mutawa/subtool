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

int Map(int n, int start1, int stop1, int start2, int stop2) {
    
    float result = ((float)n - (float)start1) / ((float)stop1 - (float)start1) * ((float)stop2 - (float)start2) + (float)start2;
    
    return (int)result;
}

void Line::Sync(int beginTimeStamp, int endTimeStamp,  int endCorrectTimeStamp) {
    int start1 = beginTimeStamp;
    int start2 = start1;
    int stop1 = endTimeStamp;
    int stop2 = endCorrectTimeStamp;
    int before = from.val();
    int after = Map(before, start1, stop1, start2, stop2);
    cout << from ;
    if(after == before) {
        cout << " NO CHANGE " ;
        //cout << " NO CHANGE before=(" << before << ") st1=(" << start1 << ") e1=(" << stop1 << ")  st2=(" << start2 << ") e2=(" << stop2 << ")" << endl;
    } else {
        //cout << "before=(" << before << ") after=(" << after << ") st1=(" << start1 << ") e1=(" << stop1 << ")  st2=(" << start2 << ") e2=(" << stop2 << ")" << endl;
        from = after;
        to = after + duration;
        cout << "  --> " << from << " " << endl;
    }
    
}


std::ostream& operator<<(std::ostream& out, const Line& line) {
    out << line.lineNumber << std::endl;
    out << line.from << " --> " << line.to << std::endl;
    out << line.text << std::endl;
    out << std::endl;
    return out;
}