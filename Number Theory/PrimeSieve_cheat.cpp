//https://liu.kattis.com/problems/primesieve
//Leif Eriksson 
//leier318

//https://codegolf.stackexchange.com/questions/74269/calculate-the-number-of-primes-up-to-n
//Sorry, men var tvingen att se om jag kunde knäcka den här med en del fuskande

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
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

uint64_t popcount(uint64_t v)
{
    v = (v & 0x5555555555555555ULL) + ((v >> 1) & 0x5555555555555555ULL);
    v = (v & 0x3333333333333333ULL) + ((v >> 2) & 0x3333333333333333ULL);
    v = (v & 0x0F0F0F0F0F0F0F0FULL) + ((v >> 4) & 0x0F0F0F0F0F0F0F0FULL);
    v *= 0x0101010101010101ULL;
    return v >> 56;
}

#define PPROD  3*5*7

int primecount(int limit)
{
    int i, j;
    int reps = (limit - 1) / (64 * PPROD) + 1;
    int mod_limit = reps * (64 * PPROD);
    int seek_limit = (int)ceil(sqrt(limit));
    int primecount = 0;
    int slice_count = limit / 250000 + 1;

    uint8_t *buf = (uint8_t *)malloc(mod_limit / 8 + seek_limit);
    int *primes = (int *)malloc(seek_limit * sizeof(int));

    // initialize a repeating bit-pattern to fill our sieve-memory with
    uint64_t v[PPROD];
    memset(v, 0, sizeof(v));
    for (i = 0; i<(64 * PPROD); i++)
        for (j = 2; j <= 7; j++)
            if (i % j == 0)
                v[i >> 6] |= 1ULL << (i & 0x3F);

    for (i = 0; i<reps; i++)
        memcpy(buf + 8 * PPROD*i, v, 8 * PPROD);

    // use naive E-sieve to get hold of all primes to test for
    for (i = 11; i<seek_limit; i += 2)
    {
        if ((buf[i >> 3] & (1 << (i & 7))) == 0)
        {
            primes[primecount++] = i;
            for (j = 3 * i; j<seek_limit; j += 2 * i)
                buf[j >> 3] |= (1 << (j & 7));
        }
    }

    // fill up whole E-sieve. Use chunks of about 30 Kbytes
    // so that the chunk of E-sieve we're working on
    // can fit into the L1-cache.
    for (j = 0; j<slice_count; j++)
    {
        int low_bound = ((uint64_t)limit * j) / slice_count;
        int high_bound = ((uint64_t)limit * (j + 1)) / slice_count - 1;

        for (i = 0; i<primecount; i++)
        {
            int pm = primes[i];
            // compute the first odd multiple of pm that is larger than or equal
            // to the lower bound.
            uint32_t lb2 = (low_bound + pm - 1) / pm;
            lb2 |= 1;
            if (lb2 < 3) lb2 = 3;
            lb2 *= pm;
            uint32_t hb2 = (high_bound / pm) * pm;

            uint32_t kt1 = ((lb2 + 2 * pm) >> 3) - (lb2 >> 3);
            uint32_t kt2 = ((lb2 + 4 * pm) >> 3) - (lb2 >> 3);
            uint32_t kt3 = ((lb2 + 6 * pm) >> 3) - (lb2 >> 3);

            uint32_t kx0 = 1 << (lb2 & 7);
            uint32_t kx1 = 1 << ((lb2 + 2 * pm) & 7);
            uint32_t kx2 = 1 << ((lb2 + 4 * pm) & 7);
            uint32_t kx3 = 1 << ((lb2 + 6 * pm) & 7);

            uint8_t *lb3 = buf + (lb2 >> 3);
            uint8_t *hb3 = buf + (hb2 >> 3);

            uint8_t *kp;
            for (kp = lb3; kp <= hb3; kp += pm)
            {
                kp[0] |= kx0;
                kp[kt1] |= kx1;
                kp[kt2] |= kx2;
                kp[kt3] |= kx3;
            }
        }
    }

    // flag tail elements to exclude them from prime-counting.
    for (i = limit; i<mod_limit; i++)
        buf[i >> 3] |= 1 << (i & 7);

    int sum = 0;
    uint64_t *bufx = (uint64_t *)buf;

    for (i = 0; i<mod_limit >> 6; i++)
        sum += popcount(bufx[i]);

    free(buf);
    free(primes);

    return mod_limit - sum + 3;
}

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

using namespace std;

int test(int n) {
    if (n == 2 || n == 3 || n == 5)
        return 1;
    if (!(n & 1) || n == 1)
        return 0;
    for (int i = 7; i*i <= n;) {
        //7
        if (!(n%i))
            return 0;
        i += 4;

        //11
        if (!(n%i))
            return 0;
        i += 2;

        //13
        if (!(n%i))
            return 0;
        i += 4;

        //17
        if (!(n%i))
            return 0;
        i += 2;

        //19
        if (!(n%i))
            return 0;
        i += 4;

        //23
        if (!(n%i))
            return 0;
        i += 6;

        //29
        if (!(n%i))
            return 0;
        i += 2;

        //31
        if (!(n%i))
            return 0;
        i += 6;
    }
    return 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, q, x;

    fastScan(n);
    fastScan(q);

    printf("%d\n", primecount(++n));
    ++q;

    while (--q) {
        fastScan(x);
        printf("%d\n", test(x));
    }

    system("Pause");
    return 0;
}