//https://liu.kattis.com/problems/unionfind
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
#include "Implementations\FastScan.cpp"
#include "Data Structures\DisjointSets.cpp"

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, q;
	fs(n);
    fs(q);

    // Create disjoint sets
    DisjointSets ds(n);

    ++q;
    int set_u, set_v, u, v;
    char t;
    while (--q) {
        t = gc();
        while (t != '=' && t != '?')
            t = gc();

		fs(u);
		fs(v);
        set_u = ds.find(u);
        set_v = ds.find(v);
        if (t == '=') {
            ds.merge(set_u, set_v);
        }
        else if (t == '?') {
            if (set_u == set_v)
                puts("yes\n");
            else
                puts("no\n");
        }
    }

    return 0;
}