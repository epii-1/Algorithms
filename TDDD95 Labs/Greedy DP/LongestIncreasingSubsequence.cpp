//https://liu.kattis.com/problems/longincsubseq
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
#include "Greedy DP\LongestIncreasingSubsequence.cpp"

using namespace std;


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int n, i, t;

	vector<int> v;
	while (fsb(n)) {
		//Input
		v.resize(n);
		for (i = 0; i < n; ++i)
			fsn(v[i]);

		//Solve
		lis<int>(n, v);

		//Output
		cout << v.size() << "\n";
		copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
		cout << "\n";
	}

	return 0;

}