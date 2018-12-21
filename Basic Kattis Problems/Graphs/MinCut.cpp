//https://liu.kattis.com/problems/mincut
//Leif Eriksson
//leier318
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <random>
#include <tuple>
#include <string>
#include <functional>
#include <queue>
#include <set>
#include <unordered_set>
#include <iterator>
#include <sstream>
#include <map>
#include <bitset>
#include <stack>
#include "TakenImplementations\FastScan.cpp"
#include "Graphs\MaxFlow.cpp"

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cout.tie(nullptr);
	cin.tie(nullptr);

	int n, m, s, i, j, t, t1, t2;
	int t3;
	//while (true) {
	//input blablabla
	fs(n);
	fs(m);
	fs(s);
	fs(t);

	MaxFlowDinics<int, int> maxFlow(n);

	++m;
	while (--m) {
		//input blablabla
		fsn(t1);
		fsn(t2);
		fsn(t3);
		maxFlow.add(t1, t2, t3);
	}

	maxFlow.solve(s, t);

	set<int> minCut;
	minCut.insert(s);

	maxFlow.findMinCut(minCut, s);

	cout << minCut.size() << "\n";
	copy(minCut.begin(), minCut.end(), std::ostream_iterator<int>(cout, "\n"));

	return 0;
}