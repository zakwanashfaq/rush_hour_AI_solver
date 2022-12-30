#include "aStar.h"
#include <iostream>

aStar::aStar()
{
    // initialize from input file first
    /*
    Grid gridX, gridY
    StartPawn size orientation positionX positionY
    Pawn size orientation positionX positionY
    Goal gridX, gridY
    */
    // initialize grid
    // initialize pawns
    std::cout << "aStar";
}

bool aStar::canFit()
{
    return false;
}

bool aStar::isNodeInClosedList()
{
    return false;
}

bool aStar::isNodeInOpenList()
{
    return false;
}

bool aStar::isLegalAction()
{
    return false;
}

// checks if all the pawns have the same positions
bool aStar::isSameState(stateNode* a, stateNode* b)
{
    std::map<int, pawn>::iterator iter;
    int sameCount = 0;
    for (iter = a->pawns.begin(); iter != a->pawns.end(); iter++)
    {
        pawn temp_a = iter->second;
        pawn temp_b = b->pawns[temp_a.id];
        // if same, increase same count
        sameCount++;
    }
    return (sameCount == a->pawns.size());
}


void aStar::startSearch()
{ 
}

void aStar::refreshGrid()
{
}

int aStar::evaluateState()
{
    return 0;
}
