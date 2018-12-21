//https://liu.kattis.com/problems/happyprime
//Leif Eriksson
//leier318
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <random>
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
#include <stack>
#include <complex>
//#include <bits/stdc++.h>

using namespace std;

//https://www.geeksforgeeks.org/fast-io-for-competitive-programming/
template<typename T>
void fastScan(T &number) {
    register T c;

    bool negative{ false };
    number = 0;

    // extract current character from buffer
    c = getchar();
    while (!(c > 47 && c < 58) && c != '-')
        c = getchar();

    if (c == '-') {
        negative = true;
        c = getchar();
    }

    // Keep on extracting characters if they are integers
    // i.e ASCII Value lies from '0'(48) to '9' (57)
    for (; (c > 47 && c < 58); c = getchar())
        number = number * 10 + c - 48;

    if (negative)
        number = -number;
}

void prime(int n, vector<bool> &p) {
    int i, j, sq{ 49 }, der{ 32 }, i2, n2;
    p[0] = 0;
    p[1] = 0;
    n2 = n - n % 30;

    //for (i = 4; i < n; i += 2)
    //    p[i] = 0;
    for (i = 9; i < n; i += 6)
        p[i] = 0;
    for (i = 25; i < n; i += 10)
        p[i] = 0;

    for (i = 7; sq < n2;) {
        //7
        if (p[i]) {
            i2 = i + i;
            for (j = sq; j < n; j += i2)
                p[j] = 0;
        }
        i += 4, sq += der + der + 8, der += 16;

        //11
        if (p[i]) {
            i2 = i + i;
            for (j = sq; j < n; j += i2)
                p[j] = 0;
        }
        i += 2, sq += der, der += 8;

        //13
        if (p[i]) {
            i2 = i + i;
            for (j = sq; j < n; j += i2)
                p[j] = 0;
        }
        i += 4, sq += der + der + 8, der += 16;

        //17
        if (p[i]) {
            i2 = i + i;
            for (j = sq; j < n; j += i2)
                p[j] = 0;
        }
        i += 2, sq += der, der += 8;

        //19
        if (p[i]) {
            i2 = i + i;
            for (j = sq; j < n; j += i2)
                p[j] = 0;
        }
        i += 4, sq += der + der + 8, der += 16;

        //23
        if (p[i]) {
            i2 = i + i;
            for (j = sq; j < n; j += i2)
                p[j] = 0;
        }
        i += 6, sq += der + der + der + 24, der += 24;

        //29
        if (p[i]) {
            i2 = i + i;
            for (j = sq; j < n; j += i2)
                p[j] = 0;
        }
        i += 2, sq += der, der += 8;

        //31
        if (p[i]) {
            i2 = i + i;
            for (j = sq; j < n; j += i2)
                p[j] = 0;
        }
        i += 6, sq += der + der + der + 24, der += 24;
    }

    for (; sq < n; i += 2, sq += der, der += 8)
        if (p[i]) {
            i2 = i + i;
            for (j = sq; j < n; j += i2)
                p[j] = 0;
        }
}

char func(int n, vector<char>& h) {
    if (n == 1)
        return 1;
    if (n < 10001) {
        if (h[n] != 0)
            return h[n];
        h[n] = -1;
    }
    int n2{ n };
    int s{ 0 }, t;

    while (n > 0) {
        t = n % 10;
        s += t*t;
        n /= 10;
    }

    char a{ func(s,h) };

    if (n2 < 10001)
        h[n2] = a;
    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);

    int P, k, m;
    char a;

    vector<bool> p(10001, 1);
    vector<char> h(10001, 0);

    prime(10001, p);

    fastScan(P);

    ++P;
    while (--P) {
        fastScan(k);
        fastScan(m);
        if (!p[m] || m % 2 == 0) {
            printf("%d %d NO\n", k, m);
        }
        else {
            a = func(m, h);
            if (a == 1)
                printf("%d %d YES\n", k, m);
            else
                printf("%d %d NO\n", k, m);
        }
    }

    return 0;
}