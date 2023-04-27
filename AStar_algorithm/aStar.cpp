#include "aStar.h"

aStar::aStar(std::string inputFileName)
{
    /* Schema for input file
    Grid gridX, gridY
    Pawn id size orientation positionX positionY
    */

    int PawnIdCount = 2;
    std::fstream inputFile;
    std::string temp;
    inputFile.open(inputFileName, std::ios::in);
    if (!inputFile) {
        throw "File not found!";
    }
    // initialize from input file first
    int x, y;
    
    std::map<int, pawn> tempPawns;
    while (inputFile >> temp)
    {
        if (temp.compare("Grid") == 0) {
            inputFile >> x;
            inputFile >> y;
        }
        if (temp.compare("Pawn") == 0) {
            int size, positionX, PositionY, orientationEnum=-1;
            std::string orientation;
            inputFile >> size >> orientation >> positionX >> PositionY;
            if (orientation == "HORIZONTAL")
            {
                orientationEnum = HORIZONTAL;
            }
            else if (orientation == "VERTICAL")
            {
                orientationEnum = VERTICAL;
            }
            tempPawns[PawnIdCount] = pawn(PawnIdCount, size, orientationEnum, coordinates(positionX, PositionY));
            PawnIdCount++;
        }
        if (temp.compare("Goal") == 0) {
            int gx, gy;
            inputFile >> gx >> gy;
            goal.x = gx;
            goal.y = gy;
        }
        if (temp.compare("Player") == 0) {
            int size, positionX, PositionY, orientationEnum = -1;
            std::string orientation;
            inputFile >> size >> orientation >> positionX >> PositionY;
            if (orientation == "HORIZONTAL")
            {
                orientationEnum = HORIZONTAL;
            }
            else if (orientation == "VERTICAL")
            {
                orientationEnum = VERTICAL;
            }
            // tempPawns[1] = pawn(1, size, orientationEnum, coordinates(positionX, PositionY));

            /*int px, py;
            inputFile >> px >> py;*/
            player.x = positionX;
            player.y = PositionY;
        }
    }

    std::shared_ptr<Grid> startGrid = std::make_shared<Grid>(x, y);
    actionData a(0, 0);

    
    root = utils::genarateNode();
    root->parent = NULL;
    root->action = a;
    root->gridState = startGrid;
    root->pawns = tempPawns;
    root->player = player;
    root->cost = 0;
    root->stateEvaluationValue = evaluateState(root);
}

bool aStar::isGoal(std::shared_ptr<stateNode> node)
{
    if (node->pawns[1].position.x == goal.x)
    {
        if (node->pawns[1].position.y == goal.y)
        {
            return true;
        }
    }
    return false;
}

bool aStar::canFit(std::shared_ptr<stateNode> state, actionData* action)
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
bool aStar::isSameState(std::shared_ptr<stateNode> a, std::shared_ptr<stateNode> b)
{
    return utils::isSameState(a, b);
}


void aStar::startSearch()
{ 
    // initialize start variables 
    inProgress = true;
    depth = 0;
    nodesSearched = 0;
    // initialize root
    addToOpenList(root);
    // refresh grid then print root state
    utils::refreshGrid(root);
    root->gridState->printGrid();
    // start search
    searchIteration();
}

