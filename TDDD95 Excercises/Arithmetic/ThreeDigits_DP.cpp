//https://liu.kattis.com/problems/threedigits
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

const long long m(1000);

long long myPow(long long a, long long b) {
    if (!b)
        return 1;
    if (b % 2)
        return (a * myPow((a*a) % m, b / 2)) % m;
    return myPow((a*a) % m, b / 2);
}


int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    const int maxx2{ 2000 };
    const int maxx5{ 5000 };
    vector<long long> v(maxx2 + 1);
    v[0] = 1;
    vector<vector<long long>> f;

    long long n;
    fastScan(n);

    for (int i{ 0 }, j{ 0 }, i2; i < maxx2;) {
        i2 = i, ++i;
        v[i] = (v[i2] * i) % m;
        i2 = i, ++i;
        v[i] = (v[i2] * ++j) % m;
        i2 = i, ++i;
        v[i] = (v[i2] * i) % m;
        i2 = i, ++i;
        v[i] = (v[i2] * ++j) % m;

        i2 = i, ++i;
        v[i] = v[i2];

        i2 = i, ++i;
        v[i] = (v[i2] * ++j) % m;
        i2 = i, ++i;
        v[i] = (v[i2] * i) % m;
        i2 = i, ++i;
        v[i] = (v[i2] * ++j) % m;
        i2 = i, ++i;
        v[i] = (v[i2] * i) % m;
        i2 = i, ++i;
        v[i] = v[i2], ++j;
    }

    {
        long long i, mm, nr, s, sm;
        long long j;
        long long curr;
        for (i = 5, mm = maxx5, s = maxx5 / 5, sm = n / 5; i <= n; i *= 5, mm = min(mm * 10, n), s = mm / i) {
            f.emplace_back(s + 1);
            f.back()[0] = 1;
            curr = 1;
            for (j = i, nr = 1; j <= mm; j += i, ++nr) {
                if (nr % 2 == 0 || nr % 5 == 0)
                    f.back()[nr] = curr;
                else
                    f.back()[nr] = curr = (curr * nr) % m;
            }
            f.back().back() = curr;
        }
    }

    long long o{ 1 };
    long long pot{ 0 };

    long long n2{ n }, n3;
    long long mod;
    long long nr, mm;
    while (n2 > 0) {
        mod = n2 % maxx2;
        o = (o*v[mod]) % m;
        pot += n2 / maxx2;

        n3 = 5;
        nr = 0, mm = maxx5;
        while (n3 <= n2) {
            o = (o * f[nr][(n2% mm) / n3] * myPow(f[nr].back(), n2 / mm)) % m;

            mm *= 10;
            n3 *= 5;
            ++nr;
        }

        n2 /= 10;
    }


    long long pot2(n / 2);

    n2 = 20;
    while (n2 <= n) {
        pot2 += n / n2;
        n2 *= 10;
    }

    n2 = 5;
    while (n2 <= n) {
        pot2 -= n / n2;
        n2 *= 5;
    }

    o = (o*myPow(v[maxx2], pot) * myPow(2, pot2)) % m;

    if (n > 7 && o < 100) {
        if (o < 10)
            printf("00%lld\n", o);
        else
            printf("0%lld\n", o);
    }
    else
        printf("%lld\n", o);

    return 0;
}