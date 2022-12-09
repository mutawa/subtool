// subtool.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

#include "TimeStamp.h"
#include "Utils.h"
#include <unistd.h>

using std::cout;
using std::string;
using std::endl;

void usage(char *argv0, bool printExamples = false) {
    cout << endl
         << "Usage: " << argv0 << endl
         << "    [-b beginLineNumber]  // marks the BEGINNING anchor-line-number point to"  << endl
         << "                             start calculation from"                           << endl
         
         << "    [-c correctTimeStamp] // used with [-s] or [-n] to mark the correct time." << endl
         
         << "    [-d]                  // displays debug information"                       << endl
         
         << "    [-e beginLineNumber]  // marks the anchor ENDING anchor-line-number point" << endl
         << "                             to end calculation to"                            << endl
         << "    [-h]                  // prints the usage manual with some examples"       << endl
         
         << "    [-m milliSeconds]     // specifies the number of milliseconds to be added" << endl
         << "                             (positive/negative) to all lines"                 << endl
         
         << "    [-n]                  // perform Sync operation (stretch or shrink) "      << endl 
         << "                             subtitles timings. used with [-b] and [-e]"       << endl
         
         << "    [-o output_filename]  // specifies the output file name. If not provided," << endl
         << "                             the input file will be overwritten"               << endl
         
         << "    [-s]                  // perform Shift operation (add/subtract) time to  " << endl
         << "                             each subtitle line"                               << endl
         << "                             this option must be used with [-b] to pick any"   << endl
         << "                             line number."                                     << endl
         << "                             also, either [-c] to denote correct time for "    << endl
         << "                             the selected line, or [-m millisecons] to add"    << endl
         << "                             milliseconds to each line."                       << endl
         << "                             Use only format: HH:mm:ss,fff"                    << endl
         
         << "    [-u]                  // will convert subtitles TEXT section to UTF-8"     << endl
         
         << "    subtitles_file        // the input SRT file to read from."                 << endl
         << endl;

         if(printExamples) {
            cout << "Examples: " << endl << endl
                 << "   " << argv0 << " -u village.srt" << endl
                 << "      converts TEXT in [village.srt] to UTF-8" << endl << endl

                 << "   " << argv0 << " -s -b 4 -c 00:03:15,123 village.srt" << endl
                 << "      SHIFT all lines by the difference of time between between 00:03:15" << endl
                 << "       and whatever timestamp is at line 4 (beginning ancor)" << endl << endl

                 << "   " << argv0 << " -n -b 4 -e 300 -c 00:45:00,00 village.srt" << endl
                 << "      SYNC all lines by measuring span of time between" << endl
                 << "        Begin-Line 4 and End-Line 300, and compairing with" << endl
                 << "        Correct-Timestamp provided (00:45:00,000) and adjusting" << endl
                 << "        increment or decrement to each line accordingly." << endl << endl

                 << "   " << argv0 << " -s -m 3000 village.srt" << endl
                 << "      SHIFT all lines by adding 3000 milliseconds to each line." << endl
                 

                 << "   " << argv0 << " -s -m -6000 -o temp.srt village.srt" << endl
                 << "      SHIFT all lines by subtracting 6000 milliseconds from each line." << endl
                 << "       and writing output to temp.srt" << endl << endl

                 << "   " << argv0 << " -n -d -b 4 -e 300 -c 01:00:00,000 village.srt" << endl
                 << "      Perform Sync as above, but with Debug enabled to print verbose data." << endl << endl
                 
                 << endl;

         }
         exit(0);
}

int main(int argc, char** argv)
{
    // extern char *optarg;
    // extern int optind;
    // extern int opterr;
    // extern int optopt;

    int opt;
    bool doUtf = false;
    bool doShift = false;
    bool doSync = false;
    bool debugMode;
    bool helpRequested;
    bool outputSpecified = false;
    bool beginLineGiven;
    bool endLineGiven;
    int beginLineNumber;
    int endLineNumber;
    bool milliSecondsGiven;
    int milliSeconds;

    TimeStamp* correctTime = nullptr;
    string output_file;

    string timeStampCorrect;


    while((opt = getopt(argc, argv, "b:c:de:hm:no:su")) != -1) {
        switch(opt) {
            
            case 'b':
                beginLineGiven = true;
                beginLineNumber = atoi(optarg);
                break;

            case 'c':
                correctTime = new TimeStamp(optarg);
                break;
            case 'd':
                debugMode = true;
                break;

            case 'e':
                endLineGiven = true;
                endLineNumber = atoi(optarg);
                break;

            case 'h':
                helpRequested = true;
                break;
            case 'm':
                milliSecondsGiven = true;
                milliSeconds = atoi(optarg);
                break;

            case 'n':
                doSync = true;
                cout << "sync" << endl;
                break;

            case 'o':
                outputSpecified = true;
                output_file = optarg;
                break;

            case 's':
                doShift = true;
                break;

            case 'u':
                doUtf = true;
                cout << "utf-8 will be done" << endl;
                break;

            default:
                cout << "Error: invalid usage" << endl;
                usage(argv[0]);
                break;
        }
    }

    if(helpRequested) {
        cout << "help" << endl;
        usage(argv[0], true);
    }
    
    if(optind >= argc) {
        cout << "Error: missing argument" << endl;
        usage(argv[0]);
    }



    string file_name = argv[optind];
    if(!outputSpecified) output_file = file_name;
    
    std::list<Line> lines = ParseFileToLines(file_name);

    if(doShift) {
        if(beginLineGiven) Shift(&lines, beginLineNumber, correctTime);
        else {
            cout << "beginLineNumber must be specified" << endl;
            usage(argv[0]);
        }
    }

    if(doSync) {
        if(!beginLineGiven) {
            cout << "beginLineNumber must be specified" << endl;
            usage(argv[0]);
        }
        if(!endLineGiven) {
            cout << "endLineNumber must be specified" << endl;
            usage(argv[0]);
        }
        if(correctTime == nullptr) {
            cout << "correctTimeStamp for endLine must be specified" << endl;
            usage(argv[0]);
        }
        
        Sync(&lines, beginLineNumber, endLineNumber, correctTime);
        
    }

    WriteOutput(&lines, output_file);

    delete correctTime;

    /*TimeStamp t1(121015) ;
    TimeStamp t2(120000);
    int diff = t1 - t2;
    t1 += diff;
    std::cout << t1 << std::endl;

    return 0;*/
    
    
        
        
        //int shiftAmount = std::stoi(argv[3]);
        //Shift(lines, shiftAmount);
        /*for(auto const& l : lines) {
            std::cout << l;
        }*/

        
        

    

    //std::cout << contents << std::endl;

    
    // std::cout << "t2 = " << t2.ToString() << std::endl;
    

    
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
