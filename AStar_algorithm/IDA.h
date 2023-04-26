#pragma once

#include "aStar.h"

struct RT
{
	std::string result;
	int threshold;

	RT()
		:result(""), threshold(0)
	{}

	RT(std::string res, int thres)
		:result(res), threshold(thres)
	{}
};

class IDAStar: public aStar
{
public:
	IDAStar(std::string inputFileName);
	void startSearch();
protected:
	std::shared_ptr<RT> search(std::shared_ptr<stateNode> node, int g_cost, int threshold);
};


