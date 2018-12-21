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
//#include <bits/stdc++.h>

using namespace std;

//https://www.geeksforgeeks.org/fast-io-for-competitive-programming/
template<typename T>
void fastScan(T &number)
{
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


    long long n, o(1), n10, two(0), five(0), i(1);
    fastScan(n);

    n10 = n - n % 10;

    for (long long j(1), t(0); i < n10;) {
        two += 4;
        o = (o * i) % 1000;
        i += 2;
        o = (o * j) % 1000;
        ++j;
        o = (o * i) % 1000;
        i += 4;
        o = (o * j) % 1000;
        ++j;

        long long t2(++t);
        ++five;
        while (t2 % 5 == 0) {
            t2 /= 5;
            ++five;
        }
        o = (o * t2) % 1000;


        o = (o * j) % 1000;
        ++j;

        o = (o * i) % 1000;
        i += 2;
        o = (o * j) % 1000;
        j += 2;
        o = (o * i) % 1000;
        ++i;
        t2 = i;
        while (t2 % 10 == 0) t2 /= 10;
        while (t2 % 5 == 0) {
            t2 /= 5;
            ++five;
        }

        o = (o*t2) % 1000;
        ++i;
        ++t;
    }

    for (; i <= n; ++i) {
        long long t(i);
        while (t % 10 == 0) t /= 10;
        while (t % 5 == 0) {
            t /= 5;
            ++five;
        }
        if (t % 2 == 0) {
            t /= 2;
            ++two;
        }

        o = (o*t) % 1000;
    }

    o = (o * myPow(2, two - five)) % 1000;

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