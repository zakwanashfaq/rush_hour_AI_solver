#pragma once
#include "structs.cpp"

namespace utils {
	bool canNodeFit(stateNode* state, actionData* action);
	bool isNodeInClosedList(stateNode* node, std::vector<stateNode>* openList);
	bool isNodeInOpenList(stateNode* node, std::vector<stateNode>* closedList);
	bool isLegalAction();
	bool moveForward(pawn* p, stateNode* node);
	bool moveBackward(pawn* p, stateNode* node);
	bool isSameState(stateNode* a, stateNode* b);
	void refreshGrid(stateNode* node);
	int getActionNum(pawn* p, int action);
	stateNode genarateNode();
	stateNode * copyNode(stateNode* node);
	// params are probalby wrong/unnecessary 
	int  evaluateState(std::vector <std::vector<int>>* gridState); // this is the heuristic function
};