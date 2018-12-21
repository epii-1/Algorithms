//https://liu.kattis.com/problems/cudak
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

vector<vector<long long>> m;

long long howMany(long long A, long long S) {
    if (A == 0) return (S == 0);

    vector<int> digit;
    while (A > 0) {
        digit.push_back(A % 10);
        A /= 10;
    }

    long long ans{ 0 };
    int sum{ 0 }, i, j;
    for (i = digit.size() - 1; i >= 0; --i) {
        for (j = 0; j < digit[i]; ++j) {
            if (S - sum - j >= 0)
                ans += m[i][S - sum - j];
        }
        sum += digit[i];
    }
    if (sum == S) ans++;
    return ans;
}

long long findFirst(long long A, long long B, long long S) {
    long long l(A), r(B), M;
    while (l < r) {
        M = (l + r) / 2;
        if (howMany(M, S) - howMany(A - 1, S) > 0) r = M;
        else l = M + 1;
    }
    return l;
}

int main() {
    ios::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);

    long long A, B, S;
    fastScan(A);
    fastScan(B);
    fastScan(S);
    m.resize(15, vector<long long>(++S, 0));

    int i, j, k;

    m[0][0] = 1;

    for (i = 1; i < 15; ++i)
        for (j = 0; j < S; ++j)
            for (k = 0; k < 10; ++k)
                if (j - k >= 0)
                    m[i][j] += m[i - 1][j - k];

    --S;
    printf("%lld\n", howMany(B, S) - howMany(A - 1, S));
    printf("%lld\n", findFirst(A, B, S));
    return 0;
}