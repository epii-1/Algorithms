//https://liu.kattis.com/problems/eulerianpath
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
#include <list>
#include "Implementations\FastScan.cpp"
#include "Graphs\EulerPath.cpp"

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cout.tie(nullptr);
	cin.tie(nullptr);

	int n, m, i, j, t1, t2;
	int m2;
	int oddOut{ 0 }, oddIn{ 0 };
	EulerianPath<int> ep;
	while (true) {
		//input blablabla
		fs(n);
		fs(m);

		if (n == 0 && m == 0)
			return 0;

		ep.resize(n);

		m2 = m;
		++m;
		oddOut = oddIn = 0;
		while (--m) {
			//input blablabla
			fs(t1);
			fs(t2);
			ep.nodes[t1].edges.emplace_back(t2);
			++ep.nodes[t1].from;
			++ep.nodes[t2].to;

			//Keeping count on odds nodes
			/*if (t1 != t2) {
			if (nodes[t1].from == nodes[t1].to + 1)
			++oddOut;
			else if (nodes[t1].from == nodes[t1].to)
			--oddIn;
			if (nodes[t2].from + 1 == nodes[t2].to)
			++oddIn;
			else if (nodes[t2].from == nodes[t2].to)
			--oddOut;
			}*/
		}

		//If there are more then 1 start, or more then 1 end,
		//Or 1 end without start
		//Or 1 start without end
		//We cant find a E-path
		//(Or if we find 2 disjoint cycles)
		list<int> l;
		if (oddIn > 1 || oddOut > 1 || oddIn != oddOut || !ep.eulerianPath(l))
			cout << "Impossible\n";

		else {
			copy(l.begin(), l.end(), std::ostream_iterator<int>(cout, " "));

			cout << "\n";
		}
	}


	return 0;
}
/*
2 3
0 1
1 0
1 0

6 8
2 3
0 1
0 2
3 4
4 0
0 1
1 0
1 3


4 4
0 1
1 2
1 3
2 3
2 2
0 1
1 0
2 1
0 1
3 6
0 1
0 0
0 1
1 0
0 0
2 0
2 2
0 1
0 0
2 2
0 0
0 1
*/