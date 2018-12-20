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
#include <cstring>

using namespace std;

#define _UNLOCKED 1
#if _UNLOCKED
#define gc() getchar_unlocked()
#else
#define gc() getchar()
#endif

//https://www.geeksforgeeks.org/fast-io-for-competitive-programming/
template<typename T>
void fastScan(T &number) {
    //variable to indicate sign of input number
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
}

template<typename T>
void fastFill(T* v, const T& x, size_t n) {
    if (n == 0)
        return;
    size_t s(1);
    *v = x;
    while (s + s <= n) {
        memcpy((v + s), v, s * sizeof(x));
        s += s;
    }
    memcpy((v + s), v, (n - s) * sizeof(x));
}

struct myBitset {
    myBitset(size_t s, bool val = false) : _trueSize{ s }, _s((s >> 3) + bool(s & 7)), _v(_s, 255 * val) {
        //_v = new char[_s];
        //fastFill(_v, (char)(255 * val), _s);
    }

    bool inline operator[] (size_t index) const {
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

    size_t count() const {
        return count(0, _trueSize);
    }

    size_t count(const size_t from, const size_t to) const {
        const size_t _to((to >> 3) + bool(to & 7));
        size_t nr{ 0 }, i;
        for (size_t i{ from >> 3 }; i < _to; ++i) {
            nr += (((_v[i] & 1) + ((_v[i] & 2) >> 1)) + (((_v[i] & 4) >> 2) + ((_v[i] & 8) >> 3))) +
                ((((_v[i] & 16) >> 4) + ((_v[i] & 32) >> 5)) + (((_v[i] & 64) >> 6) + ((_v[i] & 128) >> 7)));
        }
        for (i = from - (from & 7); i < from; ++i)
            nr -= operator[](i);
        for (i = to; i < _to << 3; ++i)
            nr -= operator[](i);
        return nr;
    }

    //~myBitset() {
    //    delete[] _v;
    //}

    const static vector<char> _c;
    const static vector<char> _n;
    const size_t _trueSize;
    const size_t _s;
    vector<char> _v;
    //char *_v;
};

const vector<char> myBitset::_c{ char(1), char(2), char(4), char(8),
char(16), char(32), char(64), char(128) };
const vector<char> myBitset::_n{ char(254), char(253), char(251), char(247),
char(239), char(223), char(191), char(127) };

#define RETURN_PRIME true
#define PRIME_COUNT false
size_t prime_sieve(int n, 
#if RETURN_PRIME
    vector<int> & prime,
#endif
    myBitset& p) {
    //Hur mycket jag än försöker rulla ut någon av looparna verkar det inte göra någon skillnad
    //Utan count kommer den ner på 0.13s

    //Simple klarar det på 0.16s
    //0.14s utan count

    //Bra med ~200 rader kod för 0.01s :)
    //https://liu.kattis.com/submissions/2887308

    //prime.clear();
    //prime.reserve(n);
#if RETURN_PRIME
    if(n > 1)
        prime.emplace_back(2);
    if (n > 2)
        prime.emplace_back(3);
    if (n > 4)
        prime.emplace_back(5);
#endif
    //i, j, i*2, n/2, i*i/2, (i+1)*(i+1)/2-i*i/2, n2/2
    int i, j, i2, nh, sqh{ 24 }, derh{ 16 }, n2h, wall, i3;

    
    //myBitset p(i >> 1, 1);
    p.set(0, 0);

#if PRIME_COUNT
    size_t nr{ 0 };
    if (n >= 5) {
        ++nr;
        if (n >= 3) {
            ++nr;
            if (n >= 2)
                ++nr;
        }
    }
#endif

    nh = n >> 1;
    n2h = nh - 30;
    for (i = 4; i < n2h; i += 30) {
        p.set(i, 0);
        p.set(i + 15, 0);
        p.set(i + 3, 0);
        p.set(i + 18, 0);
        p.set(i + 6, 0);
        p.set(i + 21, 0);
        p.set(i + 9, 0);
        p.set(i + 24, 0);
        p.set(i + 12, 0);
        p.set(i + 27, 0);
    }
    for (; i < nh; i += 3)
        p.set(i, 0);
    for (i = 12; i < n2h; i += 30) {
        p.set(i, 0);
        p.set(i + 20, 0);
        p.set(i + 5, 0);
        p.set(i + 25, 0);
        p.set(i + 10, 0);
        p.set(i + 15, 0);
    }
    for (; i < nh; i += 5)
        p.set(i, 0);

    n2h = (n - n % 30) >> 1;

    for (i = 3; sqh < n2h;) {
        //7
        if (p[i]) {
            i2 = (i << 1) + 1;
#if RETURN_PRIME
            prime.emplace_back(i);
#endif
#if PRIME_COUNT
            ++nr;
#endif
            i3 = i2 << 3;
            wall = nh - i3;
            for (j = sqh; j < wall; j += i3) {
                p.set(j, 0);
                p.set(j + i2, 0);
                p.set(j + (i2 << 1), 0);
                p.set(j + (i2 << 1) + i2, 0);
                p.set(j + (i2 << 2), 0);
                p.set(j + (i2 << 2) + i2, 0);
                p.set(j + i3 - (i2 << 1), 0);
                p.set(j + i3 - i2, 0);
            }
            for (; j < nh; j += i2)
                p.set(j, 0);
        }
        sqh += derh + derh + 4, derh += 8, i += 2;

        //11
        if (p[i]) {
            i2 = (i << 1) + 1;
#if RETURN_PRIME
            prime.emplace_back(i);
#endif
#if PRIME_COUNT
            ++nr;
#endif
            i3 = i2 << 3;
            wall = nh - i3;
            for (j = sqh; j < wall; j += i3) {
                p.set(j, 0);
                p.set(j + i2, 0);
                p.set(j + (i2 << 1), 0);
                p.set(j + (i2 << 1) + i2, 0);
                p.set(j + (i2 << 2), 0);
                p.set(j + (i2 << 2) + i2, 0);
                p.set(j + i3 - (i2 << 1), 0);
                p.set(j + i3 - i2, 0);
            }
            for (; j < nh; j += i2)
                p.set(j, 0);
        }
        sqh += derh, derh += 4, ++i;

        //13
        if (p[i]) {
            i2 = (i << 1) + 1;
#if RETURN_PRIME
            prime.emplace_back(i);
#endif
#if PRIME_COUNT
            ++nr;
#endif
            i3 = i2 << 3;
            wall = nh - i3;
            for (j = sqh; j < wall; j += i3) {
                p.set(j, 0);
                p.set(j + i2, 0);
                p.set(j + (i2 << 1), 0);
                p.set(j + (i2 << 1) + i2, 0);
                p.set(j + (i2 << 2), 0);
                p.set(j + (i2 << 2) + i2, 0);
                p.set(j + i3 - (i2 << 1), 0);
                p.set(j + i3 - i2, 0);
            }
            for (; j < nh; j += i2)
                p.set(j, 0);
        }
        sqh += derh + derh + 4, derh += 8, i += 2;

        //17
        if (p[i]) {
            i2 = (i << 1) + 1;
#if RETURN_PRIME
            prime.emplace_back(i);
#endif
#if PRIME_COUNT
            ++nr;
#endif
            i3 = i2 << 3;
            wall = nh - i3;
            for (j = sqh; j < wall; j += i3) {
                p.set(j, 0);
                p.set(j + i2, 0);
                p.set(j + (i2 << 1), 0);
                p.set(j + (i2 << 1) + i2, 0);
                p.set(j + (i2 << 2), 0);
                p.set(j + (i2 << 2) + i2, 0);
                p.set(j + i3 - (i2 << 1), 0);
                p.set(j + i3 - i2, 0);
            }
            for (; j < nh; j += i2)
                p.set(j, 0);
        }
        sqh += derh, derh += 4, ++i;

        //19
        if (p[i]) {
            i2 = (i << 1) + 1;
#if RETURN_PRIME
            prime.emplace_back(i);
#endif
#if PRIME_COUNT
            ++nr;
#endif
            i3 = i2 << 3;
            wall = nh - i3;
            for (j = sqh; j < wall; j += i3) {
                p.set(j, 0);
                p.set(j + i2, 0);
                p.set(j + (i2 << 1), 0);
                p.set(j + (i2 << 1) + i2, 0);
                p.set(j + (i2 << 2), 0);
                p.set(j + (i2 << 2) + i2, 0);
                p.set(j + i3 - (i2 << 1), 0);
                p.set(j + i3 - i2, 0);
            }
            for (; j < nh; j += i2)
                p.set(j, 0);
        }
        sqh += derh + derh + 4, derh += 8, i += 2;

        //23
        if (p[i]) {
            i2 = (i << 1) + 1;
#if RETURN_PRIME
            prime.emplace_back(i);
#endif
#if PRIME_COUNT
            ++nr;
#endif
            i3 = i2 << 3;
            wall = nh - i3;
            for (j = sqh; j < wall; j += i3) {
                p.set(j, 0);
                p.set(j + i2, 0);
                p.set(j + (i2 << 1), 0);
                p.set(j + (i2 << 1) + i2, 0);
                p.set(j + (i2 << 2), 0);
                p.set(j + (i2 << 2) + i2, 0);
                p.set(j + i3 - (i2 << 1), 0);
                p.set(j + i3 - i2, 0);
            }
            for (; j < nh; j += i2)
                p.set(j, 0);
        }
        sqh += derh * 3 + 12, derh += 12, i += 3;

        //29
        if (p[i]) {
            i2 = (i << 1) + 1;
#if RETURN_PRIME
            prime.emplace_back(i);
#endif
#if PRIME_COUNT
            ++nr;
#endif
            i3 = i2 << 3;
            wall = nh - i3;
            for (j = sqh; j < wall; j += i3) {
                p.set(j, 0);
                p.set(j + i2, 0);
                p.set(j + (i2 << 1), 0);
                p.set(j + (i2 << 1) + i2, 0);
                p.set(j + (i2 << 2), 0);
                p.set(j + (i2 << 2) + i2, 0);
                p.set(j + i3 - (i2 << 1), 0);
                p.set(j + i3 - i2, 0);
            }
            for (; j < nh; j += i2)
                p.set(j, 0);
        }
        sqh += derh, derh += 4, ++i;

        //31
        if (p[i]) {
            i2 = (i << 1) + 1;
#if RETURN_PRIME
            prime.emplace_back(i);
#endif
#if PRIME_COUNT
            ++nr;
#endif
            i3 = i2 << 3;
            wall = nh - i3;
            for (j = sqh; j < wall; j += i3) {
                p.set(j, 0);
                p.set(j + i2, 0);
                p.set(j + (i2 << 1), 0);
                p.set(j + (i2 << 1) + i2, 0);
                p.set(j + (i2 << 2), 0);
                p.set(j + (i2 << 2) + i2, 0);
                p.set(j + i3 - (i2 << 1), 0);
                p.set(j + i3 - i2, 0);
            }
            for (; j < nh; j += i2)
                p.set(j, 0);
        }
        sqh += derh * 3 + 12, derh += 12, i += 3;
    }

    for (; sqh < nh; sqh += derh, derh += 4, ++i)
        if (p[i]) {
            i2 = (i << 1) + 1;
#if RETURN_PRIME
            prime.emplace_back(i);
#endif
#if PRIME_COUNT
            ++nr;
#endif
            i3 = i2 << 3;
            wall = nh - i3;
            for (j = sqh; j < wall; j += i3) {
                p.set(j, 0);
                p.set(j + i2, 0);
                p.set(j + (i2 << 1), 0);
                p.set(j + (i2 << 1) + i2, 0);
                p.set(j + (i2 << 2), 0);
                p.set(j + (i2 << 2) + i2, 0);
                p.set(j + i3 - (i2 << 1), 0);
                p.set(j + i3 - i2, 0);
            }
            for (; j < nh; j += i2)
                p.set(j, 0);
        }

#if RETURN_PRIME

    i2 = (i << 1) + 1;
    int maxx{ min(i2 - i2 % 30 + 30,n) >> 1 };

    for (; i < maxx; ++i) {
        if (p[i]) {
            prime.emplace_back(i);
#if PRIME_COUNT
            ++nr;
#endif
        }
    }

    for (; i < n2h;) {
        //1
        if (p[i]) {
            prime.emplace_back(i);
#if PRIME_COUNT
            ++nr;
#endif
        i += 3;

        //7
        if (p[i]) {
            prime.emplace_back(i);
#if PRIME_COUNT
            ++nr;
#endif
        }
        i += 2;

        //11
        if (p[i]) {
            prime.emplace_back(i);
#if PRIME_COUNT
            ++nr;
#endif
        }
        ++i;

        //13
        if (p[i]) {
            prime.emplace_back(i);
#if PRIME_COUNT
            ++nr;
#endif
        }
        i += 2;

        //17
        if (p[i]) {
            prime.emplace_back(i);
#if PRIME_COUNT
            ++nr;
#endif
        }
        ++i;

        //19
        if (p[i]) {
            prime.emplace_back(i);
#if PRIME_COUNT
            ++nr;
#endif
        }
        i += 2;

        //23
        if (p[i]) {
            prime.emplace_back(i);
#if PRIME_COUNT
            ++nr;
#endif
        }
        i += 3;

        //29
        if (p[i]) {
            prime.emplace_back(i);
#if PRIME_COUNT
            ++nr;
#endif
        }
        ++i;
    }

    for (; i < nh; ++i) {
        if (p[i]) {
            prime.emplace_back(i);
#if PRIME_COUNT
            ++nr;
#endif
        }
    }


#if PRIME_COUNT
    return nr;
#endif
#endif
#if PRIME_COUNT
    return p.count(i, n >> 1) + nr;
#endif
    return 1;
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