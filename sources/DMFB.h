#ifndef DFMB_H
#define DFMB_H

#include <set>
#include <map>
#include "State.h"

class DMFB {
private:
	std::map<int, int> typeMap;
	int nDroplets, nSinks, nTypes, nDispensers;
	int rows, columns;
	int* boundary[4];
	int** detector;

	DMFB(const DMFB&);
	DMFB& operator = (const DMFB&);
	void print(std::ostream&, int);
	void placeSink(int sinkCount);
	void placeDispenser(int dispenserCount);
	void placeDetector(int detectorCount);
	bool dfs(const State*);
public:
	DMFB();
	~DMFB();
	void loadSequencingGraph();
	void loadModuleLibrary();
	void loadDesignObejective();
	void solve();
	void printPlace(std::ostream&);
	int getDropletNumber() const;
};

extern int *leastTime;
extern DMFB *DMFBsolver;
extern std::vector<int> type;

#endif	//DFMB_H