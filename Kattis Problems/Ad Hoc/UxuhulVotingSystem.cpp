//https://liu.kattis.com/problems/uxuhulvoting
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
void fastScan(T &number) {
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

    int n, m, m2, t, i, j, k;
    vector<vector<char>> v;

    vector<vector<char>> matrix(8, vector<char>(3));

    vector<string> output(8);
    output[0] = "NNN";
    output[1] = "NNY";
    output[2] = "NYN";
    output[3] = "NYY";
    output[4] = "YNN";
    output[5] = "YNY";
    output[6] = "YYN";
    output[7] = "YYY";

    vector<char> clear(8);
    for (i = 0; i < 8; ++i)
        clear[i] = i;

    matrix[0][0] = 1;
    matrix[0][1] = 2;
    matrix[0][2] = 4;
    matrix[1][0] = 0;
    matrix[1][1] = 3;
    matrix[1][2] = 5;

    matrix[2][0] = 0;
    matrix[2][1] = 3;
    matrix[2][2] = 6;
    matrix[3][0] = 1;
    matrix[3][1] = 2;
    matrix[3][2] = 7;

    matrix[4][0] = 0;
    matrix[4][1] = 5;
    matrix[4][2] = 6;
    matrix[5][0] = 1;
    matrix[5][1] = 4;
    matrix[5][2] = 7;

    matrix[6][0] = 2;
    matrix[6][1] = 4;
    matrix[6][2] = 7;
    matrix[7][0] = 3;
    matrix[7][1] = 5;
    matrix[7][2] = 6;

    fastScan(n);
    ++n;
    while (--n) {
        fastScan(m);

        v.resize(m, vector<char>(8));
        m2 = m;
        while (m2) {
            --m2;
            for (i = 0; i < 8; ++i) {
                fastScan(t);
                v[m2][i] = t - 1;
            }
        }

        vector<char> outcome(clear);
        vector<char> current(8);

        for (i = 0; i < m; ++i) {
            for (j = 0; j < 8; ++j) {
                char best(8);
                for (k = 0; k < 3; ++k) {
                    if (v[i][outcome[matrix[j][k]]] < best) {
                        best = v[i][outcome[matrix[j][k]]];
                        current[j] = outcome[matrix[j][k]];
                    }
                }
            }
            outcome = current;
        }
        cout << output[outcome[0]] << endl;
    }

    return 0;
}