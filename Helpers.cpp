#include "Helpers.h"
#include <fstream>
#include <cmath>

std::string GetInputPath(int day)
{
	bool test = false;
	std::string path = "input\\day" + std::to_string(day);

	if (test)
	{
		path += "test";
	}
	path += ".txt";

	return path;
}

std::vector<std::string> ProcessInput(const std::string &inputpath)
{
	std::ifstream input;
	std::string line;
	std::vector<std::string> result;

	input.open(inputpath);
	if (input.is_open())
	{
		while (std::getline(input, line))
		{
			result.push_back(line);
		}
		input.close();
	}

	return result;
}

int ConvertBinToDec(long long binary)
{
	long long dec = 0;
	int i = 0;

	while (binary != 0)
	{
		int mod = binary % 10;
		binary /= 10;
		dec += mod * pow(2, i);
		i++;
	}

	return dec;
}

int GetDigitAfterDelim(const std::string & line, char delim)
{
	size_t pos;
	int res;

	pos = line.find_first_of(delim);
	if (pos != std::string::npos)
	{
		std::string sub = line.substr(pos + 1, 1);
		res = std::stoi(sub);
	}

	return res;
}

std::vector<int> GetNumbersByDelim(std::string & line, char delim)
{
	std::vector<int> result;
	size_t pos = 0;
	size_t pos_new = 0;

	std::string sub;
	while ((pos_new = line.find(delim, pos)) != std::string::npos)
	{
		sub = line.substr(pos, pos_new - pos);
		if (pos != pos_new)
		{
			result.push_back(std::stoi(sub));
		}
		pos = pos_new + 1;
	}

	sub = line.substr(pos);
	result.push_back(std::stoi(sub));

	return result;
}

int RoundUp(const int number)
{
	int i = 0;

	while (pow(10, i) < number)
	{
		i++;
	}

	return pow(10, i);
}
