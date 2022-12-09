#pragma once
#include <string>
#include <iostream>
#include <list>
#include "Line.h"
#include <list>

std::string ReadFileContents(std::string file_name);

std::list<Line> ParseFileToLines(const std::string& text);

void Shift(std::list<Line>& lines, int milliSeconds);
void Shift(std::list<Line>& lines, int lineNumber, TimeStamp correctTime);