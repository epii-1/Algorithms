//https://liu.kattis.com/problems/modulararithmetic
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
char fastScan(T &number) {
    register T c;

    number = 0;

    // extract current character from buffer
    c = getchar();
    while (!(c == '-' || (c > 47 && c < 58)))
        c = getchar();

    // Keep on extracting characters if they are integers
    // i.e ASCII Value lies from '0'(48) to '9' (57)
    for (; (c>47 && c<58); c = getchar())
        number = number * 10 + c - 48;
    return c;
}

//Should change this some day if I got the time
long long gcdExtended(long long a, long long b, long long& x, long long& y) {
    // Base Case
    if (a == 0) {
        x = 0, y = 1;
        return b;
    }

    long long x1, y1; // To store results of recursive call
    long long gcd{ gcdExtended(b%a, a, &x1, &y1) };

    // Update x and y using results of recursive call
    x = y1 - (b / a) * x1;
    y = x1;

    return gcd;
}

long long modInverse(long long b, long long m) {
    long long x, y; // used in extended GCD algorithm
    long long g { gcdExtended(b, m, &x, &y)\;

    // Return -1 if b and m are not co-prime
    if (g != 1)
        return -1;

    // m is added to handle negative x
    return (x%m + m) % m;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);


    long long n, t, x, y;
    char c{ ' ' };
    bool good{ false };
    while (true) {
        fastScan(n);
        fastScan(t);
        if (n == 0 && t == 0)
            break;
        ++t;
        while (--t) {
            fastScan(x);
            c = getchar();
            fastScan(y);

            switch (c) {
            case '-':
                y = -y;
            case '+':
                printf("%lld\n", ((x + y) % n + n) % n);
                break;
            case '/':
                y = modInverse(y, n);
                if (y == -1) {
                    printf("-1\n");
                    break;
                }
            case '*':
                printf("%lld\n", (x * y) % n);
                break;
            }
        }
    }

    system("Pause");
    return 0;
}