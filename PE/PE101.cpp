//Leif Eriksson
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
#include <list>

using namespace std;

void getVal(long long t, long long mult, long long cVal, vector<long long> & v, const vector<long long> & w) {
	//cout << t << " " << w[t] << " " << cVal << " " << mult << "\n";
	v[t] = (w[t] - cVal) / mult;
	//cout << t << ":" << v[t] << "\n";
}

long long calc(long long x, long long i, const vector<long long> & v) {
	if (x > i)
		return 0;
	long long t(v[x] + (i - x)*calc(x + 1, i, v));
	//cout << x << " : " << v[x] << " " << t << "\n";
	return t;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	vector<long long> v(25);
	vector<long long> w(25);
	for (long long x(0); x < 25; ++x) {
		w[x-1] = (1 - x * (1 - x * (1 - x * (1 - x * (1 - x * (1 - x * (1 - x * (1 - x * (1 - x * (1 - x))))))))));
		cout << w[x-1] << " ";
	}
	cout << "\n\n";
	long long m(1);
	long long s(0);
	for (long long x(0); x < 10; ++x) {
		cout << x << "\n";
		if (x == 0)
			v[x] = w[x] / m;
		else {
			v[x] = (w[x] - calc(0, x, v)) / m;
		}

		for (long long i(x); true; ++i) {
			long long t(calc(0, i, v));
			if (t != w[i]) {
				cout << x << " " << i << " " << t << " " << w[i] << "\n";
				s += t;
				break;
			}
		}
		m *= (x + 1);
	}

	cout << s << "\n";
	system("Pause");

}

/*
0 1 1
1 1 1
2 683 683
3 44287 44287
4 838861 838861
5 8138021 8138021
6 51828151 51828151
7 247165843 247165843
8 954437177 954437177
9 3138105961 3138105961
10 9090909091 9090909091
11 23775972551 23775972551
12 57154490053 57154490053
13 128011456717 128011456717
14 269971011311 269971011311

*/