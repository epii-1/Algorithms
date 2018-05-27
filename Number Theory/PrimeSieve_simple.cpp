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
#include <bits/stdc++.h>

using namespace std;

//https://www.geeksforgeeks.org/fast-io-for-competitive-programming/
template<typename T>
void fastScan(T &number) {
    //variable to indicate sign of input number
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

struct myBitset {
    myBitset(size_t s, bool val = false) : _trueSize{ s } {
        _s = s >> 3;

        if (s & 7)
            ++_s;

        _v.resize(_s, 255 * val);
    }

    bool inline operator[] (size_t index) {
        return _v[index >> 3] & _c[index & 7];
    }

    void inline set(size_t index, bool val) {
        if (val) {
            _v[index >> 3] |= _c[index & 7];
        }
        else {
            _v[index >> 3] &= _n[index & 7];
        }
    }

    void inline flip(size_t index) {
        set(index, !(_v[index >> 3] & _c[index & 7]));
    }

    size_t count() {
        size_t nr{ 0 };
        for (size_t i{ 0 }; i < _s; ++i) {
            nr += (((_v[i] & 1) + ((_v[i] & 2) >> 1)) + (((_v[i] & 4) >> 2) + ((_v[i] & 8) >> 3))) +
                ((((_v[i] & 16) >> 4) + ((_v[i] & 32) >> 5)) + (((_v[i] & 64) >> 6) + ((_v[i] & 128) >> 7)));
        }
        for (size_t i{ _trueSize }, m{ _s << 3 }; i < m; ++i)
            nr -= operator[](i);
        return nr;
    }

    const static vector<char> _c;
    const static vector<char> _n;
    size_t _trueSize;
    size_t _s;
    vector<char> _v;
};

const vector<char> myBitset::_c{ char(1), char(2), char(4), char(8),
char(16), char(32), char(64), char(128) };
const vector<char> myBitset::_n{ char(254), char(253), char(251), char(247),
char(239), char(223), char(191), char(127) };

size_t prime_sieve(int n, /*vector<int> & prime,*/ myBitset& p) {

    //prime.clear();
    //prime.reserve(n);
    //prime.emplace_back(2);
    //i, j, i*2, n/2, i*i/2, (i+1)*(i+1)/2-i*i/2, n2/2
    int i, j;

    //prime.emplace_back(5);
    //myBitset p(i >> 1, 1);
    p.set(0, 0);

    for (i = 3; i * i <= n; i += 2) {
        if (p[i >> 1])
            for (j = i*i; j <= n; j += i + i)
                p.set(j >> 1, 0);
    }

    return p.count() + (n >= 2);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, q, x;

    fastScan(n);
    fastScan(q);
    ++n;

    myBitset p(n >> 1, 1);

    printf("%zu\n", prime_sieve(n, p));
    ++q;

    while (--q) {
        fastScan(x);
        if (x & 1) 
            printf("%d\n", p[x >> 1] ? 1 : 0);
        else if (x == 2)
            printf("1\n");
        else
            printf("0\n");
    }

    return 0;
}