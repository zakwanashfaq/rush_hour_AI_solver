#include "IDA.h"




IDAStar::IDAStar(std::string inputFileName): aStar(inputFileName)
{
	
}

void IDAStar::startSearch()
{
	// aStar::startSearch();
	int threshold = evaluateState(root);

	while (true)
	{
		std::shared_ptr<RT> result = search(root, 0, threshold);

		if (result->result == "found")
		{
            inProgress = false;
            std::stack<std::shared_ptr<stateNode>> resultStack;
            std::shared_ptr<stateNode> tempNode = result->node;
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

            std::cout << "/////////////////////////////////" << std::endl;
            std::cout << "Nodes Searched: " << nodesSearched << std::endl;
            std::cout << "Max depth traversed: " << depth << std::endl;
            std::cout << "/////////////////////////////////" << std::endl;
            return;
		}
		else if (threshold > 1500)
		{
            std::cout << "Max threshold reached. Unable to find Solution" << std::endl;
			return;
		}
		else
		{
			threshold = result->threshold;
            closedHash.clear();
		}
			
	}
}

std::shared_ptr<RT> IDAStar::search(std::shared_ptr<stateNode> node, int g_cost, int threshold)
{
    // g_cost is distance moved, node->cost is recursive depth
    // evaluateState(node) is manhattan distance from current node to goal node
    int f_cost = g_cost + evaluateState(node) + node->cost; 

    nodesSearched++;

    std::string encodedState = utils::getNodeEncoding(node);
    if (closedHash[encodedState])
    {
        return std::make_shared<RT>("null", f_cost);;
    }
    else
    {
        closedHash[encodedState] = true;
    }
	

	if (f_cost > threshold)
	{
		return std::make_shared<RT>("exceeded", f_cost);
	}

	if ((node->player.x == goal.x) && (node->player.y == goal.y))
	{
		return std::make_shared<RT>("found", g_cost, node);
	}

	float min_exceeded_value = INFINITY;
	// the player moves here
	std::shared_ptr<stateNode> playerUpNode = utils::copyNode(node);
	bool willMoveUp = utils::movePlayerUp(playerUpNode);

	std::shared_ptr<stateNode> playerDownNode = utils::copyNode(node);
	bool willMoveDown = utils::movePlayerDown(playerDownNode);

	std::shared_ptr<stateNode> playerLeftNode = utils::copyNode(node);
	bool willMoveLeft = utils::movePlayerLeft(playerLeftNode);

	std::shared_ptr<stateNode> playerRightNode = utils::copyNode(node);
	bool willMoveRight = utils::movePlayerRight(playerRightNode);

    if (willMoveUp)
    {
        playerUpNode->action.pawnID = 1;
        playerUpNode->action.actionTaken = UP;
        playerUpNode->cost = node->cost + 1;
        playerUpNode->stateEvaluationValue = evaluateState(playerUpNode);

        int distance = std::abs(playerUpNode->player.x - node->player.x) + std::abs(playerUpNode->player.y - node->player.y);
        if (distance > 0)
        {

        }
        std::shared_ptr<RT> result = search(playerUpNode, g_cost + distance, threshold);
        if (result->result == "found")
        {
            return result;
        }
        if (result->result == "exceeded")
        {
            if (result->threshold < min_exceeded_value)
            {
                min_exceeded_value = result->threshold;
            }
        }
    }

    if (willMoveDown)
    {
        playerDownNode->action.pawnID = 1;
        playerDownNode->action.actionTaken = DOWN;
        playerDownNode->cost = node->cost + 1;
        playerDownNode->stateEvaluationValue = evaluateState(playerDownNode);
        
        int distance = std::abs(playerDownNode->player.x - node->player.x) + std::abs(playerDownNode->player.y - node->player.y);
        if (distance > 0)
        {

        }
        std::shared_ptr<RT> result = search(playerDownNode, g_cost + distance, threshold);
        if (result->result == "found")
        {
            return result;
        }
        if (result->result == "exceeded")
        {
            if (result->threshold < min_exceeded_value)
            {
                min_exceeded_value = result->threshold;
            }
        }
    }

    if (willMoveLeft)
    {
        playerLeftNode->action.pawnID = 1;
        playerLeftNode->action.actionTaken = LEFT;
        playerLeftNode->cost = node->cost + 1;
        playerLeftNode->stateEvaluationValue = evaluateState(playerLeftNode);

        int distance = std::abs(playerLeftNode->player.x - node->player.x) + std::abs(playerLeftNode->player.y - node->player.y);
        if (distance > 0)
        {

        }
        std::shared_ptr<RT> result = search(playerLeftNode, g_cost + distance, threshold);
        if (result->result == "found")
        {
            return result;
        }
        if (result->result == "exceeded")
        {
            if (result->threshold < min_exceeded_value)
            {
                min_exceeded_value = result->threshold;
            }
        }
    }

    if (willMoveRight)
    {
        playerRightNode->action.pawnID = 1;
        playerRightNode->action.actionTaken = RIGHT;
        playerRightNode->cost = node->cost + 1;
        playerRightNode->stateEvaluationValue = evaluateState(playerRightNode);
        
        int distance = std::abs(playerRightNode->player.x - node->player.x) + std::abs(playerRightNode->player.y - node->player.y);
        if (distance > 0)
        {

        }
        std::shared_ptr<RT> result = search(playerRightNode, g_cost + distance, threshold);
        if (result->result == "found")
        {
            return result;
        }
        if (result->result == "exceeded")
        {
            if (result->threshold < min_exceeded_value)
            {
                min_exceeded_value = result->threshold;
            }
        }
    }

    for (std::pair<int, pawn> pawnObj : node->pawns)
    {
        pawn currentPawn = pawnObj.second;
        // forward move
        // a copy of currentNode, and altered to form new node
        std::shared_ptr<stateNode> newForwardNode = utils::copyNode(node);
        bool mForward = utils::moveForward(&newForwardNode->pawns[currentPawn.id], newForwardNode);
        if (mForward)
        {
            newForwardNode->action.pawnID = currentPawn.id;
            if (currentPawn.orientation == HORIZONTAL)
            {
                newForwardNode->action.actionTaken = RIGHT;
            }
            else if (currentPawn.orientation == VERTICAL)
            {
                newForwardNode->action.actionTaken = DOWN;
            }
            newForwardNode->cost = node->cost + 1;
            newForwardNode->stateEvaluationValue = evaluateState(newForwardNode);

            int distance = std::abs(newForwardNode->player.x - node->player.x) + std::abs(newForwardNode->player.y - node->player.y);
            if (distance > 0)
            {

            }
            std::shared_ptr<RT> result = search(newForwardNode, g_cost + distance, threshold);
            if (result->result == "found")
            {
                return result;
            }
            if (result->result == "exceeded")
            {
                if (result->threshold < min_exceeded_value)
                {
                    min_exceeded_value = result->threshold;
                }
            }
        }
        


        //move pawn backward
        // a copy of currentNode, and altered to form new node
        std::shared_ptr<stateNode> newBackwardNode = utils::copyNode(node);
        bool mBackward = utils::moveBackward(&newBackwardNode->pawns[pawnObj.second.id], newBackwardNode);
        
        if (mBackward)
        {
            newBackwardNode->action.pawnID = currentPawn.id;
            if (currentPawn.orientation == HORIZONTAL)
            {
                newBackwardNode->action.actionTaken = LEFT;
            }
            else if (currentPawn.orientation == VERTICAL)
            {
                newBackwardNode->action.actionTaken = UP;
            }
            newBackwardNode->cost = node->cost + 1;
            newBackwardNode->stateEvaluationValue = evaluateState(newBackwardNode);

            int distance = std::abs(newBackwardNode->player.x - node->player.x) + std::abs(newBackwardNode->player.y - node->player.y);
            if (distance > 0)
            {

            }
                
            std::shared_ptr<RT> result2 = search(newBackwardNode, g_cost + distance, threshold);
            if (result2->result == "found")
            {
                return result2;
            }
            if (result2->result == "exceeded")
            {
                if (result2->threshold < min_exceeded_value)
                {
                    min_exceeded_value = result2->threshold;
                }
            }
        }
        
    }

    // check if min_exceeded_value is infinite
    if (min_exceeded_value == INFINITY)
    {
        return std::make_shared<RT>("null", min_exceeded_value);
    }
    return std::make_shared<RT>("exceeded", min_exceeded_value);
}

int IDAStar::evaluateState(std::shared_ptr<stateNode> node)
{
    coordinates player = node->player;
    double distance = std::abs(goal.x - player.x) + std::abs(goal.y - player.y);
    int score = MAX_EVAL_VALUE / distance;

    return score;
}

