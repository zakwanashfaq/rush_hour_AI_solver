#pragma once
#include <map>
#include <memory>   
#include <vector>
#include <string>

enum orientation {
	vertical = 0,
	horizontal = 1
};

struct coordinates {
	int x;
	int y;
};

struct actionData {
	int pawnID;
	int actionTaken;
};

struct pawn {
	int id;
	int size;
	int orientation;
	coordinates position; // grid position
};

struct stateNode {
	int cost; // cost to reach state
	int orientation; // vertical or horizontal
	int stateEvaluationValue; // calculated by evaluateState
	stateNode * parent; // parent node that spawned this node
	actionData action; // action that spawned this node
	std::vector <std::vector<int>> gridState; // state representation
	std::map<int, pawn> pawns; // pawns map
};


class aStar
{
	
	
public:
	std::vector<stateNode> openList;
	std::vector<stateNode> closedList;

	aStar();
	
private:
	bool canFit();
	bool isNodeInClosedList();
	bool isNodeInOpenList();
	bool isLegalAction();
	bool isSameState(stateNode* a, stateNode* b);
	void startSearch();
	void refreshGrid();
	int  evaluateState(); // this is the heuristic function

};
