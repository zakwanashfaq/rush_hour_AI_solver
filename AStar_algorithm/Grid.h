#pragma once
#include <vector>

class Grid
{
public:
	std::vector <std::vector<int>> gridArray;
	int WIDTH, HEIGHT;
	Grid() : WIDTH(0), HEIGHT(0) {};
	Grid(int sizeX, int sizeY);
	int get(int x, int y);
	void set(int x, int y, int value);
	void clearGrid();
	void printGrid();
	std::vector <std::vector<int>>* getGridArray();
private:
	
};

