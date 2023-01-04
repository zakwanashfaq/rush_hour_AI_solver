#include "utils.h"

bool utils::canNodeFit(stateNode* state, actionData* action)
{
    refreshGrid(state);
    pawn current_pawn = state->pawns[action->pawnID];
    Grid grid = state->gridState;
    coordinates startPos = current_pawn.position;
    int x = current_pawn.position.x;
    int y = current_pawn.position.y;
    // check vertiacal
    if (current_pawn.orientation == 0)
    {
        // downward check
        if (action->actionTaken == 1)
        {

            for (int i = 0; i < current_pawn.size; i++)
            {
                y++;
                int value = grid.get(x, y);
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
            int value = grid.get(x, y);
            if ((value != 0) && (value != current_pawn.id))
            {
                return false;
            }
        }
    }
    // check horizontal
    else
    {
        // right check
        if (action->actionTaken == 1)
        {

            for (int i = 0; i < current_pawn.size; i++)
            {
                x++;
                int value = grid.get(x, y);
                if ((value != 0) && (value != current_pawn.id))
                {
                    return false;
                }
            }
        }
        // left check
        else if (action->actionTaken == -1)
        {
            x--;
            int value = grid.get(x, y);
            if ((value != 0) && (value != current_pawn.id))
            {
                return false;
            }       
        }
    }

    // can overlap its own self, 0 and id value to be simulated as empty
    return true;
}

bool utils::moveForward(pawn* p, stateNode* node)
{
    bool mLoopFlag = true;
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
        return true;
    }
    return false;
}

bool utils::moveBackward(pawn* p, stateNode* node)
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

bool utils::isSameState(stateNode* a, stateNode* b)
{
    std::map<int, pawn>::iterator iter;
    int sameCount = 0;
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
    return (sameCount == a->pawns.size());
}

void utils::refreshGrid(stateNode* node)
{
    // initializing new grid
    node->gridState.clearGrid();
    // updating the grid object with the new array
    
    // adding pawns to the grid
    //      look for out of bounds, overlap and throw error
    for (std::pair<int, pawn> pObj: node->pawns)
    {
        
        pawn temp_pawn = pObj.second;
        int x = temp_pawn.position.x, y = temp_pawn.position.y;
        for (int i = 0; i < temp_pawn.size; i++)
        {
            node->gridState.set(x, y, temp_pawn.id);
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



stateNode utils::genarateNode()
{
    stateNode tempState;
    // generating pawns
    std::map<int, pawn> tempPawns;
    tempPawns[1] = pawn(1, 2, HORIZONTAL, coordinates(0, 2));
    tempPawns[2] = pawn(2, 2, HORIZONTAL, coordinates(0, 3));
    tempPawns[3] = pawn(3, 2, VERTICAL, coordinates(1, 4));
    tempPawns[4] = pawn(4, 2, HORIZONTAL, coordinates(2, 5));
    tempPawns[5] = pawn(5, 3, VERTICAL, coordinates(3, 2));
    tempPawns[6] = pawn(6, 3, VERTICAL, coordinates(4, 3));
    // generating grid
    Grid gridState(6, 6);
    tempState.pawns = tempPawns;
    tempState.gridState = gridState;
    //tempState.gridState.printGrid();
    // updating grid with pawns
    refreshGrid(&tempState);
    //tempState.gridState.printGrid();
    // generating action
    actionData mockAction;
    mockAction.pawnID = 1;
    mockAction.actionTaken = 1;
    return tempState;
}

void utils::copyNode(stateNode* node, stateNode* nodeCopy)
{
    actionData action;
    // grid setup
    Grid gridState(node->gridState.WIDTH, node->gridState.HEIGHT);
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
    

    //stateNode tempNode(-1, -1, node, action, gridState, pawns);
    nodeCopy->cost = -1;
    nodeCopy->stateEvaluationValue = -1;
    nodeCopy->parent = node;
    nodeCopy->action = action;
    nodeCopy->gridState = gridState;
    nodeCopy->pawns = pawns;
    // updating grid
    refreshGrid(nodeCopy);
    //return nodeCopy;
}
