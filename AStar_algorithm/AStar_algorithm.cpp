#include <iostream>
#include "aStar.h"

void testCanFit()
{
    stateNode tempState = utils::genarateNode();
    // generating action
    actionData mockAction;
    mockAction.pawnID = 6;
    mockAction.actionTaken = 1;
    bool result = utils::canNodeFit(&tempState, &mockAction);
}

void testCanMoveHorizontally()
{
    stateNode tempState = utils::genarateNode();
    tempState.gridState.printGrid();
    // generating action
    utils::moveForward(&tempState.pawns[1], &tempState);
    tempState.gridState.printGrid();

    //actionData mockAction2;
}

void testCanMoveVertically()
{
    stateNode tempState = utils::genarateNode();
    tempState.gridState.printGrid();
    // generating action
    utils::moveForward(&tempState.pawns[4], &tempState);
    tempState.gridState.printGrid();
    utils::moveBackward(&tempState.pawns[5], &tempState);
    tempState.gridState.printGrid();
    utils::moveBackward(&tempState.pawns[6], &tempState);
    tempState.gridState.printGrid();
    utils::moveForward(&tempState.pawns[4], &tempState);
    tempState.gridState.printGrid();
    utils::moveForward(&tempState.pawns[2], &tempState);
    tempState.gridState.printGrid();
    // check final state
    // check to see if the pawns in the corect state
    /* 
0 0 0 5 6 0
0 0 0 5 6 0
1 1 0 5 6 0
0 0 0 0 2 2
0 3 0 0 0 0
0 3 0 0 4 4
    */
}


void testCases()
{
    //testCanFit();
    //testCanMoveHorizontally();
    testCanMoveVertically();
}

int main()
{
    //testCases();
    aStar * searchObject = new aStar();
    searchObject->startSearch();
    return 1;
}
