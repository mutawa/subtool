#include "Utils.h"
#include <fstream>
#include <sstream>
#include <string>
#include <regex>

using std::cout;
using std::endl;
using std::string;
using std::ofstream;

std::string ReadFileContents(std::string file_path) {
    std::ifstream file;
    std::stringstream buffer;

    file.open(file_path);
    buffer << file.rdbuf();
    std::string  contents = buffer.str();

    file.close();


    return contents;
}

std::list<Line> ParseFileToLines(const std::string& file_name) {

    std::string text = ReadFileContents(file_name);

    std::list<Line> lines;
    //std::regex reg("(\\d+)(?:\\r|\\n)+(\\d{2}:\\d{2}:\\d{2}.\\d{3}) --> (\\d{2}:\\d{2}:\\d{2}.\\d{3})(?:\\r|\\n)+(.*?)(?:\\r|\\n)+");
    std::regex reg("(\\d+)(?:\\r?\\n)(\\d{2}:\\d{2}:\\d{2}.\\d{3}) --> (\\d{2}:\\d{2}:\\d{2}.\\d{3})(?:\\r?\\n)([\\s\\S]*?)\\r?\\n\\r?\\n");
    std::sregex_iterator currentMatch(text.begin(), text.end(), reg);
    std::sregex_iterator lastMatch;
    while(currentMatch != lastMatch) {
        std::smatch match = *currentMatch;
        int lineNumber = std::stoi(match.str(1));
        std::string from = match.str(2);
        std::string to = match.str(3);
        std::string text = match.str(4);
        lines.push_back(Line(lineNumber, from, to, text));
        currentMatch++;
    }
    return lines;

}

void ShiftLines(std::list<Line>* lines, const int& milliSeconds)
{
    cout << "shift all lines by " << milliSeconds << " let's go" << endl;
    for (auto& l : (*lines)) {
        
        l.Shift(milliSeconds);
    }
}

void Shift(std::list<Line>* lines, int lineNumber, TimeStamp* correctTime)
{
    Line* aLine;
    bool found = false;
    for (auto& l : (*lines)) {
        if (l.lineNumber == lineNumber) {
            aLine = &l;
            found = true;
            break;
        }
    }

    // todo: check if found
    if (found) {
        cout << "correct time must be " << correctTime << endl;
        std::cout << "Timestamp of line " << lineNumber << " in file is " << (*aLine).from << std::endl;
        int diff = (*correctTime) - (*aLine).from;
        if(diff == 0) {
            std::cout << "No shifting required";
        } else {
            TimeStamp shift(diff);
            // std::cout << "Shifting all lines by " << shift;  // todo: negative time displayed wrongly
            std::cout << "Shifting all lines by " << diff << " milliseconds." << std::endl;
            ShiftLines(lines, diff);
        }

    }
    else {
        int min = (*lines).front().lineNumber;
        int max = (*lines).back().lineNumber;

        cout << "line [" << lineNumber << "] not found. Use number between " << min << " and " << max << "." << endl;
        exit(0);
    }
}

void WriteOutput(list<Line>* lines, const string& file_name) {
    cout << "Writing to [" << file_name << "]" << endl;
    ofstream out(file_name);
    if(out.fail()) {
        cout << "ERROR: unable to write to output file." << endl;
        exit(0);
    }
    int lineNumber = 0;
    for(auto& l : (*lines)) {
        out << ++lineNumber << endl;
        out << l.from << " --> " << l.to << endl;
        out << l.text << endl << endl;
    }

    out.close();
    cout << "Writing to file done." << endl;
}