#pragma once
#include <map>
#include <memory>   
#include <vector>
#include <string>
#include "structs.cpp"
#include "utils.h"

class aStar
{
	
	
public:
	std::vector<stateNode> openList; // not sorted
	std::vector<stateNode> closedList;
	aStar();
	
private:
	stateNode root;
	bool inProgress;
	coordinates goal;

	bool isGoal();
	bool canFit(stateNode* state, actionData* action);
	bool isNodeInClosedList();
	bool isNodeInOpenList();
	bool isLegalAction();
	bool isSameState(stateNode* a, stateNode* b);
	void startSearch();
	void searchIteration();
	void refreshGrid();
	int  evaluateState(); // this is the heuristic function
	stateNode getNextNode(); // gets next node from openList;

};
