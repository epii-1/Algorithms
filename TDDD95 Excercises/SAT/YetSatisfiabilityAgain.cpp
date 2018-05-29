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

using namespace std;

//https://www.geeksforgeeks.org/fast-io-for-competitive-programming/
template<typename T>
char fastScan(T &number) {
    //variable to indicate sign of input number
    bool negative{ false };
    register T c;

    number = 0;

    // extract current character from buffer
    c = getchar_unlocked();
    while (!(c == '-' || (c > 47 && c < 58)))
        c = getchar_unlocked();

    // Keep on extracting characters if they are integers
    // i.e ASCII Value lies from '0'(48) to '9' (57)
    for (; (c>47 && c<58); c = getchar_unlocked())
        number = number * 10 + c - 48;
    return c;
}

struct Comp {
    bool operator() (const vector<pair<int, char>> lhs, const vector<pair<int, char>> rhs) {
        return lhs.size() < rhs.size();
    }
};

bool sat(vector<char> & vVars, const vector<vector<pair<int, char>>> & vClau, int i) {
    if (i >= vClau.size())
        return true;
    int j;
    int s;
    int v;
    s = vClau[i].size();
    bool existsZero{ false };
    for (j = 0; j < s; ++j)
        if (vVars[vClau[i][j].first] == vClau[i][j].second)
            return sat(vVars, vClau, i + 1);
        else if (!vVars[vClau[i][j].first])
            existsZero = true;
    if (existsZero) {
        vector<char> vVarsCopy(vVars);
        for (j = 0; j < s; ++j) {
            v = vClau[i][j].first;

            if (!vVarsCopy[v]) {
                vVarsCopy[v] = vClau[i][j].second;
                if (sat(vVarsCopy, vClau, i + 1))
                    return true;
                vVarsCopy[v] = -vClau[i][j].second;
            }
            else if (vVarsCopy[v] == vClau[i][j].second)
                if (sat(vVarsCopy, vClau, i + 1))
                    return true;
        }
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
    Comp comp();
    fastScan(N);
    ++N;
    vector<char> vVars;
    vector<vector<pair<int, char>>> vClau;

    while (--N) {
        fastScan(n);
        c = fastScan(m);
        fill(vVars.begin(), min(vVars.end(), vVars.begin()+n), 0);
        vVars.resize(n, 0);
        vClau.resize(m);

        for (i = 0; i < m; ++i) {
            vClau[i].clear();
            while (c != '~' && c != 'X') c = getchar_unlocked();
            bool go = true;
            while (go) {
                while (c != '~' && c != 'X' && c != '\n') c = getchar_unlocked();

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
                    vClau[i].emplace_back(t, -1 + 2 * good);
                }
            }
        }

        sort(vClau.begin(), vClau.end(), Comp());

        if (!sat(vVars, vClau, 0))
            printf("un");
        printf("satisfiable\n");
    }

    return 0;
}