#include <iostream>
#include "aStar.h"
#include "IDA.h"

void testCanMoveVertically()
{
    std::shared_ptr<stateNode> tempState = utils::genarateNode();
    tempState->gridState->printGrid();
    // generating action
    utils::moveForward(&tempState->pawns[4], tempState);
    tempState->gridState->printGrid();
    utils::moveBackward(&tempState->pawns[5], tempState);
    tempState->gridState->printGrid();
    utils::moveBackward(&tempState->pawns[6], tempState);
    tempState->gridState->printGrid();
    utils::moveForward(&tempState->pawns[4], tempState);
    tempState->gridState->printGrid();
    utils::moveForward(&tempState->pawns[2], tempState);
    tempState->gridState->printGrid();
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
    auto startTime = std::chrono::high_resolution_clock::now();
    aStar * searchObject = new aStar("input.txt");
    searchObject->startSearch();
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
    std::cout << "Time taken A*: " << duration << " microseconds" << " ";
    std::cout << (duration / 1000000) << " seconds" << std::endl;

    auto startTime2 = std::chrono::high_resolution_clock::now();
    IDAStar* searchObject2 = new IDAStar("input.txt");
    searchObject2->startSearch();
    auto endTime2 = std::chrono::high_resolution_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(endTime2 - startTime2).count();
    std::cout << "Time taken IDA*: " << duration2 << " microseconds" << " ";
    std::cout << (duration2 / 1000000) << " seconds" << std::endl;
    
    return 1;
}
