//https://liu.kattis.com/problems/knapsack
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
#include "Greedy DP\Knapsack.cpp"

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	float c;

	short n, i, t1, t2;
	vector<pair<short, pair<short, short>>> v;
	while (fsndb(c)) {
		//Input
		fs(n);

		v.resize(n);
		for (i = 0; i < n; ++i) {
			fs(t1);
			fs(t2);
			v[i] = { i,{ t1, t2 } };
		}

		//This sorting seems to yield the best result
		sort(v.begin(), v.end(), 
			[](const pair<short, pair<short, short>>& lhs, const pair<short, pair<short, short>>& rhs)->bool { 
			return lhs.second.second < rhs.second.second || (lhs.second.second == rhs.second.second && lhs.second.first > rhs.second.first); 
		});
		//Solve
		vector<short> result;
		knapsack<short, short, int>(c, v, result);

		//Output
		cout << result.size() << "\n";
		copy(result.begin(), result.end(), ostream_iterator<short>(cout, " "));
		cout << "\n";
	}

	return 0;

}