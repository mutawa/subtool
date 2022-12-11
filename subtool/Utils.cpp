#include "Utils.h"
#include <fstream>
#include <sstream>
#include <string>
#include <regex>

using std::cout;
using std::endl;
using std::string;
using std::ofstream;
using std::vector;
using std::byte;
using std::stringstream;


static const uint16_t lookup[128] = {
    0x20AC,0x067E,0x201A,0x0192,0x201E,0x2026,0x2020,0x2021,0x02C6,0x2030,0x0679,0x2039,0x0152,0x0686,0x0698,0x0688,
    0x06AF,0x2018,0x2019,0x201C,0x201D,0x2022,0x2013,0x2014,0x06A9,0x2122,0x0691,0x203A,0x0153,0x200C,0x200D,0x06BA,
    0x00A0,0x060C,0x00A2,0x00A3,0x00A4,0x00A5,0x00A6,0x00A7,0x00A8,0x00A9,0x06BE,0x00AB,0x00AC,0x00AD,0x00AE,0x00AF,
    0x00B0,0x00B1,0x00B2,0x00B3,0x00B4,0x00B5,0x00B6,0x00B7,0x00B8,0x00B9,0x061B,0x00BB,0x00BC,0x00BD,0x00BE,0x061F,
    0x06C1,0x0621,0x0622,0x0623,0x0624,0x0625,0x0626,0x0627,0x0628,0x0629,0x062A,0x062B,0x062C,0x062D,0x062E,0x062F,
    0x0630,0x0631,0x0632,0x0633,0x0634,0x0635,0x0636,0x00D7,0x0637,0x0638,0x0639,0x063A,0x0640,0x0641,0x0642,0x0643,
    0x00E0,0x0644,0x00E2,0x0645,0x0646,0x0647,0x0648,0x00E7,0x00E8,0x00E9,0x00EA,0x00EB,0x0649,0x064A,0x00EE,0x00EF,
    0x064B,0x064C,0x064D,0x064E,0x00F4,0x064F,0x0650,0x00F7,0x0651,0x00F9,0x0652,0x00FB,0x00FC,0x200E,0x200F,0x06D2
};

vector<byte> getBytes(string const &s) {
    std::vector<std::byte> bytes;
    bytes.reserve(std::size(s));

    std::transform(std::begin(s), std::end(s), std::back_inserter(bytes), [](char const &c){
        return std::byte(c);
    });

    return bytes;
}

string convertWinToUtf8(string const& input) {
    stringstream out;
    vector<byte> bytes = getBytes(input);
    for (auto byte: bytes) {
        if((unsigned char)byte < 0x80) {
            out << (unsigned char)byte;
        } else {
        uint16_t utf8_byte = lookup[ (unsigned char)byte & 0x7f];

        // upper half is obtained by shifting the conversion by 8 bits
        unsigned char upper = utf8_byte >> 8;
        // lower half is masked with 0b0000000011111111 to get rid of the upper bytes
        unsigned char lower = utf8_byte & 0x00FF;
        
        // preparing the conversion place holders
        unsigned char byte1 = 0;
        unsigned char byte2 = 0;
        
        // take the first 6 bits of the lower byte and add them to 10_ _ _ _ _ _
        byte1 = 0b10000000 + ( lower & 0b00111111 );
        
        // shift-left lower 6 bits so we are left with the remaining 2 bits that we still did not use
        // and shift-right the upper bytes 2 bits to make room for the unused 2 bits from lower byte
        // the result is added to 110 _ _ _ _ _

        byte2 = 0b11000000 + (lower >> 6) + (upper << 2);

        out << byte2 << byte1;

        }
    }
    return out.str();

}


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
    int c = 0;
    for (auto& l : (*lines)) {
        cout << ++c << " - " << l.from ;
        l.Shift(milliSeconds);
        cout << "  -->  " << l.from << endl;
    }
}

Line* FindLine(list<Line>* lines, int num) {
    for (auto& l : (*lines)) {
        if (l.lineNumber == num) {
            return &l;
        }
    }

    int min = (*lines).front().lineNumber;
    int max = (*lines).back().lineNumber;

    cout << "line [" << num << "] not found. Use numbers between " << min << " and " << max << "." << endl;
    exit(0);
    
}

void Sync(list<Line>* lines, int beginLineNumber, int endLineNumber, TimeStamp* endCorrectTime) {
    Line* begin = FindLine(lines, beginLineNumber);
    Line* end = FindLine(lines, endLineNumber);
    
    int correct = (*endCorrectTime).val();
    int beginTimeStamp = (*begin).from.val();
    int endTimeStamp = (*end).from.val();



    cout << "start is at " << (*begin).from << " and end is at " << (*end).from << " which should end at " << (*endCorrectTime) << "." << endl;
    int span = (*endCorrectTime).val() - (*end).from.val();
    cout << "span difference between end and correct is " << span << " milliseconds" << endl;


    int before = (*lines).back().from.val();
    int c = 0;
    for(auto& l : (*lines)) {
        cout << ++c << " - ";
        l.Sync(beginTimeStamp, endTimeStamp, correct);
        
    }

    int after = (*lines).back().from.val();
    float diff = after - before;
    if(diff == 0) cout << "No change after sync" << endl;
    else cout << "difference of " << std::fixed << std::setprecision(1) << (diff/1000) << " seconds" << endl;

}

void Shift(list<Line>* lines, int milliSeconds) {
    std::cout << "Shifting all lines by " << milliSeconds << " milliseconds." << std::endl;
    ShiftLines(lines, milliSeconds);
}

void Shift(list<Line>* lines, int lineNumber, TimeStamp* correctTime)
{
    Line* aLine = FindLine(lines, lineNumber);
   
    
    std::cout << "Timestamp of line " << lineNumber << " in file is " << (*aLine).from << std::endl;
    int diff = (*correctTime) - (*aLine).from;
    if(diff == 0) {
        std::cout << "No shifting required" << endl;
        exit(0);
    } else {
        TimeStamp shift(diff);
        
        // std::cout << "Shifting all lines by " << shift;  // todo: negative time displayed wrongly
        std::cout << "Shifting all lines by " << diff << " milliseconds." << std::endl;
        ShiftLines(lines, diff);
    }

    
}

void WriteOutput(list<Line>* lines, const string& file_name, bool convertToUtf8) {
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
        if(convertToUtf8) {
            out << convertWinToUtf8(l.text) << endl << endl;
        } else {

            out << l.text << endl << endl;
        }
    }

    out.close();
    cout << "Writing to file done." << endl;
}