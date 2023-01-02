#include "utils.h"

bool utils::canNodeFit(stateNode* state, actionData* action)
{
    state->gridState.printGrid();
    refreshGrid(state);
    state->gridState.printGrid();
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
    //node->gridState.printGrid();
}



stateNode utils::genarateNode()
{
    stateNode tempState;
    // generating pawns
    std::map<int, pawn> tempPawns;
    tempPawns[1] = pawn(1, 2, 1, coordinates(0, 2));
    tempPawns[2] = pawn(2, 2, 1, coordinates(0, 3));
    tempPawns[3] = pawn(3, 2, 0, coordinates(1, 4));
    tempPawns[4] = pawn(4, 2, 1, coordinates(2, 5));
    tempPawns[5] = pawn(5, 3, 0, coordinates(3, 2));
    tempPawns[6] = pawn(6, 3, 0, coordinates(4, 3));
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
