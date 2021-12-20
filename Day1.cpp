#include "Day1.h"
#include "Helpers.h"
#include <fstream>

int SonarSweep1(const std::string &inputpath)
{
	std::ifstream input;
	std::string line;
	int oldnum = -1;
	int sum = 0;

	input.open(inputpath);
	if (input.is_open())
	{
		while (std::getline(input, line))
		{
			int newnum = std::stoi(line);
			if (oldnum != -1 && newnum > oldnum)
			{
				sum++;
			}
			oldnum = newnum;
		}
		input.close();
	}

	return sum;
}

int SonarSweep2(const std::string &inputpath)
{
	std::ifstream input;
	std::string line;

	int num1 = -1, num2 = -1, num3 = -1, num4 = -1;
	int windowold, windownew;
	int sum = 0;

	input.open(inputpath);
	if (input.is_open())
	{
		while (std::getline(input, line))
		{
			num1 = num2;
			num2 = num3;
			num3 = num4;
			num4 = std::stoi(line);

			if (num1 != -1 && num2 != -1 && num3 != -1 && num4 != -1)
			{
				windowold = num1 + num2 + num3;
				windownew = num2 + num3 + num4;
				if (windownew > windowold)
				{
					sum++;
				}
			}
		}
		input.close();
	}

	return sum;
}