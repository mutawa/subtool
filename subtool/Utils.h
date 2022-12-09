#pragma once
#include <string>
#include <iostream>
#include <list>
#include "Line.h"
#include <list>

using std::string;
using std::list;


string ReadFileContents(string file_name);

list<Line> ParseFileToLines(const string& text);

void WriteOutput(list<Line>* lines, const string& file_name);
void Shift(list<Line>* lines, int milliSeconds);
void Shift(list<Line>* lines, int lineNumber, TimeStamp* correctTime);