#pragma once

#include "State.h"
#include "Wash.h"
#include "WashState.h"

class WasherRouter {
private:
	std::vector<Wash> washes;
	std::vector<Wash> *wash;
	bool*** reachable;	//reachable[t][r][c]表示在t时刻，格子(r,c)没有被规划好的路径占据
	const WashState* result;
	const State* endState;
public:
	WasherRouter(const State* endState);	//构造函数传入最后的状态，计算出所有的清洗任务装入wash中，同时计算计算各个时刻每个格子的reachalbe
	bool Route(int** boudary);
	bool dfs(const WashState*);
	bool canReach(int time, Point position) const;
	int getSteps() const;
	std::vector<Wash> getWashes() const;
};

extern WasherRouter* washerRouter;
