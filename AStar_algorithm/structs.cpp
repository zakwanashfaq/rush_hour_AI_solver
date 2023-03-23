#pragma once
#include <chrono>
#include <memory>
#include <string>
#include <unordered_map> 

#include "map"
#include "Grid.h"

// enums
const int VERTICAL = 0;
const int HORIZONTAL = 1;
const int DOWN = 1;
const int UP = -1;
const int RIGHT = 2;
const int LEFT = -2;
const int FORWARD = 11;
const int BACKWARD = -11;

// evaluation config enums
const int DEPTH_FACTOR = 4;
const int MAX_EVAL_VALUE = 10;

// structs
struct coordinates {
	int x;
	int y;

	coordinates() 
		: x(-1), y(-1)
	{}

	coordinates(int _x, int _y) 
		: x(_x), y(_y)
	{}
};

struct actionData {
	int pawnID;
	int actionTaken;

	actionData()
		: pawnID(-1), actionTaken(-1)
	{}

	actionData(int id, int action) 
		: pawnID(id), actionTaken(action)
	{}
};

struct pawn {
	int id;
	int size;
	int orientation;
	coordinates position; // grid position

	pawn() 
		: id(-1), size(-1), orientation(-1), position(coordinates(0, 0))
	{}

	pawn(int _id, int _size, int _orientation, coordinates _position) 
		: id(_id), size(_size), orientation(_orientation), position(_position)
	{}
};

struct stateNode {
	int cost; // cost to reach state
	int stateEvaluationValue; // calculated by evaluateState
	std::shared_ptr<stateNode> parent; // parent node that spawned this node
	actionData action; // action that spawned this node
	std::shared_ptr<Grid> gridState; // state representation
	std::map<int, pawn> pawns; // pawns map
	coordinates player;

	stateNode()
		//: cost(-1), stateEvaluationValue(-1), parent(NULL), action(NULL), gridState(NULL), pawns(NULL)
	{}

	stateNode(int c, int eval, std::shared_ptr<stateNode> node, actionData parentAction, std::shared_ptr<Grid> g, std::map<int, pawn> pawnMap)
		: cost(c), stateEvaluationValue(eval), parent(node), action(parentAction), gridState(g), pawns(pawnMap)
	{}
};
