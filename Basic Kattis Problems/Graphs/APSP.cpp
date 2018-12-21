//https://liu.kattis.com/problems/allpairspath
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
#include "Implementations\FastScan.cpp"
#include "Graphs\APSP.cpp"

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cout.tie(nullptr);
	cin.tie(nullptr);

	short n, m, i, q, t1, t2;
	int t3;
	while (true) {
		//input blablabla
		fs(n);
		fs(m);
		fs(q);

		if (n == 0 && m == 0 && q == 0)
			break;

		AllShotestPathFloydWarshall<int, short> asp(n);

		++m;
		while (--m) {
			//input blablabla
			fastScan(t1);
			fastScan(t2);
			fastScan(t3);
			if (t3 < asp._dist[t1][t2])
				asp._dist[t1][t2] = t3;
		}

		asp.solve();

		++q;
		while (--q) {
			fs(t1);
			fs(t2);

			pair<short, int> solution(asp.getDist(t1, t2));
			if (solution.first == -1)
				printf("-Infinity\n");
			else {
				if (solution.first == 1)
					printf("Impossible\n");
				else
					printf("%d\n", solution.second);
			}
		}
		printf("\n");
	}

	return 0;
}

/*


5 4 4
0 1 999
1 2 -2
2 1 1
0 3 2
0 1
2 2
0 3
0 4
*/