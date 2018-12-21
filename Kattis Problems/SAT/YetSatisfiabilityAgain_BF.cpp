//https://liu.kattis.com/problems/satisfiability
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
//#include <bits/stdc++.h>

using namespace std;

//https://www.geeksforgeeks.org/fast-io-for-competitive-programming/
template<typename T>
char fastScan(T &number)
{
    //variable to indicate sign of input number
    bool negative = false;
    register T c;

    number = 0;

    // extract current character from buffer
    c = getchar();
    while (!(c == '-' || (c > 47 && c < 58)))
        c = getchar();

    // Keep on extracting characters if they are integers
    // i.e ASCII Value lies from '0'(48) to '9' (57)
    for (; (c>47 && c<58); c = getchar())
        number = number * 10 + c - 48;
    return c;
}

struct Comp {
    bool operator() (const vector<pair<char, char>> lhs, const vector<pair<char, char>> rhs) {
        return lhs.size() < rhs.size();
    }
};

bool sat(vector<int> & vVars, vector<vector<pair<int, bool>>> & vClau, int i) {
    if (i == vVars.size()) {
        for (int i{ 0 }; i < vClau.size(); ++i) {
            bool good{ false };
            for (int j{ 0 }; j < vClau[i].size(); ++j)
                if (vClau[i][j].second == vVars[vClau[i][j].first]) {
                    good = true;
                    break;
                }
            if (!good)
                return false;
        }
        return true;
    }
    else {
        vVars[i] = false;
        if (sat(vVars, vClau, i + 1))
            return true;
        vVars[i] = true;
        if (sat(vVars, vClau, i + 1))
            return true;
    }

    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, n, m, i, t;
    char c{ ' ' };
    bool good{ false };
    fastScan(N);
    ++N;
    while (--N) {
        fastScan(n);
        c = fastScan(m);
        vector<int> vVars;
        vector<vector<pair<int, bool>>> vClau;
        vVars.resize(n, 0);
        vClau.resize(m);

        for (i = 0; i < m; ++i) {
            vClau[i].clear();
            while (c != '~' && c != 'X') c = getchar();
            bool go = true;
            while (go) {
                while (c != '~' && c != 'X' && c != '\n') c = getchar();

                if (c == '\n')
                    go = false;
                else {

                    good = true;
                    if (c == '~') {
                        good = false;
                        c = getchar();
                    }

                    c = fastScan(t);
                    --t;
                    vClau[i].emplace_back(t, good);
                }
            }
        }

        //sort(vClau.begin(), vClau.end(), Comp());

        if (!sat(vVars, vClau, 0))
            printf("un");
        printf("satisfiable\n");
    }

    system("Pause");
    return 0;
}