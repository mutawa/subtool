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

void usage(char *argv0) {
    cout << "Usage: " << argv0
         << " [-l anchorLine]"
         << " [-n syncMilliSeconds]"
         << " [-o output_filename]"
         << " [-s shiftMilliSeconds]"
         << " [-t timeStamp]"
         << " [-u]"
         << " subtitles_file"
         << endl;
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
    bool outputSpecified = false;
    int lineNumber;
    TimeStamp* correctTime;
    string output_file;

    string timeStampCorrect;


    while((opt = getopt(argc, argv, "l:no:st:u")) != -1) {
        switch(opt) {
            case 'n':
                doSync = true;
                cout << "sync" << optarg << endl;
                break;
            case 'u':
                doUtf = true;
                cout << "utf-8 will be done" << endl;
                break;
            case 's':
                doShift = true;
                break;
            case 'l':
                lineNumber = atoi(optarg);
                break;
            case 'o':
                outputSpecified = true;
                output_file = optarg;
                break;
            case 't':
                correctTime = new TimeStamp(optarg);
                break;
            default:
                cout << "Error: invalid usage" << endl;
                usage(argv[0]);
                break;
        }
    }

    if(optind >= argc) {
        cout << "Error: missing argument" << endl;
        usage(argv[0]);
    }


    string file_name = argv[optind];
    if(!outputSpecified) output_file = file_name;
    
    std::list<Line> lines = ParseFileToLines(file_name);

    if(doShift) {
        Shift(&lines, lineNumber, correctTime);
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
