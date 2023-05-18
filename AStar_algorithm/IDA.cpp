#include "IDA.h"




IDAStar::IDAStar(std::string inputFileName, bool customEvaluation): aStar(inputFileName)
{
    useCustomEvaluation = customEvaluation;
}

void IDAStar::startSearch()
{
	// aStar::startSearch();
    int threshold = useCustomEvaluation ? evaluateStateCustom(root) : evaluateState(root);
    std::cout << std::endl;
    utils::refreshGrid(root);
    root->gridState->printGrid();
    std::cout << std::endl;
	while (true)
	{
        std::unordered_map<std::string, bool> hash = std::unordered_map<std::string, bool>();
		std::shared_ptr<RT> result = search(root, 0, threshold, hash);
        // std::cout << "Threshold: " << threshold << std::endl;
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
            std::cout << "Unique Nodes Searched: " << uniqueHash.size() << std::endl;
            std::cout << "Nodes Searched: " << nodesSearched << std::endl;
            std::cout << "Max depth traversed: " << threshold << std::endl;
            std::cout << "/////////////////////////////////" << std::endl;
            return;
		}
		else if (threshold > 500)
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

std::shared_ptr<RT> IDAStar::search(std::shared_ptr<stateNode> node, int g_cost, int threshold, std::unordered_map<std::string, bool> hash)
{
    // g_cost is distance moved to get ti this state, node->cost is recursive depth
    // evaluateState(node) is manhattan distance from current node to goal node
    int stateEvaluationValue = useCustomEvaluation ? evaluateStateCustom(root) : evaluateState(root);
    int f_cost = g_cost + stateEvaluationValue;
    
    std::string encodedState = utils::getNodeEncoding(node);
    std::unordered_map<std::string, bool> temphash = std::unordered_map<std::string, bool>(hash);
    if (!uniqueHash[encodedState])
    {
        uniqueHash[encodedState] = true;
    }
    
    if (temphash[encodedState])
    {
        return std::make_shared<RT>("visited", f_cost);;
    }
    else
    {
        temphash[encodedState] = true;
    }

	if (f_cost > threshold)
	{
		return std::make_shared<RT>("exceeded", f_cost);
	}

	if ((node->player.x == goal.x) && (node->player.y == goal.y))
	{
		return std::make_shared<RT>("found", g_cost, node);
	}

    nodesSearched++;

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

        std::shared_ptr<RT> result = search(playerUpNode, g_cost + 1, threshold, temphash);
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

        std::shared_ptr<RT> result = search(playerDownNode, g_cost + 1, threshold, temphash);
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

        std::shared_ptr<RT> result = search(playerLeftNode, g_cost + 1, threshold, temphash);
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
        
        std::shared_ptr<RT> result = search(playerRightNode, g_cost + 1, threshold, temphash);
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

    for (const std::pair<int, pawn> pawnObj : node->pawns)
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
            std::shared_ptr<RT> result = search(newForwardNode, g_cost + 1, threshold, temphash);
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
                
            std::shared_ptr<RT> result2 = search(newBackwardNode, g_cost + 1, threshold, temphash);
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

    return std::make_shared<RT>("exceeded", min_exceeded_value);
}

int IDAStar::evaluateState(std::shared_ptr<stateNode> node)
{
    coordinates player = node->player;
    int distance = std::abs(goal.x - player.x) + std::abs(goal.y - player.y);

    return distance/2; 
}

int IDAStar::evaluateStateCustom(std::shared_ptr<stateNode> node)
{
    coordinates player = node->player;
    int distance = sqrt(pow(std::abs(goal.x - player.x), 2) + pow(std::abs(goal.y - player.y), 2));
    int score = distance;
    score += (node->cost * DEPTH_FACTOR);

    return score;
}

