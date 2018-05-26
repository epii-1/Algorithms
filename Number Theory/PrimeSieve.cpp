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
    myBitset(size_t s, bool val = false) {
        _s = s >> 3;

        if (s & 7)
            ++_s;
        _v.resize(_s, 255 * val);
    }

    bool operator[] (size_t index) {
        return _v[index >> 3] & _c[index & 7];
    }

    void set(size_t index, bool val) {
        if (val) {
            _v[index >> 3] |= _c[index & 7];
        }
        else {
            _v[index >> 3] &= _n[index & 7];
        }
    }

    void flip(size_t index) {
        set(index, !(_v[index >> 3] & _c[index & 7]));
    }

    const static vector<char> _c;
    const static vector<char> _n;
    vector<char> _v;
    size_t _s;
};

const vector<char> myBitset::_c{ char(1), char(2), char(4), char(8),
char(16), char(32), char(64), char(128) };
const vector<char> myBitset::_n{ char(254), char(253), char(251), char(247),
char(239), char(223), char(191), char(127) };

size_t prime_sieve(int n, /*vector<int> & prime,*/ myBitset& p) {
    //prime.clear();
    //prime.reserve(n);
    size_t nr{ 0 };
    if (n >= 2)
        ++nr;
    //prime.emplace_back(2);
    //i, j, i*2, n/2, i*i/2, (i+1)*(i+1)/2-i*i/2, n2/2
    int i, j, i2, nh, sqh{ 24 }, derh{ 16 }, n2h;

    if (n >= 3)
        ++nr;
    //prime.emplace_back(3);
    if (n >= 5)
        ++nr;
    //prime.emplace_back(5);
    //myBitset p((n+1)/2, 1);
    p.set(0, 0);

    nh = n >> 1;
    n2h = (n - n % 30) >> 1;

    for (i = 4; i < nh; i += 3)
        p.set(i, 0);
    for (i = 12; i < nh; i += 5)
        p.set(i, 0);

    for (i = 3; sqh < n2h;) {
        //7
        if (p[i]) {
            ++nr;
            i2 = i + i + 1;
            //prime.emplace_back(i);

            for (j = sqh; j < nh; j += i2)
                p.set(j, 0);
        }
        sqh += derh + derh + 4, derh += 8, i += 2;

        //11
        if (p[i]) {
            ++nr;
            i2 = i + i + 1;
            //prime.emplace_back(i);

            for (j = sqh; j < nh; j += i2)
                p.set(j, 0);
        }
        sqh += derh, derh += 4, ++i;

        //13
        if (p[i]) {
            ++nr;
            i2 = i + i + 1;
            //prime.emplace_back(i);

            for (j = sqh; j < nh; j += i2)
                p.set(j, 0);
        }
        sqh += derh + derh + 4, derh += 8, i += 2;

        //17
        if (p[i]) {
            ++nr;
            i2 = i + i + 1;
            //prime.emplace_back(i);

            for (j = sqh; j < nh; j += i2)
                p.set(j, 0);
        }
        sqh += derh, derh += 4, ++i;

        //19
        if (p[i]) {
            ++nr;
            i2 = i + i + 1;
            //prime.emplace_back(i);

            for (j = sqh; j < nh; j += i2)
                p.set(j, 0);
        }
        sqh += derh + derh + 4, derh += 8, i += 2;

        //23
        if (p[i]) {
            ++nr;
            i2 = i + i + 1;
            //prime.emplace_back(i);

            for (j = sqh; j < nh; j += i2)
                p.set(j, 0);
        }
        sqh += derh + derh + derh + 12, derh += 12, i += 3;

        //29
        if (p[i]) {
            ++nr;
            i2 = i + i + 1;
            //prime.emplace_back(i);

            for (j = sqh; j < nh; j += i2)
                p.set(j, 0);
        }
        sqh += derh, derh += 4, ++i;

        //31
        if (p[i]) {
            ++nr;
            i2 = i + i + 1;
            //prime.emplace_back(i);

            for (j = sqh; j < nh; j += i2)
                p.set(j, 0);
        }
        sqh += derh + derh + derh + 12, derh += 12, i += 3;
    }

    for (; sqh < nh; sqh += derh, derh += 4, ++i)

        if (p[i]) {
            ++nr;
            i2 = i + i + 1;
            //prime.emplace_back(i);

            for (j = sqh; j < nh; j += i2)
                p.set(j, 0);
        }

    i2 = i + i + 1;
    int maxx{ min(i2 - i2 % 30 + 30,n) >> 1 };

    for (; i < maxx; ++i) {
        if (p[i])
            ++nr;
        //prime.emplace_back(i);
    }

    for (; i < n2h;) {
        //1
        if (p[i])
            ++nr;
        //prime.emplace_back(i);
        i += 3;

        //7
        if (p[i]) {
            ++nr;
            //prime.emplace_back(i);
        }
        i += 2;

        //11
        if (p[i]) {
            ++nr;
            //prime.emplace_back(i);
        }
        ++i;

        //13
        if (p[i]) {
            ++nr;
            //prime.emplace_back(i);
        }
        i += 2;

        //17
        if (p[i]) {
            ++nr;
            //prime.emplace_back(i);
        }
        ++i;

        //19
        if (p[i]) {
            ++nr;
            //prime.emplace_back(i);
        }
        i += 2;

        //23
        if (p[i]) {
            ++nr;
            //prime.emplace_back(i);
        }
        i += 3;

        //29
        if (p[i]) {
            ++nr;
            //prime.emplace_back(i);
        }
        ++i;
    }

    for (; i < nh; ++i) {
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

    myBitset p(n >> 1, 1);

    printf("%zu\n", prime_sieve(n, p));
    ++q;

    while (--q) {
        fastScan(x);
        if (x & 1) {
            printf("%d\n", p[x >> 1] ? 1 : 0);
        }
        else if (x == 2)
            printf("1\n");
        else
            printf("0\n");
    }
    system("Pause");
    return 0;
}
