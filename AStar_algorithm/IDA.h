#pragma once

#include "aStar.h"

struct RT
{
	std::string result;
	int threshold;
	std::shared_ptr<stateNode> node;

	RT()
		:result(""), threshold(0), node(NULL)
	{}

	RT(std::string res, int thres)
		:result(res), threshold(thres), node(NULL)
	{}

	RT(std::string res, int thres, std::shared_ptr<stateNode> node)
		:result(res), threshold(thres), node(node)
	{}
};

class IDAStar: public aStar
{
public:
	IDAStar(std::string inputFileName);
	void startSearch();
protected:
	std::shared_ptr<RT> search(std::shared_ptr<stateNode> node, int g_cost, int threshold, std::unordered_map<std::string, bool> hash);
	int evaluateState(std::shared_ptr<stateNode> node);
};


