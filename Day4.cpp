#include "Day4.h"
#include "Helpers.h"
#include <fstream>

int GiantSquid(const std::string & inputpath, const bool lose)
{
	std::vector<bingoTable> bingoTables;
	std::vector<int> numbers = ProcessInput(inputpath, bingoTables);
	int result = 0;
	int index = -1;

	for (size_t i = 0; i < numbers.size(); i++)
	{
		DrawNumber(numbers[i], bingoTables);
		if (!lose)
		{
			result = GetWinningTableScore(bingoTables);
		}
		else
		{
			if (index < 0)
			{
				index = GetLosingTableIndex(bingoTables);
			}
			else
			{
				result = GetLosingTableScore(bingoTables[index]);
			}
		}
	
		if (result != 0)
		{
			return result * numbers[i];
		}
	}

	return 0;
}

void DrawNumber(const int num, std::vector<bingoTable>& bingoTables)
{
	for (size_t i = 0; i < bingoTables.size(); i++)
	{
		bingoTables[i].drawNumber(num);
	}
}

int GetWinningTableScore(const std::vector<bingoTable>& bingoTables)
{
	for (size_t i = 0; i < bingoTables.size(); i++)
	{
		if (bingoTables[i].isWinning())
		{
			return bingoTables[i].getScore();
		}
	}

	return 0;
}

int GetLosingTableIndex(const std::vector<bingoTable>& bingoTables)
{
	int losingTable = -1;

	for (size_t i = 0; i < bingoTables.size(); i++)
	{
		if (!bingoTables[i].isWinning())
		{	// if there's more than one losing table, we break the cycle
			if (losingTable < 0)
			{
				losingTable = i;
			}
			else
			{
				return -1;
			}
		}
	}

	return losingTable;
}

int GetLosingTableScore(const bingoTable & table)
{
	if (table.isWinning())
	{
		return table.getScore();
	}

	return 0;
}

std::vector<int> ProcessInput(const std::string& inputpath, std::vector<bingoTable>& bingoTables)
{
	std::ifstream input;
	std::string line;
	std::vector<int> numbersToDraw;

	input.open(inputpath);
	if (input.is_open())
	{
		int lineCnt = 0;
		bingoTable table;
		while (getline(input, line))
		{
			if (lineCnt == 0)
			{
				numbersToDraw = GetNumbersByDelim(line, ',');
			}
			else if ((lineCnt - 1) % 6 == 0)
			{
				if (lineCnt - 1 != 0)
				{
					bingoTables.push_back(table);
				}
			}
			else
			{
				std::vector<int> bingoRow = GetNumbersByDelim(line, ' ');
				int row = ((lineCnt - 1) % 6) - 1;
				table.pushRow(row, bingoRow);
			}
			lineCnt++;
		}
		bingoTables.push_back(table);
		input.close();
	}
	return numbersToDraw;
}

void bingoTable::pushRow(const int index, const std::vector<int>& row)
{
	bingoNumber x;
	for (size_t i = 0; i < row.size(); i++)
	{
		x.num = row[i];
		table[index][i] = x;
	}
}

void bingoTable::drawNumber(const int num)
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (table[i][j].num == num)
			{
				table[i][j].hit = true;
			}
		}
	}
}

bool bingoTable::isWinning() const
{
	for (int i = 0; i < 5; i++)
	{
		if (table[i][0].hit && table[i][1].hit && table[i][2].hit && table[i][3].hit && table[i][4].hit)
		{
			return true;
		}

		if (table[0][i].hit && table[1][i].hit && table[2][i].hit && table[3][i].hit && table[4][i].hit)
		{
			return true;
		}
	}

	return false;
}

int bingoTable::getScore() const
{
	int result = 0;

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (!table[i][j].hit)
			{
				result += table[i][j].num;
			}
		}
	}

	return result;
}
