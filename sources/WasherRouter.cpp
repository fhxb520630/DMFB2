#include <vector>
#include "Grid.h"
#include "Hash.h"
#include "WasherRouter.h"

using namespace std;

WasherRouter::WasherRouter(const State* state, int** boudary) : endState(state), boudary(boudary)
{	
	reachable = new bool**[state->step + 1];
	for (int i = 0; i <= state->step; ++i) {
		reachable[i] = new bool*[grid->getRows()];
		for (int j = 0; j < grid->getRows(); ++j) {
			reachable[i][j] = new bool[grid->getColumns()];
			for (int k = 0; k < grid->getColumns(); ++k) {
				reachable[i][j][k] = true;
			}
		}
	}
	int** belongId;
	int** belongT;
	belongId = new int*[grid->getRows()];
	belongT = new int*[grid->getRows()];
	for (int i = 0; i < grid->getRows(); ++i) {
		belongId[i] = new int[grid->getColumns()];
		belongT[i] = new int[grid->getColumns()];
		for (int j = 0; j < grid->getColumns(); ++j) {
			belongId[i][j] = -1;
			belongT[i][j] = -1;
		}
	}
	const static Point dir[9] = {Point(0, 0),
	Point(-1, 0), Point(-1, 1), Point(0, 1), Point(1, 1),
	Point(1, 0), Point(1, -1), Point(0, -1), Point(-1, -1)};
	while (state != nullptr) {
		int curStep = state->step;
		auto droplets = state->getDroplets();
		for (int i = 0; i < droplets.size(); ++i) {
			Point pos = droplets[i]->getPosition();
			for (int k = 0; k < 9; ++k) {
			Point tmp = pos + dir[k];
			if (grid->inside(tmp))
				reachable[curStep][tmp.r][tmp.c] = false;
			}
			if (belongT[pos.r][pos.c] != -1 && belongId[pos.r][pos.c] != i) {
				auto cur = Wash(pos, curStep + 1, belongT[pos.r][pos.c] - 1);
				this->washes.push_back(cur);
			}
			belongId[pos.r][pos.c] = i;
			belongT[pos.r][pos.c] = curStep;
		}
		state = state->decision;
	} 
	for (int i = 0; i < grid->getRows(); ++i) {
		delete []belongId[i];
		delete []belongT[i];
	}
	delete []belongId;
	delete []belongT;
	cerr << "the number of washes: " << this->washes.size() << endl;
}

bool WasherRouter::dfs(const WashState* state)
{
	if (state->isEndState()) {
		this->result = state;
		return true;
	} else {
		auto successors = state->getSuccessors();
		for (auto successor: successors) {
			if (this->dfs(successor)) {
				return true;
			}
		}
	}
	delete state;
	return false;
}

bool WasherRouter::Route()
{
	washHashSet.clear();
	WashState *init = new WashState;
	washHashSet.insert(init->hash());
	return dfs(init);
}

bool WasherRouter::canReach(int time, Point position) const
{
	return reachable[time][position.r][position.c];
}

vector<Wash> WasherRouter::getWashes() const
{
	return this->washes;
}

int WasherRouter::getSteps() const
{
	return this->endState->step;
}

WasherRouter* washerRouter;