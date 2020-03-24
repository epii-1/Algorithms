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

using namespace std;

#define _UNLOCKED 0
#if _UNLOCKED
#define gc() getchar_unlocked()
#else
#define gc() getchar()
#endif

template<typename T>
void fastScan(T &number){
    register T c;

    number = 0;

    // extract current character from buffer
    c = gc();
    while (!(c > 47 && c < 58))
        c = gc();

    // Keep on extracting characters if they are integers
    // i.e ASCII Value lies from '0'(48) to '9' (57)
    for (; (c>47 && c<58); c = gc())
        number = number * 10 + c - 48;

    if (c == '.') {
        c = gc();
        T pot(0.1);
        for (; (c>47 && c<58); c = gc(), pot *= 0.1)
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

        auto it(m.insert({ 1, v[K - 1] }).first);

        long double start(v[K - 1]);
        long double end(v[0] * v[K - 1]);
        while (end < X) {
            for (int i(0); i < K; ++i) {
                auto check(m.insert({ start*v[i], 0 }).first);
                check->second = max(check->second, end*v[i]);
                if (check->first <= end && (it->second < check->second || it->second != end)) {
                    it = check;
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
