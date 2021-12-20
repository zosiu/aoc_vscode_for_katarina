#pragma once
#include <string>
#include <vector>

int GiantSquid(const std::string &inputpath, const bool lose);

struct bingoNumber {
	int num = 0;
	bool hit = false;
};

struct bingoTable {
	bingoNumber table[5][5];

	void pushRow(const int index, const std::vector<int>& row);
	void drawNumber(const int num);
	bool isWinning() const;
	int getScore() const;
};

std::vector<int> ProcessInput(const std::string &inputpath, std::vector<bingoTable> &bingoTables);
void DrawNumber(const int num, std::vector<bingoTable> &bingoTables);
int GetWinningTableScore(const std::vector<bingoTable> &bingoTables);
int GetLosingTableIndex(const std::vector<bingoTable> &bingoTables);
int GetLosingTableScore(const bingoTable &table);