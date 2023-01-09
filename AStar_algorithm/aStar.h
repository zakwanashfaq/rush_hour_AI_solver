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
	aStar(std::string inputFileName);
	void startSearch();

private:
	stateNode* root;
	std::vector<stateNode*> openList; // not sorted
	std::vector<stateNode*> closedList;
	int nodesSearched;
	coordinates goal;
	bool inProgress;
	int depth;

	bool isGoal(stateNode* node);
	bool canFit(stateNode* state, actionData* action);
	bool isNodeInClosedList();
	bool isNodeInOpenList();
	bool isLegalAction();
	bool isSameState(stateNode* a, stateNode* b);
	void searchIteration();
	void addToOpenList(stateNode* node);
	int  evaluateState(); // this is the heuristic function
	stateNode* getNextNode(); // gets next node from openList;

};
