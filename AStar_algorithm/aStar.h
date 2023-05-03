#pragma once
#include <map>
#include <memory>   
#include <vector>
#include <cmath>
#include <queue>
#include <string>
#include <iostream>
#include <fstream>
#include <stack>
#include "structs.cpp"
#include "utils.h"

struct CompareNode {
	bool operator()(std::shared_ptr<stateNode> a, std::shared_ptr<stateNode> b) const {
		if (a->cost > b->cost)
		{
			return true;
		}
		else if (a->cost == b->cost)
		{
			return a->stateEvaluationValue < b->stateEvaluationValue;
		}
		return false;
	}
};

class aStar
{
	
	
public:
	aStar(std::string inputFileName);
	void startSearch();
protected:
	std::shared_ptr<stateNode> root;
	std::priority_queue<std::shared_ptr<stateNode>, std::vector<std::shared_ptr<stateNode>>, CompareNode> openList;
	std::vector<std::shared_ptr<stateNode>> closedList;
	std::unordered_map<std::string, bool> closedHash;
	std::unordered_map<std::string, bool> uniqueHash;
	std::unordered_map<std::string, bool> openHash;
	int nodesSearched;
	coordinates goal;
	coordinates player;
	bool inProgress;
	int depth;
	int count = 0;

	bool isGoal(std::shared_ptr<stateNode> node);
	bool canFit(std::shared_ptr<stateNode> state, actionData* action);
	bool isNodeInClosedList();
	bool isNodeInOpenList();
	bool isLegalAction();
	bool isSameState(std::shared_ptr<stateNode> a, std::shared_ptr<stateNode> b);
	void searchIteration();
	void addToOpenList(std::shared_ptr<stateNode> node);
	int evaluateState(std::shared_ptr<stateNode> node); // this is the heuristic function
	std::shared_ptr<stateNode> getNextNode(); // gets next node from openList;

};
