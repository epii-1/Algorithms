//https://liu.kattis.com/problems/perfectpowers
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
    //variable to indicate sign of input number
    bool negative = false;
    register T c;

    number = 0;

    // extract current character from buffer
    c = getchar_unlocked();
    while (!(c == '-' || (c > 47 && c < 58)))
        c = getchar_unlocked();

    if (c == '-')
    {
        // number is negative
        negative = true;

        // extract the next character from the buffer
        c = getchar_unlocked();
    }

    // Keep on extracting characters if they are integers
    // i.e ASCII Value lies from '0'(48) to '9' (57)
    for (; (c>47 && c<58); c = getchar_unlocked())
        number = number * 10 + c - 48;

    // if scanned input has a negative sign, negate the
    // value of the input number
    if (negative)
        number *= -1;
}


template <typename T>
T  myPow(T a, T b) {
    if (!b)
        return 1;
    if (b % 2) {
        return a * myPow(a*a, b / 2);
    }
    return myPow(a*a, b / 2);
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout.precision(17);

    long long X;
    long long X2;
    long long r;

    while (true) {
        fastScan(X);
        if (X == 0) {
            return 0;
        }
        X2 = abs(X);
        r = 1;
        for (long long i = min(32LL, X2); i > 1; --i) {
            long long t = pow(X2, (long double) 1.0 / i);
            long long t1 = t - 1;
            long long t2 = t + 1;
            if (t != 0) {
                if (X2 % t == 0 && myPow(t, i) == X2) {
                    r = i;
                    break;
                }
                if (t1 != 0 && X2 % t1 == 0 && myPow(t1, i) == X2) {
                    r = i;
                    break;
                }
                if (X2 % t2 == 0 && myPow(t2, i) == X2) {
                    r = i;
                    break;
                }
            }
        }

        if (X < 0)
            while (r % 2 == 0)
                r /= 2;
        printf("%lld\n", r);
    }

    return 0;
}