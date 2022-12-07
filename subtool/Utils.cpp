#include "Utils.h"
#include <fstream>
#include <sstream>
#include <string>
#include <regex>


std::string ReadFileContents(std::string file_path) {
    std::ifstream file;
    std::stringstream buffer;

    file.open(file_path);
    buffer << file.rdbuf();
    std::string  contents = buffer.str();

    file.close();


    return contents;
}

std::list<Line> FindMatches(const std::string& text) {
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

void Shift(std::list<Line>& lines, int milliSeconds)
{
    for (auto& l : lines) {
        l.Shift(milliSeconds);
    }
}

void Shift(std::list<Line>& lines, int lineNumber, TimeStamp correctTime)
{
    Line aLine;
    bool found = false;
    for (auto const& l : lines) {
        if (l.lineNumber == lineNumber) {
            aLine = l;
            found = true;
            break;
        }
    }

    // todo: check if found
    if (found) {
        std::cout << "Timestamp of line " << lineNumber << " in file is " << aLine.from << std::endl;
    }
}
