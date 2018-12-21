//https://liu.kattis.com/problems/minspantree
//Leif Eriksson 
//leier318

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <random>
#include <iterator>
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
#include "Implementations\FastScan.cpp"
#include "Graphs\MinSpanningTree.cpp"

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cout.tie(nullptr);
	cin.tie(nullptr);

	int m, u, v;
	size_t n;
	int c;
	vector<vector<pair<int, int>>> nodes;
	vector<pair<int, int>> mstEdges;
	while (true) {
		fs(n);
		fs(m);

		if (n == 0 && m == 0)
			break;

		nodes.clear();
		nodes.resize(n);

		++m;
		while (--m) {
			fs(u);
			fs(v);
			fsn(c);
			nodes[u].emplace_back(v, c);
			nodes[v].emplace_back(u, c);
		}

		mstEdges.clear();

		pair<bool, int> success(minSpanningTree_Prim(nodes, n, mstEdges));

		if (!success.first) {
			printf("Impossible\n");
		}
		else {
			printf("%d\n", success.second);
			sort(mstEdges.begin(), mstEdges.end(),
				[](const pair<int, int>& lhs, const pair<int, int>& rhs)->
				bool {return lhs.first < rhs.first ||
				(lhs.first == rhs.first && lhs.second < rhs.second); });
			for (pair<int, int> p : mstEdges)
				printf("%d %d\n", p.first, p.second);
		}

	}

	return 0;
}