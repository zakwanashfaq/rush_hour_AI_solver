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
    std::cout << "aStar" << std::endl;
    bool flag = canFit(NULL, NULL);
    std::cout << flag << std::endl;
}

bool aStar::isGoal()
{
    return false;
}

bool aStar::canFit(stateNode* state, actionData* action)
{
    stateNode tempState = utils::genarateNode();
    // generating action
    actionData mockAction;
    mockAction.pawnID = 6;
    mockAction.actionTaken = 1;
    bool result =  utils::canNodeFit(&tempState, &mockAction);
    return result;
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
    // first check if it can fit
    // then check if its out of bounds
    //      if OOB then check if its the main player and if main player
    //      is in the goal state
    return false;
}

// checks if all the pawns have the same positions
bool aStar::isSameState(stateNode* a, stateNode* b)
{
    /*stateNode node1;
    stateNode node2;
    std::map<int, pawn> tempPawns;

    for (int i= 1; i <= 5; i++)
    {
        tempPawns[i] = pawn(i, 1, 1, coordinates(1, 3));
    }
    node1.pawns = tempPawns;
    node2.pawns = tempPawns;*/

    /*std::map<int, pawn>::iterator iter;
    for (iter = node1.pawns.begin(); iter != node1.pawns.end(); iter++)
    {
        std::cout << iter->second.id << std::endl;
    }*/
    return utils::isSameState(a, b);
}


void aStar::startSearch()
{ 
    // initialize root 
}

void aStar::searchIteration()
{
}

void aStar::refreshGrid()
{
}

int aStar::evaluateState()
{
    return 0;
}

stateNode aStar::getNextNode()
{
    return stateNode();
}
