//https://liu.kattis.com/problems/shortestpath2
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
#include "Graphs\SSSP_time_table.cpp"

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cout.tie(nullptr);
	cin.tie(nullptr);

	int n, m, s, i, q, u, v, t0, P, d;
	long long t3;
	while (true) {
		//input blablabla
		fs(n);
		fs(m);
		fs(q);
		fs(s);

		if (n == 0 && m == 0 && q == 0 && s == 0)
			break;

		SingleShortestPathTime<int, int> ssp(n, s);

		++m;
		while (--m) {
			//input blablabla
			fs(u);
			fs(v);
			fs(t0);
			fs(P);
			fs(d);
			//Store edges
			ssp.G[u].emplace_back(v, make_tuple(t0, P, d));
		}

		++q;
		while (--q) {
			fs(u);

			//Finaly calculate and output distance!
			if (ssp.shortestPath(u))
				printf("%lld\n", ssp.path[u].second);
			else
				printf("Impossible\n");
		}
		printf("\n");
	}

	return 0;
}