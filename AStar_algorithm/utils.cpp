#include "utils.h"

bool utils::canNodeFit(std::shared_ptr<stateNode> state, actionData* action)
{
    refreshGrid(state);
    pawn current_pawn = state->pawns[action->pawnID];
    auto grid = state->gridState;
    coordinates startPos = current_pawn.position;
    int x = current_pawn.position.x;
    int y = current_pawn.position.y;
    
    // check vertiacal
    if (current_pawn.orientation == VERTICAL)
    {
        // downward check
        if (action->actionTaken == 1)
        {

            for (int i = 0; i < current_pawn.size; i++)
            {
                y++;
                int value = grid->get(x, y);
                if ((value != 0) && (value != current_pawn.id))
                {
                    return false;
                }
            }
        }
        // upward check
        else if (action->actionTaken == -1)
        {          
            y--;
            int value = grid->get(x, y);
            if ((value != 0) && (value != current_pawn.id))
            {
                return false;
            }
        }
    }
    // check horizontal
    else if (current_pawn.orientation == HORIZONTAL)
    {
        // right check
        if (action->actionTaken == RIGHT)
        {

            for (int i = 0; i < current_pawn.size; i++)
            {
                x++;
                int value = grid->get(x, y);
                if ((value != 0) && (value != current_pawn.id))
                {
                    return false;
                }
            }
        }
        // left check
        else if (action->actionTaken == LEFT)
        {
            x--;
            int value = grid->get(x, y);
            if ((value != 0) && (value != current_pawn.id))
            {
                return false;
            }       
        }
    }
    else
    {
        throw "Orientation error";
    }

    // can overlap its own self, 0 and id value to be simulated as empty
    return true;
}

bool utils::movePlayerUp(std::shared_ptr<stateNode> node)
{
    auto grid = node->gridState;
    //grid->printGrid();
    const int SIZE = 2;
    bool stop = false;

    while (!stop)
    {
        for (int i = 0; i < SIZE; i++)
        {
            int result = grid->get(node->player.x + i, node->player.y - 1);
            if ((result == -1) || (result > 0))
            {
                stop = true;
                break;
            }
        }
        if (!stop)
        {
            node->player.y -= 1;
        }
    }
    
    // todo: removing the line below causes error, but it should not be required
    node->pawns[1].position = node->player;
    refreshGrid(node);
    return true;
}

bool utils::movePlayerDown(std::shared_ptr<stateNode> node)
{
    auto grid = node->gridState;
    //grid->printGrid();
    const int SIZE = 2;
    bool stop = false;

    while (!stop)
    {
        
        for (int i = 0; i < SIZE; i++)
        {
            // todo: check if it will fit first
            int result = grid->get(node->player.x + i, node->player.y + SIZE);
            if ((result == -1) || (result > 0))
            {
                stop = true;
                break;
            }
        }
        if (!stop)
        {
            node->player.y += 1;
        }
    }
   
    

    
    // todo: removing the line below causes error, but it should not be required
    node->pawns[1].position = node->player;
    refreshGrid(node);
    return true;
}

bool utils::movePlayerLeft(std::shared_ptr<stateNode> node)
{
    auto grid = node->gridState;
    //grid->printGrid();
    const int SIZE = 2;
    bool stop = true;

    /*while (!stop)
    {

        if (!stop)
        {

        }
    }*/
    
    for (int i = 0; i < SIZE; i++)
    {
        int result = grid->get(node->player.x - 1, node->player.y + i);
        if ((result == -1) || (result > 0))
        {
            return false;
        }
    }
    
    node->player.x -= 1;
    node->pawns[1].position = node->player;
    refreshGrid(node);
    //grid->printGrid();
    return true;
}

bool utils::movePlayerRight(std::shared_ptr<stateNode> node)
{    
    auto grid = node->gridState;
    //grid->printGrid();
    const int SIZE = 2;
    bool stop = true;

    /*while (!stop)
    {

        if (!stop)
        {

        }
    }*/

    for (int i = 0; i < SIZE; i++)
    {
        int result = grid->get(node->player.x + SIZE, node->player.y + i);
        if ((result == -1) || (result > 0))
        {
            return false;
        }
    }

    node->player.x += 1;
    node->pawns[1].position = node->player;
    refreshGrid(node);
    //grid->printGrid();
    return true;
}

bool utils::moveForward(pawn* p, std::shared_ptr<stateNode> node)
{
    bool mLoopFlag = true;
    if (p->id == 4)
    {
        bool f = true;
    }
    // check orientation
    if (p->orientation == HORIZONTAL)
    {
        while (mLoopFlag)
        {
            actionData generatedAction(p->id, RIGHT);
            if (canNodeFit(node, &generatedAction))
            {
                p->position.x++;
            }
            else
            {
                mLoopFlag = false;
            }
        }
        refreshGrid(node);
        return true;
    }
    else if (p->orientation == VERTICAL)
    {
        while (mLoopFlag)
        {
            actionData generatedAction(p->id, DOWN);
            if (canNodeFit(node, &generatedAction))
            {
                p->position.y++;
            }
            else
            {
                mLoopFlag = false;
            }
        }
        refreshGrid(node);
        return true;
    }
    return false;
}

