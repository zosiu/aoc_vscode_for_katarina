#pragma once
#include <string>
#include <vector>

std::vector<std::string> ProcessInput(const std::string &inputpath);
int ConvertBinToDec(long long binary);
int GetDigitAfterDelim(const std::string &line, char delim);
std::vector<int> GetNumbersByDelim(std::string &line, char delim);
int RoundUp(const int number);