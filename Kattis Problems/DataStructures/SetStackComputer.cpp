//https://liu.kattis.com/problems/setstack
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
#include <stack>
#include <bits/stdc++.h>

using namespace std;

map< set<int>, int > R;
map<int, set<int> > mR;
int rename(set<int> s) {
    int &ret = R[s];
    if (ret == 0)
        ret = (int)R.size(), mR[ret] = s;
    return ret;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int testcase, n;
    int a, b;
    cin >> testcase;
    ++testcase;
    string stri;
    while (--testcase) {
        cin >> n;
        stack<int> stk;
        for (int i = 0; i < n; i++) {
            cin >> stri;
            if (stri == "PUSH") {
                stk.push(rename(set<int>()));
            }
            else if (stri == "DUP") {
                stk.push(stk.top());
            }
            else if (stri == "UNION") {
                a = stk.top(), stk.pop();
                b = stk.top(), stk.pop();
                set<int> &A = mR[a], &B = mR[b], C;
                set_union(A.begin(), A.end(), B.begin(), B.end(), inserter(C, C.begin()));
                stk.push(rename(C));
            }
            else if (stri == "INTERSECT") {
                a = stk.top(), stk.pop();
                b = stk.top(), stk.pop();
                set<int> &A = mR[a], &B = mR[b], C;
                set_intersection(A.begin(), A.end(), B.begin(), B.end(), inserter(C, C.begin()));
                stk.push(rename(C));
            }
            else if (stri == "ADD") {
                a = stk.top(), stk.pop();
                b = stk.top(), stk.pop();
                set<int> B = mR[b];
                B.insert(a);
                stk.push(rename(B));
            }
            printf("%d\n", (int)mR[stk.top()].size());
        }
        puts("***");
    }

    return 0;
}