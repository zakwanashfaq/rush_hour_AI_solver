#pragma once
#include "structs.cpp"

namespace utils {
	bool canNodeFit(stateNode* state, actionData* action);
	bool isNodeInClosedList(stateNode* node, std::vector<stateNode>* openList);
	bool isNodeInOpenList(stateNode* node, std::vector<stateNode>* closedList);
	bool isLegalAction();
	bool isSameState(stateNode* a, stateNode* b);
	void refreshGrid(stateNode* node);
	stateNode genarateNode();
	// params are probalby wrong/unnecessary 
	int  evaluateState(std::vector <std::vector<int>>* gridState); // this is the heuristic function
};