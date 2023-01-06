#include "aStar.h"
#include <iostream>
#include <stack>

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
    nodesSearched = 0;
    // initialize root
    stateNode root = utils::genarateNode();
    root.parent = NULL;
    root.cost = 0;
    root.stateEvaluationValue = 0;
    // add to openList
    addToOpenList(&root);
    // print root
    root.gridState.printGrid();
    std::cout << "Initial State" << std::endl;
    std::cout << std::endl;
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
            std::stack<stateNode*> resultStack;
            stateNode* tempNode = currentNode;
            while (tempNode->parent != NULL)
            {
                resultStack.push(tempNode);
                tempNode = tempNode->parent;
            }

            while (!resultStack.empty())
            {
                stateNode* tempNodeFromStack = resultStack.top();
                tempNodeFromStack->gridState.printGrid();
                std::cout << tempNodeFromStack->action.pawnID << "=> ";
                if (tempNodeFromStack->action.actionTaken == FORWARD)
                {
                    std::cout << "Forward" << std::endl;
                }
                else if (tempNodeFromStack->action.actionTaken == BACKWARD)
                {
                    std::cout << "Backward" << std::endl;
                }
                std::cout << std::endl;
                resultStack.pop();
            }
            
            std::cout << "/////////////////////////////////" <<std::endl;
            std::cout << "Nodes Searched: " << nodesSearched << std::endl;
            std::cout << "Max depth traversed: " << depth << std::endl;
            std::cout << "/////////////////////////////////" << std::endl;
            return;
        }

        if (depth == 10000)
        {
            throw "Limit!";
        }

        for (std::pair<int, pawn> pawnObj : currentNode->pawns)
        {
            pawn currentPawn = pawnObj.second;
            // forward move
            // a copy of currentNode, and altered to form new node
            stateNode* newForwardNode = utils::copyNode(currentNode);
            utils::moveForward(&newForwardNode->pawns[currentPawn.id], newForwardNode);
            // todo: score node and save value to state
            newForwardNode->action.pawnID = currentPawn.id;
            newForwardNode->action.actionTaken = FORWARD;
            newForwardNode->cost = depth;
            newForwardNode->stateEvaluationValue = depth;
            addToOpenList(newForwardNode);
            //newForwardNode.gridState.printGrid();


            //move pawn backward
            // a copy of currentNode, and altered to form new node
            stateNode* newBackwardNode = utils::copyNode(currentNode);
            utils::moveBackward(&newBackwardNode->pawns[pawnObj.second.id], newBackwardNode);
            // todo: score node and save value to state
            newBackwardNode->action.pawnID = currentPawn.id;
            newBackwardNode->action.actionTaken = BACKWARD;
            newBackwardNode->cost = depth;
            newBackwardNode->stateEvaluationValue = depth;
            addToOpenList(newBackwardNode);
            // newBackwardNode.gridState.printGrid();
        }
    }
}

void aStar::addToOpenList(stateNode* node)
{
    // check if it already exists in closedList
    for (stateNode* cNode: closedList)
    {
        if (isSameState(cNode, node))
        {
            return;
        }
    }

    // check if it already exists in openList, if it does check if cost is lower
    for (stateNode* oNode : openList)
    {
        // if cost is lower replace with the node
        if (isSameState(oNode, node))
        {
            if (oNode->cost < node->cost)
            {
                oNode = node;
            }
            return;
        }
    }

    nodesSearched++;
    openList.push_back(node);
}

int aStar::evaluateState()
{
    // todo: implement evaluateState
    return depth;
}

stateNode* aStar::getNextNode()
{
    // todo: get node with lowest cost
    stateNode* tempHold = openList[0];

    // remove node from the list
    openList.erase(openList.begin());

    return tempHold;
}
