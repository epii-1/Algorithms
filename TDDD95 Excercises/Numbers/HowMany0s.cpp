//https://liu.kattis.com/problems/howmanyzeros
//Leif Eriksson 
//leier318

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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

#define _UNLOCKED 1
#if _UNLOCKED
#define gc() getchar_unlocked()
#else
#define gc() getchar()
#endif

template<typename T>
void fs(T &number) {
    //variable to indicate sign of input number
    bool negative{ false };
    register T c;

    number = 0;

    // extract current character from buffer
    c = gc();
    while (!(c == '-' || (c > 47 && c < 58)))
        c = gc();

    if (c == '-') {
        // number is negative
        negative = true;

        // extract the next character from the buffer
        c = gc();
    }

    // Keep on extracting characters if they are integers
    // i.e ASCII Value lies from '0'(48) to '9' (57)
    for (; (c>47 && c<58); c = gc())
        number = number * 10 + c - 48;

    // if scanned input has a negative sign, negate the
    // value of the input number
    if (negative)
        number *= -1;
}

using namespace std;

long long count(long long n) {
    if (n == -1)
        return -1;
    if (n < 10)
        return 0;
    long long n10{ n / 10 };
    if (n % 10 != 9)
        return count(n10, m) * (n % 10 + 1) + count(n10 - 1, m)* (9 - n % 10) + n10;
    else
        return count(n10, m) * (n % 10 + 1) + n10;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    long long n, m;
    while (true) {
        fs(n);
        fs(m);
        if (n == -1 && m == -1)
            break;
        printf("%lld\n", count(m) - count(--n));

    }
    system("Pause");
    return 0;
}