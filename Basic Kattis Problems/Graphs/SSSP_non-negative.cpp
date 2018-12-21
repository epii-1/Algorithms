//https://liu.kattis.com/problems/shortestpath1
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
#include "Graphs\SSSP_non-negative.cpp"

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cout.tie(nullptr);
	cin.tie(nullptr);

	int n, m, s, i, q, t1, t2;
	int t3;
	while (true) {
		//input blablabla
		fs(n);
		fs(m);
		fs(q);
		fs(s);

		if (n == 0 && m == 0 && q == 0 && s == 0)
			break;

		SingleShortestPath<int, int> ssp(n, s);

		++m;
		while (--m) {
			//input blablabla
			fs(t1);
			fs(t2);
			fs(t3);
			//Store edges, check for duplicates, only store the best
			auto it(ssp.G[t1].insert(make_pair(t2, t3)));
			if (!it.second && it.first->second > t3)
				it.first->second = t3;
		}

		++q;
		while (--q) {
			fs(t1);

			//Finaly calculate and output distance!
			if (ssp.shortestPath(t1))
				printf("%d\n", ssp.path[t1].second);
			else
				printf("Impossible\n");
		}
		printf("\n");
	}

	return 0;
}