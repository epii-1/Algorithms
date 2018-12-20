//https://liu.kattis.com/problems/maxflow
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
#include <cstring>
#include "TakenImplementations\FastScan.cpp"
#include "Graphs\MaxFlow.cpp"

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cout.tie(nullptr);
	cin.tie(nullptr);

	int n, m, s, i, j, t, t1, t2;
	int t3;

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

	int mflow(maxFlow.solve(s, t));

	vector<int> a;

	for (i = 0; i < maxFlow._nodes.size(); ++i) {
		for (j = 0; j < maxFlow._nodes[i].edges.size(); ++j) {
			if (maxFlow._nodes[i].edges[j].flow > 0) {
				a.push_back(maxFlow._nodes[i].edges[j].u);
				a.push_back(maxFlow._nodes[i].edges[j].v);
				a.push_back(maxFlow._nodes[i].edges[j].flow);
			}
		}
	}

	printf("%d %d %zu\n", n, mflow, a.size() / 3);

	for (i = 0; i < a.size(); i += 3)
		printf("%d %d %d\n", a[i], a[i + 1], a[i + 2]);

	return 0;
}

/*
4 5 0 3
0 1 10
1 2 1
1 3 1
0 2 1
2 3 10
*/