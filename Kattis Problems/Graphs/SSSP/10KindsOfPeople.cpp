//https://liu.kattis.com/sessions/errnrk/problems/10kindsofpeople
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


int main() {
    ios::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);

    int r, c, r2, c2, i, j, t, n, s, g;

    fastScan(r);
    fastScan(c);

    vector<vector<bool>> v(r, vector<bool>(c, false));
    vector<vector<int>> v2(r, vector<int>(c, -1));
    int count = 0;

    for (i = 0; i < r; ++i) {
        for (j = 0; j < c; ++j) {
            t = getchar() - 48;
            while (t != 0 && t != 1) t = getchar() - 48;
            v[i][j] = t;
        }
    }

    fastScan(n);

    ++n;

    while (--n) {
        fastScan(c2);
        fastScan(r2);
        fastScan(s);
        fastScan(g);
        --c2;
        --r2;
        --s;
        --g;

        queue<pair<int, int>> q;

        bool found = false;

        bool start = v[c2][r2];


        if (v2[c2][r2] == -1) {
            v2[c2][r2] = count;
            q.push({ c2,r2 });
            while (!q.empty()) {
                pair<int, int> curr = q.front();
                q.pop();

                ++curr.first;
                if (curr.first < r && v[curr.first][curr.second] == start && v2[curr.first][curr.second] == -1) {
                    q.push(curr);
                    v2[curr.first][curr.second] = count;
                }
                curr.first -= 2;
                if (curr.first > -1 && v[curr.first][curr.second] == start && v2[curr.first][curr.second] == -1) {
                    q.push(curr);
                    v2[curr.first][curr.second] = count;
                }
                ++curr.first;
                ++curr.second;
                if (curr.second < c && v[curr.first][curr.second] == start && v2[curr.first][curr.second] == -1) {
                    q.push(curr);
                    v2[curr.first][curr.second] = count;
                }
                curr.second -= 2;
                if (curr.second > -1 && v[curr.first][curr.second] == start && v2[curr.first][curr.second] == -1) {
                    q.push(curr);
                    v2[curr.first][curr.second] = count;
                }
            }
            ++count;
        }


        if (v2[c2][r2] == v2[s][g]) {
            if (start)
                printf("decimal\n");
            else
                printf("binary\n");
        }
        else
            printf("neither\n");

    }

    return 0;
}
