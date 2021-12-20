#include "Day3.h"
#include "Helpers.h"
#include <fstream>
#include <iostream>

long long BinaryDiagnostic1(const std::string &inputpath)
{
	std::vector<int> zeroes;
	std::vector<int> ones;
	const std::size_t size = GetCountOfBinaryData(inputpath, zeroes, ones);

	std::string gamma = "";
	std::string epsilon = "";
	for (size_t i = 0; i < size; i++)
	{
		if (zeroes[i] > ones[i])
		{
			gamma.push_back('0');
			epsilon.push_back('1');
		}
		else if (ones[i] > zeroes[i])
		{
			gamma.push_back('1');
			epsilon.push_back('0');
		}
		else
		{
			std::cout << "Input exception: Bits at position " << i << " have equal amount!";
		}
	}
	return ConvertBinToDec(stoll(gamma))*ConvertBinToDec(stoll(epsilon));
}

long long BinaryDiagnostic2(const std::string &inputpath)
{
	const std::vector<std::string> input = ProcessInput(inputpath);
	const int size = input[0].size();
	std::vector<std::string> o2 = input, co2 = input;

	int i = 0;
	while (o2.size() > 1)
	{
		o2 = FilterArrayByBit(GetCommonBitAtPosition(true, i, o2), i, o2);
		i++;
	}

	i = 0;
	while (co2.size() > 1)
	{
		co2 = FilterArrayByBit(GetCommonBitAtPosition(false, i, co2), i, co2);
		i++;
	}

	return ConvertBinToDec(stoll(o2[0]))*ConvertBinToDec(stoll(co2[0]));
}

std::vector<int> InitializeArrayInt(int size)
{
	std::vector<int> init;

	for (int i = 0; i < size; i++)
	{
		init.push_back(0);
	}

	return init;
}

size_t GetCountOfBinaryData(const std::string &inputpath, std::vector<int> &zeroes, std::vector<int> &ones)
{
	std::ifstream input;
	std::string line;

	size_t size;

	input.open(inputpath);
	if (input.is_open())
	{
		while (getline(input, line))
		{
			if (zeroes.size() == 0 && ones.size() == 0)
			{
				size = line.size();
				zeroes = InitializeArrayInt(size);
				ones = InitializeArrayInt(size);
			}

			for (size_t i = 0; i < size; i++)
			{
				char num = line.at(i);
				if (num == '0')
				{
					zeroes[i]++;
				}
				else if (num == '1')
				{
					ones[i]++;
				}
			}
		}
		input.close();
	}

	return size;
}

char GetCommonBitAtPosition(bool max, int pos, const std::vector<std::string>& input)
{
	int zeroes = 0;
	int ones = 0;
	for (unsigned int i = 0; i < input.size(); i++)
	{
		if (input[i].at(pos) == '0')
		{
			zeroes++;
		}
		else if (input[i].at(pos) == '1')
		{
			ones++;
		}
	}

	if (max)
	{
		return ones >= zeroes ? '1' : '0';
	}
	else
	{
		return ones >= zeroes ? '0' : '1';
	}
}

std::vector<std::string> FilterArrayByBit(char bit, int pos, const std::vector<std::string>& input)
{
	std::vector<std::string> output;

	for (size_t i = 0; i < input.size(); i++)
	{
		if (input[i].at(pos) == bit)
		{
			output.push_back(input[i]);
		}
	}

	return output;
}
