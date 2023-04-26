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
			return;
		}
		else if (result->result == "not found")
		{
			return;
		}
		else
		{
			threshold = result->threshold;
		}
			
	}
}

std::shared_ptr<RT> IDAStar::search(std::shared_ptr<stateNode> node, int g_cost, int threshold)
{
	int f_cost = g_cost + evaluateState(node);

	if (f_cost > threshold)
	{
		return std::make_shared<RT>("excedded", f_cost);
	}

	if ((node->player.x == goal.x) && (node->player.y == goal.y))
	{
		return std::make_shared<RT>("found", g_cost);
	}

	float min_exceeded_value = -INFINITY;
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
        std::shared_ptr<RT> result = search(root, 0, threshold);
        if (result->result == "found")
        {
            return std::make_shared<RT>("found", result->threshold);
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
        // playerDownNode->gridState->printGrid();
        addToOpenList(playerDownNode);
    }

    if (willMoveLeft)
    {
        playerLeftNode->action.pawnID = 1;
        playerLeftNode->action.actionTaken = LEFT;
        playerLeftNode->cost = node->cost + 1;
        playerLeftNode->stateEvaluationValue = evaluateState(playerLeftNode);
        // playerLeftNode->gridState->printGrid();
        addToOpenList(playerLeftNode);
    }

    if (willMoveRight)
    {
        playerRightNode->action.pawnID = 1;
        playerRightNode->action.actionTaken = RIGHT;
        playerRightNode->cost = node->cost + 1;
        playerRightNode->stateEvaluationValue = evaluateState(playerRightNode);
        // playerLeftNode->gridState->printGrid();
        addToOpenList(playerRightNode);
    }

    for (std::pair<int, pawn> pawnObj : node->pawns)
    {
        pawn currentPawn = pawnObj.second;
        // forward move
        // a copy of currentNode, and altered to form new node
        std::shared_ptr<stateNode> newForwardNode = utils::copyNode(node);
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
        newForwardNode->cost = node->cost + 1;
        newForwardNode->stateEvaluationValue = evaluateState(newForwardNode);
        addToOpenList(newForwardNode);
        //newForwardNode->gridState->printGrid();


        //move pawn backward
        // a copy of currentNode, and altered to form new node
        std::shared_ptr<stateNode> newBackwardNode = utils::copyNode(node);
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
        newBackwardNode->cost = node->cost + 1;
        newBackwardNode->stateEvaluationValue = evaluateState(newBackwardNode);
        addToOpenList(newBackwardNode);
        //newBackwardNode->gridState->printGrid();
    }
}

