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
	std::shared_ptr<stateNode> root;
	std::vector<std::shared_ptr<stateNode>> openList; // not sorted
	std::vector<std::shared_ptr<stateNode>> closedList;
	int nodesSearched;
	coordinates goal;
	bool inProgress;
	int depth;

	bool isGoal(std::shared_ptr<stateNode> node);
	bool canFit(std::shared_ptr<stateNode> state, actionData* action);
	bool isNodeInClosedList();
	bool isNodeInOpenList();
	bool isLegalAction();
	bool isSameState(std::shared_ptr<stateNode> a, std::shared_ptr<stateNode> b);
	void searchIteration();
	void addToOpenList(std::shared_ptr<stateNode> node);
	int  evaluateState(); // this is the heuristic function
	std::shared_ptr<stateNode> getNextNode(); // gets next node from openList;

};
