//https://liu.kattis.com/problems/equationsolver
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
#include "Arithmetic\LinearEquation.cpp"

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);

    int n, i, j;

    vector<vector<long double>> a2;
    vector<vector<long double>*> a;
    vector<long double> b;

    while (true) {
        //Input
        fs(n);
        if (n == 0)
            break;
        //return 0;

        //Storing shits in pointers instead of vectors to not have to swap the actual vectors :)
        a2.resize(n, vector<long double>(n));
        a.resize(n);
        for (i = 0; i < n; ++i) {
            a2[i].resize(n);
            a[i] = &(a2[i]);
            for (j = 0; j < n; ++j) {
				fsnd(a2[i][j]);
            }
        }
        b.resize(n);
        for (i = 0; i < n; ++i) 
            fsnd(b[i]);

        //Solve
        Solution solved{ LinearEquation::solve(a, b) };

        //Output
		if (solved == SOLVED)
			copy(b.begin(), b.end(), ostream_iterator<long double>(cout, " "));
		else if (solved == INCONSISTENT)
			cout << "inconsistent";
		else
			cout << "multiple";
        //printf("\n");
        cout << "\n";
    }

    return 0;
}