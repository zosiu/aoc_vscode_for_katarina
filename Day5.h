#pragma once
#include <string>
#include <vector>

int HydrothermalVenture(const std::string &inputpath, const bool parse);

struct coordinates {
	int x = 0;
	int y = 0;
};

struct vent {
	coordinates start;
	coordinates end;
};

int ProcessInput(const std::string& inputpath, const bool parse, std::vector<vent>& ventMap);
coordinates ParseCoordinates(const std::string& coord);
int GetHighest(const vent coord);
std::vector<std::vector<int>> InitializeMap(const int mapSize);
void DrawMap(const std::vector<vent>& ventCoords, std::vector<std::vector<int>>& map);
void DrawLine(vent ventCoords, std::vector<std::vector<int>>& map);
bool UpdateDiagonalCoords(vent &ventCoords);
int CountDangerousAreas(const std::vector<std::vector<int>>& map);