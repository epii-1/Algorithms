//https://liu.kattis.com/problems/stringmatching
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
#include <complex>
//#include <bits/stdc++.h>

using namespace std;


int main() {
    ios::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);

    string s, p;
    char c(getchar());
    size_t pos, cpos;

    while (c != EOF) {

        p = "";
        while (c != '\n') {
            p += c;
            c = getchar();
        }

        c = getchar();
        s = "";
        while (c != '\n') {
            s += c;
            c = getchar();
        }

        cpos = 0;
        pos = s.find(p, cpos);

        while (pos != -1) {
            printf("%zu ", pos);
            cpos = pos + 1;
            pos = s.find(p, cpos);
        }
        printf("\n");
        c = getchar();
    }

    return 0;
}