bool utils::moveBackward(pawn* p, std::shared_ptr<stateNode> node)
{
    bool mLoopFlag = true;
    // check orientation
    if (p->orientation == HORIZONTAL)
    {
        while (mLoopFlag)
        {
            actionData generatedAction(p->id, LEFT);
            if (canNodeFit(node, &generatedAction))
            {
                p->position.x--;
            }
            else
            {
                mLoopFlag = false;
            }
        }
        refreshGrid(node);
        return true;
    }
    else if (p->orientation == VERTICAL)
    {
        while (mLoopFlag)
        {
            actionData generatedAction(p->id, UP);
            if (canNodeFit(node, &generatedAction))
            {
                p->position.y--;
            }
            else
            {
                mLoopFlag = false;
            }
        }
        refreshGrid(node);
        return true;
    }
    return false;
}

bool utils::isSameState(std::shared_ptr<stateNode> a, std::shared_ptr<stateNode> b)
{
    std::map<int, pawn>::iterator iter;
    int sameCount = 0;

    auto playerPosA = a->player;
    auto playerPosB = b->player;
    if ((playerPosA.x == playerPosB.x) && (playerPosA.y == playerPosB.y))
    {
        sameCount++;
    }

    for (iter = a->pawns.begin(); iter != a->pawns.end(); iter++)
    {
        pawn temp_a = iter->second;
        pawn temp_b = b->pawns[temp_a.id];
        if ((temp_a.position.x == temp_b.position.x) && (temp_a.position.y == temp_b.position.y))
        {
            // if same, increase same count
            sameCount++;
        }
    }
    // if all the states are same, return true, else false
    // added 1 to account for the player check
    return (sameCount == (a->pawns.size() + 1));
}

void utils::refreshGrid(std::shared_ptr<stateNode> node)
{
    // initializing new grid
    node->gridState->clearGrid();
    // updating the grid object with the new array
    
    // paint player to the grid
    for (int i = node->player.x; i < node->player.x + 2; i++)
    {
        for (int j = node->player.y; j < node->player.y + 2; j++)
        {
            if ((i < 0) || (j < 0))
            {
                break;
            }
            node->gridState->set(i, j, 1);
        }
    }

    // adding pawns to the grid
    //      look for out of bounds, overlap and throw error
    for (std::pair<int, pawn> pObj: node->pawns)
    {
        
        pawn temp_pawn = pObj.second;
        int x = temp_pawn.position.x, y = temp_pawn.position.y;
        for (int i = 0; i < temp_pawn.size; i++)
        {
            node->gridState->set(x, y, temp_pawn.id);
            if (temp_pawn.orientation == 1)
            {
                x++;
            }
            else
            {
                y++;
            }
        }
    }
}

int utils::getActionNum(pawn* p, int action)
{
    if (p->orientation == VERTICAL)
    {
        if (action == FORWARD)
        {
            return DOWN;
        }
        else if (action == BACKWARD)
        {
            return UP;
        }
    }
    else if (p->orientation == HORIZONTAL)
    {
        if (action == FORWARD)
        {
            return RIGHT;
        }
        else if (action == BACKWARD)
        {
            return LEFT;
        }
    }
    return -1;
}



std::shared_ptr<stateNode> utils::genarateNode()
{
    std::shared_ptr<stateNode> tempState = std::make_shared<stateNode>();
    // generating pawns
    std::map<int, pawn> tempPawns;
    tempPawns[1] = pawn(1, 2, HORIZONTAL, coordinates(0, 2));
    tempPawns[2] = pawn(2, 2, HORIZONTAL, coordinates(0, 3));
    tempPawns[3] = pawn(3, 2, VERTICAL, coordinates(1, 4));
    tempPawns[4] = pawn(4, 2, HORIZONTAL, coordinates(2, 5));
    tempPawns[5] = pawn(5, 3, VERTICAL, coordinates(3, 2));
    tempPawns[6] = pawn(6, 3, VERTICAL, coordinates(4, 3));
    // generating grid
    std::shared_ptr<Grid> gridState = std::make_shared<Grid>(6, 6);
    tempState->pawns = tempPawns;
    tempState->gridState = gridState;
    //tempState.gridState.printGrid();
    // updating grid with pawns
    refreshGrid(tempState);
    //tempState.gridState.printGrid();
    // generating action
    actionData mockAction;
    mockAction.pawnID = 1;
    mockAction.actionTaken = 1;
    return tempState;
}

std::shared_ptr<stateNode> utils::copyNode(std::shared_ptr<stateNode> node)
{
    actionData action;
    // grid setup
    std::shared_ptr<Grid> gridState = std::make_shared<Grid>(node->gridState->WIDTH, node->gridState->HEIGHT);
    // setting up pawns map
    std::map<int, pawn> pawns;
    for (std::pair<int, pawn> pawnObj : node->pawns)
    {
        pawn tempPawn = pawnObj.second;
        pawns[tempPawn.id] = pawn(
            tempPawn.id,
            tempPawn.size,
            tempPawn.orientation,
            coordinates(tempPawn.position.x, tempPawn.position.y)
        );
    }

    std::shared_ptr<stateNode> copiedNode = std::make_shared<stateNode>(
        -1,
        -1,
        node,
        action,
        gridState,
        pawns
    );

    copiedNode->player = node->player;

    
    // updating grid
    refreshGrid(copiedNode);
    //return nodeCopy;
    return copiedNode;
}
