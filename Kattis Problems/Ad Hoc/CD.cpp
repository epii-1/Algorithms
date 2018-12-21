//https://liu.kattis.com/sessions/tgp7wb/problems/cd
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
//#include <bits/stdc++.h>

using namespace std;

//https://www.geeksforgeeks.org/fast-io-for-competitive-programming/
template<typename T>
void fastScan(T &number) {
    register T c;

    number = 0;

    // extract current character from buffer
    c = getchar();
    while (!(c > 47 && c < 58))
        c = getchar();

    // Keep on extracting characters if they are integers
    // i.e ASCII Value lies from '0'(48) to '9' (57)
    for (; (c>47 && c<58); c = getchar())
        number = number * 10 + c - 48;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;

    int sell;
    int t;
    int i;
    int j;
    vector<int> v;
    while (true) {

        sell = 0;
        fastScan(n);
        fastScan(m);
        v.resize(n);

        if (n == 0 && m == 0)
            return 0;

        for (i = 0; i < n; ++i)
            fastScan(v[i]);

        j = 0;
        for (i = 0; i < m; ++i) {
            fastScan(t);
            while (v[j] < t)
                ++j;
            if (v[j] == t)
                ++sell;
        }

        printf("%d\n", sell);
    }
}