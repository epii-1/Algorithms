//https://liu.kattis.com/problems/suffixsorting
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
#include <bits/stdc++.h>

using namespace std;

//https://www.geeksforgeeks.org/fast-io-for-competitive-programming/
template<typename T>
bool fastScan(T &number) {
    register T c;

    number = 0;

    // extract current character from buffer
    c = getchar();
    while (!((c > 47 && c < 58) || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')))
        c = getchar_unlocked();

    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return false;

    // Keep on extracting characters if they are integers
    // i.e ASCII Value lies from '0'(48) to '9' (57)
    for (; (c > 47 && c < 58); c = getchar_unlocked())
        number = number * 10 + c - 48;
    return true;
}

struct suffixsorting {
    const string s;
    vector<size_t>* v;

    suffixsorting(const string & sIn, vector<size_t>* v) : s(sIn), v(v), c(this) {
        size_t oldSize{ v->size() };
        v->resize(sIn.length());
        if (sIn.length() > oldSize) {
            for (size_t i{ oldSize }; i < sIn.length(); ++i)
                v->at(i) = i;
        }


        sort(v->begin(), v->end(), c);
    }

    size_t getSuffix(size_t i) {
        return v->at(i);
    }

    struct comperator {
        const suffixsorting* s;

        comperator(suffixsorting* s) {
            this->s = s;
        }

        bool const operator()(size_t lhs, size_t rhs) {
            return s->s.compare(lhs, string::npos, s->s, rhs, string::npos) < 0;
        }
    };

    comperator c;
};

int main() {
    ios::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);

    string s;
    char c(getchar_unlocked());
    int i, j, k;
    vector<size_t> v;
    while (c != EOF && c != '1') {
        s = "";
        while (c != '\n') {
            s += c;
            c = getchar_unlocked();
        }

        suffixsorting ss(s, &v);

        fastScan(j);
        for (k = 0; k < j; ++k) {
            fastScan(i);
            printf("%zu ", ss.getSuffix(i));
        }
        printf("\n");
        c = getchar_unlocked();
    }

    return 0;
}

/*
4 5 0 3
0 1 10
1 2 1
1 3 1
0 2 1
2 3 10
*/

