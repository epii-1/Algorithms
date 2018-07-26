//https://liu.kattis.com/problems/fenwick
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
#include <stdio.h>
#include "Implementations\FastScan.cpp"
#include "Data Structures\FenwickTree.cpp"

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, q;
    fs(n);
    fs(q);

    FenwickTree<long, int> ft(n);
    char t;
	int j;
	long u;
    ++q;
    while(--q){
        t = gc();
        while (t != '+' && t != '?')
            t = gc();
        fs(j);
        if (t == '+') {
            fsn(u);
            ft.update(j, u);
        }
        else if (t == '?')
            printf("%ld\n", ft.sum(j-1));
    }
    return 0;
}