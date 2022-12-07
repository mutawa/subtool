// subtool.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

#include "TimeStamp.h"
#include "Utils.h"



int main(int argc, char** argv)
{

    TimeStamp t1(121015) ;
    TimeStamp t2(120000);
    int diff = t1 - t2;
    t1 += diff;
    std::cout << t1 << std::endl;

    return 0;

    std::string file_name = argv[1];
    std::string contents = ReadFileContents(file_name);
    //std::cout << contents << std::endl;

    std::list<Line> lines = FindMatches(contents);
    for(auto const& l : lines) {
        std::cout << l;
    }
    
    // std::cout << "t2 = " << t2.ToString() << std::endl;
    

    std::cout << "Hello World!\n";
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
