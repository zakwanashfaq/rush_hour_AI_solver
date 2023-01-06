#include "Grid.h"
#include <iostream>

Grid::Grid(int sizeX, int sizeY)
{
    WIDTH = sizeX;
    HEIGHT = sizeY;
    clearGrid();
}

int Grid::get(int x, int y)
{
    // out of bounds case 
    if ((x > WIDTH - 1) || (x < 0))
    {
        // std::cout << "values are out of bounds: X" << std::endl;
        return -1;
    }
    else if ((y > HEIGHT - 1) || (y < 0))
    {
        // std::cout << "values are out of bounds: Y" << std::endl;
        return -1;
    }
    else
    {
        return gridArray[y][x];
    }
}

void Grid::set(int x, int y, int value)
{
    // out of bounds case 
    if (x > WIDTH - 1)
    {
        throw "values are out of bounds: X";
    }
    else if (y > HEIGHT - 1)
    {
        throw "values are out of bounds: Y";
    }
    else
    {
        gridArray[y][x] = value;
    }
}

void Grid::clearGrid()
{
    gridArray.clear();
    for (int i = 0; i < HEIGHT; i++)
    {
        std::vector<int> v(WIDTH);
        gridArray.push_back(v);
    }
}

void Grid::printGrid()
{
    for (std::vector<int> subVector : gridArray)
    {
        for (int element : subVector)
        {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


std::vector<std::vector<int>>* Grid::getGridArray()
{
    return &gridArray;
}
