//https://liu.kattis.com/sessions/errnrk/problems/brexit
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
#include <bits/stdc++.h>

using namespace std;

//https://www.geeksforgeeks.org/fast-io-for-competitive-programming/
template<typename T>
void fastScan(T &number)
{
    //variable to indicate sign of input number
    bool negative = false;
    register T c;

    number = 0;

    // extract current character from buffer
    c = getchar_unlocked();
    while (!(c == '-' || (c > 47 && c < 58)))
        c = getchar_unlocked();

    if (c == '-')
    {
        // number is negative
        negative = true;

        // extract the next character from the buffer
        c = getchar_unlocked();
    }

    // Keep on extracting characters if they are integers
    // i.e ASCII Value lies from '0'(48) to '9' (57)
    for (; (c>47 && c<58); c = getchar_unlocked())
        number = number * 10 + c - 48;

    // if scanned input has a negative sign, negate the
    // value of the input number
    if (negative)
        number *= -1;
}

struct Node {
    vector<int> t;
    int c{ 0 };
    bool m{ false };
};

int main() {
    ios::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);


    int C, P, X, L, t1, t2;
    fastScan(C);
    fastScan(P);
    fastScan(X);
    fastScan(L);

    --X;
    --L;

    if (X == L) {
        printf("leave\n");
        return 0;
    }

    vector<Node> v(C);

    ++P;
    while (--P) {
        fastScan(t1);
        fastScan(t2);
        --t1;
        --t2;
        v[t1].t.push_back(t2);
        v[t2].t.push_back(t1);
    }

    stack<int> s;

    v[L].m = true;

    s.push(L);

    while (!s.empty()) {
        int c = s.top();
        s.pop();
        //cout << c << "\n";
        for (int i = 0; i < v[c].t.size(); ++i) {
            //cout << " " << v[c].t[i] << "\n";
            ++v[v[c].t[i]].c;
            if (v[v[c].t[i]].c * 2 >= v[v[c].t[i]].t.size() && !v[v[c].t[i]].m) {
                v[v[c].t[i]].m = true;
                s.push(v[c].t[i]);
                if (v[c].t[i] == X) {
                    printf("leave\n");
                    return 0;
                }
            }
        }

    }


    printf("stay\n");
    return 0;
}
