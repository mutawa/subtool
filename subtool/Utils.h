#pragma once
#include <string>
#include <iostream>
#include <list>
#include "Line.h"


std::string ReadFileContents(std::string file_name);

std::list<Line> FindMatches(const std::string& text);