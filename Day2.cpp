#include "Day2.h"
#include "Helpers.h"
#include <fstream>

int Dive(const std::string &inputpath, bool part)
{
	std::ifstream input;
	std::string line;

	int depth = 0;
	int pos = 0;
	int aim = 0;

	input.open(inputpath);
	if (input.is_open())
	{
		while (getline(input, line))
		{
			int temp = GetDigitAfterDelim(line, ' ');
			if (part)
			{
				if (line.find("forward") != std::string::npos)
				{
					pos += temp;
					depth += aim * temp;
				}
				else if (line.find("down") != std::string::npos)
				{
					aim += temp;
				}
				else if (line.find("up") != std::string::npos)
				{
					aim -= temp;
				}
			}
			else
			{
				if (line.find("forward") != std::string::npos)
				{
					pos += temp;
				}
				else if (line.find("down") != std::string::npos)
				{
					depth += temp;
				}
				else if (line.find("up") != std::string::npos)
				{
					depth -= temp;
				}
			}
		}
		input.close();
	}
	return depth*pos;
}