//https://liu.kattis.com/problems/primesieve
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
void fastScan(T &number) {
    //variable to indicate sign of input number
    register T c;

    number = 0;

    // extract current character from buffer
    c = getchar();
    while (!(c > 47 && c < 58))
        c = getchar();


    // Keep on extracting characters if they are integers
    // i.e ASCII Value lies from '0'(48) to '9' (57)
    for (; (c>47 && c<58); c = getchar())
        number = number * 10 + c - 48;
}

struct myBitset {
    myBitset(size_t s) {
        _s = s / 8;

        if (s % 8)
            ++_s;

        _v.resize(_s, 0);

        _c = { char(1), char(2), char(4), char(8),
            char(16), char(32), char(64), char(128) };

        _n = { char(254), char(253), char(251), char(247),
            char(239), char(223), char(191), char(127) };
    }


    myBitset(size_t s, bool val) {
        _s = s / 8;

        if (s % 8)
            ++_s;

        _v.resize(_s, 255 * val);

        _c = { char(1), char(2), char(4), char(8),
            char(16), char(32), char(64), char(128) };

        _n = { char(254), char(253), char(251), char(247),
            char(239), char(223), char(191), char(127) };
    }

    bool operator[] (size_t index) {
        return _v[index / 8] & _c[index % 8];
    }

    void set(size_t index, bool val) {
        if (val) {
            _v[index / 8] = _v[index / 8] || _c[index % 8];
        }
        else {
            _v[index / 8] = _v[index / 8] & _n[index % 8];
        }
    }

    void flip(size_t index) {
        set(index, !(_v[index / 8] & _c[index % 8]));
    }

    vector<char> _c;
    vector<char> _n;
    vector<char> _v;
    size_t _s;
};

unsigned int prime_sieve(int n, /*vector<int> & prime,*/ myBitset& p) {
    //prime.clear();
    //prime.reserve(n);
    unsigned int nr{ 0 };
    if (n >= 2)
        ++nr;
    //prime.emplace_back(2);
    int q, x, i, j, sq{ 49 }, der{ 32 }, i2, n2;

    if (n >= 3)
        ++nr;
    //prime.emplace_back(3);
    if (n >= 5)
        ++nr;
    //prime.emplace_back(5);
    //myBitset p(n+1, 1);
    p.set(0, 0);
    p.set(1, 0);

    n2 = n - n % 30;

    for (i = 9; i < n; i += 6)
        p.set(i, 0);
    for (i = 25; i < n; i += 10)
        p.set(i, 0);

    for (i = 7; sq < n2;) {
        //7
        if (p[i]) {
            ++nr;
            //prime.emplace_back(i);
            i2 = i + i;
            for (j = sq; j < n; j += i2)
                p.set(j, 0);
        }
        i += 4, sq += der + der + 8, der += 16;

        //11
        if (p[i]) {
            ++nr;
            //prime.emplace_back(i);
            i2 = i + i;
            for (j = sq; j < n; j += i2)
                p.set(j, 0);
        }
        i += 2, sq += der, der += 8;

        //13
        if (p[i]) {
            ++nr;
            //prime.emplace_back(i);
            i2 = i + i;
            for (j = sq; j < n; j += i2)
                p.set(j, 0);
        }
        i += 4, sq += der + der + 8, der += 16;

        //17
        if (p[i]) {
            ++nr;
            //prime.emplace_back(i);
            i2 = i + i;
            for (j = sq; j < n; j += i2)
                p.set(j, 0);
        }
        i += 2, sq += der, der += 8;

        //19
        if (p[i]) {
            ++nr;
            //prime.emplace_back(i);
            i2 = i + i;
            for (j = sq; j < n; j += i2)
                p.set(j, 0);
        }
        i += 4, sq += der + der + 8, der += 16;

        //23
        if (p[i]) {
            ++nr;
            //prime.emplace_back(i);
            i2 = i + i;
            for (j = sq; j < n; j += i2)
                p.set(j, 0);
        }
        i += 6, sq += der + der + der + 24, der += 24;

        //29
        if (p[i]) {
            ++nr;
            //prime.emplace_back(i);
            i2 = i + i;
            for (j = sq; j < n; j += i2)
                p.set(j, 0);
        }
        i += 2, sq += der, der += 8;

        //31
        if (p[i]) {
            ++nr;
            //prime.emplace_back(i);
            i2 = i + i;
            for (j = sq; j < n; j += i2)
                p.set(j, 0);
        }
        i += 6, sq += der + der + der + 24, der += 24;
    }

    for (; sq < n; i += 2, sq += der, der += 8)
        if (p[i]) {
            ++nr;
            //prime.emplace_back(i);
            i2 = i + i;
            for (j = sq; j < n; j += i2)
                p.set(j, 0);
        }

    int maxx{ min(i - i % 30 + 30,n) };

    for (; i < maxx; i += 2) {
        if (p[i])
            ++nr;
        //prime.emplace_back(i);
    }

    for (; i < n2;) {
        //1
        if (p[i])
            ++nr;
        //prime.emplace_back(i);

        i += 6;

        //7
        if (p[i]) {
            ++nr;
            //prime.emplace_back(i);
        }
        i += 4;

        //11
        if (p[i]) {
            ++nr;
            //prime.emplace_back(i);
        }
        i += 2;

        //13
        if (p[i]) {
            ++nr;
            //prime.emplace_back(i);
        }
        i += 4;

        //17
        if (p[i]) {
            ++nr;
            //prime.emplace_back(i);
        }
        i += 2;

        //19
        if (p[i]) {
            ++nr;
            //prime.emplace_back(i);
        }
        i += 4;

        //23
        if (p[i]) {
            ++nr;
            //prime.emplace_back(i);
        }
        i += 6;

        //29
        if (p[i]) {
            ++nr;
            //prime.emplace_back(i);
        }
        i += 2;
    }

    for (; i < n; i += 2) {
        if (p[i])
            ++nr;
        //prime.emplace_back(i);
    }
    return nr; //prime.size();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, q, x;

    fastScan(n);
    fastScan(q);
    ++n;

    myBitset p(n + 1, 1);

    printf("%zu\n", prime_sieve(n, p));
    ++q;

    while (--q) {
        fastScan(x);
        if (x % 2 || x == 2) {
            printf("%d\n", p[x] ? 1 : 0);
        }
        else
            printf("0\n");
    }
    system("Pause");
    return 0;
}