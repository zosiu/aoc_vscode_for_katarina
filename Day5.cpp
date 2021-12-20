#include "Day5.h"
#include "Helpers.h"
#include <fstream>
#include <iostream>

// use dictionary = std::map, std::unorderedMap
// get direction (vector) between two points
int HydrothermalVenture(const std::string & inputpath, const bool parse)
{
	std::vector<vent> ventCoords;
	int mapSize = ProcessInput(inputpath, parse, ventCoords);
	std::vector<std::vector<int>> map = InitializeMap(RoundUp(mapSize));

	DrawMap(ventCoords, map);

	return CountDangerousAreas(map);
}

void DrawMap(const std::vector<vent>& ventCoords, std::vector<std::vector<int>>& map)
{
	for (size_t i = 0; i < ventCoords.size(); i++)
	{
		DrawLine(ventCoords[i], map);
	}
}

void DrawLine(vent ventCoords, std::vector<std::vector<int>>& map)
{
	bool horizontal = false;
	bool vertical = false;
	bool ascending = false;

	if ( ventCoords.start.x == ventCoords.end.x )
	{
		horizontal = true;
	}
	else if ( ventCoords.start.y == ventCoords.end.y )
	{
		vertical = true;
	}
	else
	{
		ascending = UpdateDiagonalCoords(ventCoords);
	}

	int start = 0;
	int end = 0;
	if (horizontal)
	{
		start = ventCoords.start.y < ventCoords.end.y ? ventCoords.start.y : ventCoords.end.y;
		end = ventCoords.start.y > ventCoords.end.y ? ventCoords.start.y : ventCoords.end.y;
	}
	else if (vertical)
	{
		start = ventCoords.start.x < ventCoords.end.x ? ventCoords.start.x : ventCoords.end.x;
		end = ventCoords.start.x > ventCoords.end.x ? ventCoords.start.x : ventCoords.end.x;
	}
	else
	{
		start = ventCoords.start.x;
		end = ventCoords.end.x;
	}

	for (int i = start; i <= end; i++)
	{
		if (horizontal)
		{
			map[i][ventCoords.start.x]++;
		}
		else if (vertical)
		{
			map[ventCoords.start.y][i]++;
		}
		else
		{
			int j = i - start;
			if (ascending)
			{
				map[ventCoords.start.y + j][ventCoords.start.x + j]++;
			}
			else
			{
				map[ventCoords.start.y - j][ventCoords.start.x + j]++;
			}
		}
	}
}

bool UpdateDiagonalCoords(vent & ventCoords)
{
	if (ventCoords.start.x > ventCoords.end.x)
	{
		int temp = ventCoords.start.x;
		ventCoords.start.x = ventCoords.end.x;
		ventCoords.end.x = temp;

		temp = ventCoords.start.y;
		ventCoords.start.y = ventCoords.end.y;
		ventCoords.end.y = temp;
	}

	return ventCoords.start.y < ventCoords.end.y ? true : false;
}

int CountDangerousAreas(const std::vector<std::vector<int>>& map)
{
	int result = 0;
	for (size_t i = 0; i < map.size(); i++)
	{
		//std::string row = "";
		for (size_t j = 0; j < map.size(); j++)
		{
			//row += map[i][j] == 0 ? "." : std::to_string(map[i][j]);
			if ( map[i][j] > 1)
			{
				result++;
			}
		}
		//std::cout << row << "\n";
	}

	//std::cout << "\n";

	return result;
}

std::vector<std::vector<int>> InitializeMap(const int mapSize)
{
	std::vector<int> rows;
	std::vector<std::vector<int>> map;

	for (int i = 0; i < mapSize; i++)
	{
		rows.push_back(0);
	}

	for (int i = 0; i < mapSize; i++)
	{
		map.push_back(rows);
	}
	return map;
}

int ProcessInput(const std::string& inputpath, const bool parse, std::vector<vent>& ventCoords)
{
	std::ifstream input;
	std::string line;
	int mapSize = 0;

	input.open(inputpath);
	if (input.is_open())
	{
		while (getline(input, line))
		{
			size_t delim = line.find(" -> ");

			coordinates start = ParseCoordinates(line.substr(0, delim));
			coordinates end = ParseCoordinates(line.substr(delim + 4));

			// if the input is parsed, values of x or y have to be equal
			if (!parse || start.x == end.x || start.y == end.y)
			{
				vent ventline;
				ventline.start = start;
				ventline.end = end;

				int high = GetHighest(ventline);
				if (high > mapSize)
				{
					mapSize = high;
				}

				ventCoords.push_back(ventline);
			}
		}
		input.close();
	}

	return mapSize;
}

coordinates ParseCoordinates(const std::string & coord)
{
	coordinates result;
	size_t delim = coord.find(",");

	result.x = stoi(coord.substr(0, delim));
	result.y = stoi(coord.substr(delim+1));

	return result;
}

int GetHighest(const vent coord)
{
	int result = 0;

	if ( coord.start.x > result )
	{ 
		result = coord.start.x;
	}

	if (coord.start.y > result)
	{
		result = coord.start.y;
	}

	if (coord.end.x > result)
	{
		result = coord.end.x;
	}

	if (coord.end.y > result)
	{
		result = coord.end.y;
	}

	return result;
}
