#pragma once
#include "map"
#include "Grid.h"

enum orientation {
	vertical = 0,
	horizontal = 1
};

struct coordinates {
	int x;
	int y;

	coordinates() : x(-1), y(-1)
	{}

	coordinates(int _x, int _y) :
		x(_x), y(_y)
	{}
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

	pawn() :
		id(-1), size(-1), orientation(-1), position(coordinates(0, 0))
	{}

	pawn(int _id, int _size, int _orientation, coordinates _position) :
		id(_id), size(_size), orientation(_orientation), position(_position)
	{}
};

struct stateNode {
	int cost; // cost to reach state
	int stateEvaluationValue; // calculated by evaluateState
	stateNode* parent; // parent node that spawned this node
	actionData action; // action that spawned this node
	Grid gridState; // state representation
	std::map<int, pawn> pawns; // pawns map
};
