//https://liu.kattis.com/problems/funnygames
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
#include <sstream>
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

    if (c == '.') {
        c = getchar_unlocked();
        T pot(0.1);
        for (; (c>47 && c<58); c = getchar_unlocked(), pot *= 0.1)
            number += (c - 48)*pot;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);

    int N, K;
    long double X, F;

    fastScan(N);

    ++N;
    while (--N) {

        fastScan(X);
        fastScan(K);
        vector<long double> v(K);
        map<long double, long double> m;
        for (int i = 0; i < K; ++i) {
            fastScan(F);
            v[i] = 1.0 / F;
        }

        sort(v.begin(), v.end());

        auto it(m.insert(make_pair(1, v[K - 1])).first);

        long double start(v[K - 1]);
        long double end(v[0] * v[K - 1]);
        while (end < X) {
            for (int i(0); i < K; ++i) {
                auto check(m.insert(make_pair(start*v[i], end*v[i])));
                if (!check.second) {
                    check.first->second = max(check.first->second, end*v[i]);
                }
                if (check.first->first <= end && (it->second < check.first->second || it->second != end)) {
                    it = check.first;
                }
            }
            end = it->second;
            ++it;
            while (it != m.end() && it->first < end) {
                end = max(end, it->second);
                ++it;
            }
            if (it == m.end()) {
                --it;
                start = end;
                end = start * v[0];
            }
            else {
                start = end;
                end = min(it->first, start*v[0]);
            }
        }


        if (start < X && X < end)
            printf("Mikael\n");
        else
            printf("Nils\n");
    }

    return 0;
}
