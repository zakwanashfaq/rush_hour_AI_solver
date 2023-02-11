#pragma once
#include "structs.cpp"

namespace utils {
	bool canNodeFit(std::shared_ptr<stateNode> state, actionData* action);
	bool isNodeInClosedList(std::shared_ptr<stateNode> node, std::vector<stateNode>* openList);
	bool isNodeInOpenList(std::shared_ptr<stateNode> node, std::vector<stateNode>* closedList);
	bool isLegalAction();
	bool movePlayerForward(std::shared_ptr<stateNode> node);
	bool movePlayerBackward(std::shared_ptr<stateNode> node);
	bool movePlayerLeft(std::shared_ptr<stateNode> node);
	bool movePlayerRight(std::shared_ptr<stateNode> node);
	bool moveForward(pawn* p, std::shared_ptr<stateNode> node);
	bool moveBackward(pawn* p, std::shared_ptr<stateNode> node);
	bool isSameState(std::shared_ptr<stateNode> a, std::shared_ptr<stateNode> b);
	void refreshGrid(std::shared_ptr<stateNode> node);
	int getActionNum(pawn* p, int action);
	std::shared_ptr<stateNode> genarateNode();
	std::shared_ptr<stateNode> copyNode(std::shared_ptr<stateNode> node);
	// params are probalby wrong/unnecessary 
	int  evaluateState(std::vector <std::vector<int>>* gridState); // this is the heuristic function
};