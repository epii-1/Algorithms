//https://liu.kattis.com/problems/gold
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
#include <stack>
#include <set>
#include <unordered_set>
#include <iterator>
#include <sstream>
#include <map>
#include <bitset>
#include <time.h>
#include <bits/stdc++.h>

using namespace std;

//https://www.geeksforgeeks.org/fast-io-for-competitive-programming/
template<typename T>
void fastScan(T &number)
{
    register T c;

    number = 0;

    // extract current character from buffer
    c = getchar_unlocked();
    while (!(c > 47 && c < 58))
        c = getchar_unlocked();

    // Keep on extracting characters if they are integers
    // i.e ASCII Value lies from '0'(48) to '9' (57)
    for (; (c>47 && c<58); c = getchar_unlocked())
        number = number * 10 + c - 48;
}

int main() {
    ios::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);

    char W, H, c;
    int collected(0), i, j;
    fastScan(W);
    fastScan(H);

    vector<vector<char>> m(H, vector<char>(W, 0));
    vector<vector<bool>> draft(H, vector<bool>(W, false));
    vector<vector<bool>> visited(H, vector<bool>(W, false));
    stack <pair<int, int>> s;
    c = getchar_unlocked();
    for (i = 0; i < H; ++i) {
        while (!(c == 'T' || c == '#' || c == '.' || c == 'P' || c == 'G')) c = getchar_unlocked();
        for (j = 0; j < W; ++j) {
            m[i][j] = c;
            if (c == 'T') {
                draft[i - 1][j] = true;
                draft[i + 1][j] = true;
                draft[i][j - 1] = true;
                draft[i][j + 1] = true;
            }
            else if (c == 'P')
                s.emplace(i, j);
            c = getchar_unlocked();
        }
    }

    while (!s.empty()) {
        pair<int, int> p(s.top());
        s.pop();

        if (m[p.first][p.second] == 'G') ++collected;

        if (m[p.first][p.second] != '#' && !draft[p.first][p.second]) {

            if (!visited[p.first + 1][p.second]) {
                visited[p.first + 1][p.second] = true;
                s.emplace(p.first + 1, p.second);
            }
            if (!visited[p.first - 1][p.second]) {
                visited[p.first - 1][p.second] = true;
                s.emplace(p.first - 1, p.second);
            }
            if (!visited[p.first][p.second + 1]) {
                visited[p.first][p.second + 1] = true;
                s.emplace(p.first, p.second + 1);
            }
            if (!visited[p.first][p.second - 1]) {
                visited[p.first][p.second - 1] = true;
                s.emplace(p.first, p.second - 1);
            }
        }
    }

    printf("%d\n", collected);

    return 0;
}