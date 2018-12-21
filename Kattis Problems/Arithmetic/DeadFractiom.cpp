//https://liu.kattis.com/problems/deadfraction
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
//#include <bits/stdc++.h>

using namespace std;

//https://www.geeksforgeeks.org/fast-io-for-competitive-programming/
template<typename T, typename D>
void fastScan(T &number, D &size, D &pot)
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

    if (c == '.') {
        c = getchar_unlocked();
        for (; (c>47 && c<58); c = getchar_unlocked(), ++size, pot *= 10)
            number = number * 10 + c - 48;
    }

    // if scanned input has a negative sign, negate the
    // value of the input number
    if (negative)
        number *= -1;
}

template<typename T>
T gcd(T a, T b) {
    if (b == 0 || b == 1)
        return 1;

    if (a%b)
        return gcd(b, a%b);

    return b;
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout.precision(17);

    unsigned long long d;
    unsigned long long s;
    unsigned long long a;
    unsigned long long b;
    unsigned long long t;
    int i;
    unsigned long long pot, pot2, pot3;
    unsigned long long ob, oa;
    unsigned long long g;
    while (true) {
        pot3 = 1;
        s = 0;
        fastScan(d, s, pot3);
        ob = std::numeric_limits<long long>::max();
        if (d == 0)
            return 0;

        for (i = 0, pot2 = 10, pot = 1; i < s; ++i, pot = pot2, pot2 *= 10) {
            a = d * pot2 + d % pot2 - d;
            b = (pot2 - 1)*pot3;
            g = gcd(a, b);
            b /= g;
            a /= g;
            if (b < ob)
                ob = b, oa = a;
        }
        printf("%lld/%lld \n", oa, ob);

    }

    return 0;
}