#pragma once
#include <string>
#include <vector>

long long BinaryDiagnostic1(const std::string &inputpath);
long long BinaryDiagnostic2(const std::string &inputpath);

std::vector<int> InitializeArrayInt(int size);
size_t GetCountOfBinaryData(const std::string &inputpath, std::vector<int> &zeroes, std::vector<int> &ones);

char GetCommonBitAtPosition(bool max, int pos, const std::vector<std::string> &input);
std::vector<std::string> FilterArrayByBit(char bit, int pos, const std::vector<std::string> &input);
