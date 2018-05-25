//https://liu.kattis.com/problems/towers
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
//#include <bits/stdc++.h>

using namespace std;

//https://www.geeksforgeeks.org/fast-io-for-competitive-programming/
template<typename T>
bool fastScan(T &number) {
    register T c;

    number = 0;

    // extract current character from buffer
    c = getchar();
    while (!(c > 47 && c < 58))
        c = getchar();

    // Keep on extracting characters if they are integers
    // i.e ASCII Value lies from '0'(48) to '9' (57)
    for (; (c > 47 && c < 58); c = getchar())
        number = number * 10 + c - 48;

    return c == '^';
}

struct Node {
    Node() : ex(100, 1.0) {}
    mutable vector<long double> ex;
    string str;
    size_t s{ 0 };
    bool skip{ false };
};

bool operator< (const Node & lhs, const Node & rhs) {
    long double lt{ 1.0 }, rt{ 1.0 }, m;

    //cout << lhs.str << " < " << rhs.str << "\n";
    for (size_t i{ max(lhs.s, rhs.s) - 1 }; i < -1; --i) {
        if (lhs.ex[i] != 1)
            lt = pow(lhs.ex[i], lt);
        if (rhs.ex[i] != 1)
            rt = pow(rhs.ex[i], rt);
        if (lt * 14 < rt)
            return true;
        if (rt * 14 < lt)
            return false;
        m = min(lt, rt);
        lt /= m;
        rt /= m;
        //cout << lt << " " << rt << "\n";
    }
    //cout << lhs.str << " < " << rhs.str << " == " << (lt < rt) << "\n";
    //cout << lt << " " << rt << "\n";
    return lt < rt;
}

int main() {
    ios::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);

    int n, i, i2, t1;
    long double j, j2, t2;
    fastScan(n);
    //vector<long double> t(100);

    //for (i = 1, j = 1.0; i < 100; ++i, ++j) {
    //    t[i] = log(j);
    //}

    vector<Node> v(n);
    bool next, cont;
    for (i = 0; i < n; ++i) {
        cont = true;
        while (cont) {
            next = fastScan(t1);
            //cout << t1 << " a\n";
            if (t1 == 1) {
                v[i].skip = true;
                if (v[i].s == 0) {
                    v[i].ex[0] = 1;
                    ++v[i].s;
                }
            }
            else if (!v[i].skip) {
                v[i].ex[v[i].s] = t1;
                ++v[i].s;
            }
            v[i].str += to_string(t1) + '^';
            cont = next;
        }
        v[i].str.pop_back();
    }

    stable_sort(v.begin(), v.end());

    printf("Case 1:\n");
    for (i = 0; i < n; ++i)
        printf("%s\n", v[i].str.c_str());


    return 0;
}


/*

12
2^2^2
3^4
15
9^2
1
2^2^1^3
2^2^2^1^1^1
100^100^100^100^100^100^100^100^100^100^100^100^100^100^100^100^100^100^100^100^100^100^100^100
99^100^100^100^100^100^100^100^100^100^100^100^100^100^100^100^100^100^100^100^100^100^100^100
100^99^100^100^100^100^100^100^100^100^100^100^100^100^100^100^100^100^100^100^100^100^100^100
100^100^100^100^100^100^100^100^100^100^100^100^100^100^100^100^100^100^100^100^100^100^100^99
100^100^100^100^100^100^100^100^100^100^100^100^100^100^100^100^100^100^100^100^100^100^99^100
*/
