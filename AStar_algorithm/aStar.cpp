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
    /*std::cout << "aStar" << std::endl;
    bool flag = canFit(NULL, NULL);
    std::cout << flag << std::endl;*/
}

bool aStar::isGoal(stateNode* node)
{
    if (node->pawns[1].position.x == 4)
    {
        return true;
    }
    return false;
}

bool aStar::canFit(stateNode* state, actionData* action)
{
    return utils::canNodeFit(state, action);
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
    // initialize start variables 
    inProgress = true;
    depth = 0;
    // initialize root
    stateNode root = utils::genarateNode();
    root.parent = NULL;
    root.cost = 0;
    root.stateEvaluationValue = 0;
    // add to openList
    addToOpenList(&root);
    // start searh
    searchIteration();
}

void aStar::searchIteration()
{
    while (inProgress)
    {
        stateNode* currentNode = getNextNode(); // not working
        closedList.push_back(currentNode);
        depth++;

        // checking if goal is reached
        if (isGoal(currentNode))
        {
            inProgress = false; 
            return;
        }

        for (std::pair<int, pawn> pawnObj : currentNode->pawns)
        {
            // forward move
            // a copy of currentNode, and altered to form new node
            stateNode newForwardNode;  
            utils::copyNode(currentNode, &newForwardNode);
            utils::moveForward(&newForwardNode.pawns[pawnObj.second.id], &newForwardNode);
            addToOpenList(&newForwardNode);
            //currentNode->gridState.printGrid();
            //newForwardNode.gridState.printGrid();
            //std::cout << "######################################" << std::endl;


            //move pawn backward
            // a copy of currentNode, and altered to form new node
            stateNode newBackwardNode; 
            utils::copyNode(currentNode, &newBackwardNode);
            utils::moveBackward(&newBackwardNode.pawns[pawnObj.second.id], &newBackwardNode);
            addToOpenList(&newBackwardNode);
            /*currentNode->gridState.printGrid();
            newBackwardNode.gridState.printGrid();
            std::cout << "######################################" << std::endl;*/
        }
    }
}

void aStar::addToOpenList(stateNode* node)
{
    // todo: check if it already exists in closedList
    // todo: check if it already exists in openList
    openList.push_back(node);
}

int aStar::evaluateState()
{
    return depth;
}

stateNode* aStar::getNextNode()
{
    stateNode* tempHold = openList[0];
    openList.erase(openList.begin());
    // make sure node is removed from list
    return tempHold;
}