void aStar::searchIteration()
{
    while (inProgress)
    {
        std::shared_ptr<stateNode> currentNode = getNextNode(); // not working
        if (!currentNode)
        {
            inProgress = false; 
            std::cout << "This problem is not solvable. Check input parameters.";
            return;
        }
        std::string encodedNode = utils::getNodeEncoding(currentNode);
        closedList.push_back(currentNode);
        closedHash[encodedNode] = true;

         /*if (count >= 100) {
            count = 0;
            std::cout << depth << ", openlist size: ";
            std::cout << openList.size() << std::endl;
        } */
        count++;

        // checking if goal is reached
        if (isGoal(currentNode))
        {
            inProgress = false; 
            std::stack<std::shared_ptr<stateNode>> resultStack;
            std::shared_ptr<stateNode> tempNode = currentNode;
            while (tempNode->parent != NULL)
            {
                resultStack.push(tempNode);
                tempNode = tempNode->parent;
            }

            while (!resultStack.empty())
            {
                std::shared_ptr<stateNode> tempNodeFromStack = resultStack.top();
                tempNodeFromStack->gridState->printGrid();
                std::cout << tempNodeFromStack->action.pawnID << "=> ";
                if (tempNodeFromStack->action.actionTaken == FORWARD)
                {
                    std::cout << "Forward" << std::endl;
                }
                else if (tempNodeFromStack->action.actionTaken == BACKWARD)
                {
                    std::cout << "Backward" << std::endl;
                }
                else if (tempNodeFromStack->action.actionTaken == LEFT)
                {
                    std::cout << "LEFT" << std::endl;
                }
                else if (tempNodeFromStack->action.actionTaken == RIGHT)
                {
                    std::cout << "RIGHT" << std::endl;
                }
                else if (tempNodeFromStack->action.actionTaken == UP)
                {
                    std::cout << "UP" << std::endl;
                }
                else if (tempNodeFromStack->action.actionTaken == DOWN)
                {
                    std::cout << "DOWN" << std::endl;
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
            std::cout << "Max allowed depth reached!\n";
            throw "Max allowed depth reached!\n";
        }

        // todo: investigate how pawn with -1 id gets added
        //       this is causing serious performance issues
        //       temporary fix below
        currentNode->pawns.erase(1);

        // the player moves here
        std::shared_ptr<stateNode> playerUpNode = utils::copyNode(currentNode);
        bool willMoveUp = utils::movePlayerUp(playerUpNode);

        std::shared_ptr<stateNode> playerDownNode = utils::copyNode(currentNode);
        bool willMoveDown = utils::movePlayerDown(playerDownNode);

        std::shared_ptr<stateNode> playerLeftNode = utils::copyNode(currentNode);
        bool willMoveLeft = utils::movePlayerLeft(playerLeftNode);

        std::shared_ptr<stateNode> playerRightNode = utils::copyNode(currentNode);
        bool willMoveRight = utils::movePlayerRight(playerRightNode);

        if (willMoveUp)
        {
            playerUpNode->action.pawnID = 1;
            playerUpNode->action.actionTaken = UP;
            playerUpNode->cost = currentNode->cost + 1;
            playerUpNode->stateEvaluationValue = evaluateState(playerUpNode);
            // playerUpNode->gridState->printGrid();
            addToOpenList(playerUpNode);
        }

        if (willMoveDown)
        {
            playerDownNode->action.pawnID = 1;
            playerDownNode->action.actionTaken = DOWN;
            playerDownNode->cost = currentNode->cost + 1;
            playerDownNode->stateEvaluationValue = evaluateState(playerDownNode);
            // playerDownNode->gridState->printGrid();
            addToOpenList(playerDownNode);
        }

        if (willMoveLeft)
        {
            playerLeftNode->action.pawnID = 1;
            playerLeftNode->action.actionTaken = LEFT;
            playerLeftNode->cost = currentNode->cost + 1;
            playerLeftNode->stateEvaluationValue = evaluateState(playerLeftNode);
            // playerLeftNode->gridState->printGrid();
            addToOpenList(playerLeftNode);
        }

        if (willMoveRight)
        {
            playerRightNode->action.pawnID = 1;
            playerRightNode->action.actionTaken = RIGHT;
            playerRightNode->cost = currentNode->cost + 1;
            playerRightNode->stateEvaluationValue = evaluateState(playerRightNode);
            // playerLeftNode->gridState->printGrid();
            addToOpenList(playerRightNode);
        }

        for (std::pair<int, pawn> pawnObj : currentNode->pawns)
        {
            pawn currentPawn = pawnObj.second;
            // forward move
            // a copy of currentNode, and altered to form new node
            std::shared_ptr<stateNode> newForwardNode = utils::copyNode(currentNode);
            utils::moveForward(&newForwardNode->pawns[currentPawn.id], newForwardNode);
            // todo: score node and save value to state
            newForwardNode->action.pawnID = currentPawn.id;
            if (currentPawn.orientation == HORIZONTAL)
            {
                newForwardNode->action.actionTaken = RIGHT;
            }
            else if (currentPawn.orientation == VERTICAL)
            {
                newForwardNode->action.actionTaken = DOWN;
            }
            newForwardNode->cost = currentNode->cost + 1;
            newForwardNode->stateEvaluationValue = evaluateState(newForwardNode);
            addToOpenList(newForwardNode);
            //newForwardNode->gridState->printGrid();


            //move pawn backward
            // a copy of currentNode, and altered to form new node
            std::shared_ptr<stateNode> newBackwardNode = utils::copyNode(currentNode);
            utils::moveBackward(&newBackwardNode->pawns[pawnObj.second.id], newBackwardNode);
            // todo: score node and save value to state
            newBackwardNode->action.pawnID = currentPawn.id;
            if (currentPawn.orientation == HORIZONTAL)
            {
                newBackwardNode->action.actionTaken = LEFT;
            }
            else if (currentPawn.orientation == VERTICAL)
            {
                newBackwardNode->action.actionTaken = UP;
            }
            newBackwardNode->cost = currentNode->cost + 1;
            newBackwardNode->stateEvaluationValue = evaluateState(newBackwardNode);
            addToOpenList(newBackwardNode);
            //newBackwardNode->gridState->printGrid();
        }


        if (currentNode->cost > depth)
        {
            depth = currentNode->cost;
        }
    }
}

void aStar::addToOpenList(std::shared_ptr<stateNode> node)
{
    //std::cout << "########################" << std::endl;
    // std::cout.flush();
    auto startTime = std::chrono::high_resolution_clock::now();
    // check if it already exists in closedList
    std::string encodedNode = utils::getNodeEncoding(node);
    if (closedHash[encodedNode])
    {
        return;
    }
    /*for (std::shared_ptr<stateNode> cNode: closedList)
    {
        if (isSameState(cNode, node))
        {
            return;
        }
    }*/
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
    //std::cout << "Closed List: " << duration << " microseconds" << std::endl;

    bool flag = true;

    //startTime = std::chrono::high_resolution_clock::now();
    //std::vector<std::shared_ptr<stateNode>> tempList;
    //while (!openList.empty())
    //{
    //    std::shared_ptr<stateNode> node = openList.top();
    //    openList.pop();
    //    tempList.push_back(node);
    //}
    //endTime = std::chrono::high_resolution_clock::now();
    //duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
    //std::cout << "Copy open List: " << duration << " microseconds" << std::endl;


    startTime = std::chrono::high_resolution_clock::now();
    // std::sort(tempList.begin(), tempList.end(), CompareNode());

    if (!openHash[encodedNode])
    {
        openList.push(node);
        openHash[encodedNode] = true;
        nodesSearched++;
    }

    //for (std::shared_ptr<stateNode> oNode : tempList)
    //{
    //    if (isSameState(oNode, node))
    //    {
    //        if (oNode->cost > node->cost)
    //        {
    //            oNode = node;
    //        }
    //        flag = false;
    //    }
    //    // oNode->gridState->printGrid();
    //    openList.push(oNode);
    //}

    //if (flag)
    //{
    //    nodesSearched++;
    //    openList.push(node);
    //    // openList.push_back(node);
    //}

    endTime = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
    // std::cout << "Open List Check: " << duration << " microseconds" << std::endl;

}

int aStar::evaluateState(std::shared_ptr<stateNode> node)
{
    coordinates player = node->player;
    double distance = sqrt(pow(std::abs(goal.x - player.x), 2) + pow(std::abs(goal.y - player.y), 2));
    int score = MAX_EVAL_VALUE / distance;
    score -= (node->cost * DEPTH_FACTOR);
    // todo: check manhattan diagonal path and how many pawns block this path
    // score unblocked states higher
    
    return score;
}

std::shared_ptr<stateNode> aStar::getNextNode()
{
    if (openList.size() == 0)
    {
        return NULL;
    }
    // get node with lowest cost
    std::shared_ptr<stateNode> tempHold = openList.top();

    // remove node from the list
    openList.pop();

    return tempHold;
}
