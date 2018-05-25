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
void fastScan(T &number)
{
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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, q, x, i, j, nr{ 3 }, sq{ 49 }, der{ 32 }, i2, n2;

    fastScan(n);
    fastScan(q);
    ++n;
    vector<bool> p(n + 1, 1);
    p[0] = 0;
    p[1] = 0;
    n2 = n - n % 30;

    for (i = 9; i < n; i += 6)
        p[i] = 0;
    for (i = 25; i < n; i += 10)
        p[i] = 0;

    for (i = 7; sq < n2;) {
        //7
        if (p[i]) {
            ++nr;
            i2 = i + i;
            for (j = sq; j < n; j += i2)
                p[j] = 0;
        }
        i += 4, sq += der + der + 8, der += 16;

        //11
        if (p[i]) {
            ++nr;
            i2 = i + i;
            for (j = sq; j < n; j += i2)
                p[j] = 0;
        }
        i += 2, sq += der, der += 8;

        //13
        if (p[i]) {
            ++nr;
            i2 = i + i;
            for (j = sq; j < n; j += i2)
                p[j] = 0;
        }
        i += 4, sq += der + der + 8, der += 16;

        //17
        if (p[i]) {
            ++nr;
            i2 = i + i;
            for (j = sq; j < n; j += i2)
                p[j] = 0;
        }
        i += 2, sq += der, der += 8;

        //19
        if (p[i]) {
            ++nr;
            i2 = i + i;
            for (j = sq; j < n; j += i2)
                p[j] = 0;
        }
        i += 4, sq += der + der + 8, der += 16;

        //23
        if (p[i]) {
            ++nr;
            i2 = i + i;
            for (j = sq; j < n; j += i2)
                p[j] = 0;
        }
        i += 6, sq += der + der + der + 24, der += 24;

        //29
        if (p[i]) {
            ++nr;
            i2 = i + i;
            for (j = sq; j < n; j += i2)
                p[j] = 0;
        }
        i += 2, sq += der, der += 8;

        //31
        if (p[i]) {
            ++nr;
            i2 = i + i;
            for (j = sq; j < n; j += i2)
                p[j] = 0;
        }
        i += 6, sq += der + der + der + 24, der += 24;
    }

    for (; sq < n; i += 2, sq += der, der += 8)
        if (p[i]) {
            ++nr;
            i2 = i + i;
            for (j = sq; j < n; j += i2)
                p[j] = 0;
        }

    int maxx{ min(i - i % 30 + 30,n) };

    for (; i < maxx; i += 2) {
        if (p[i])
            nr += p[i];
    }

    for (; i < n2;) {
        //1
        if (p[i])
            ++nr;

        i += 6;

        //7
        if (p[i]) {
            ++nr;
        }
        i += 4;

        //11
        if (p[i]) {
            ++nr;
        }
        i += 2;

        //13
        if (p[i]) {
            ++nr;
        }
        i += 4;

        //17
        if (p[i]) {
            ++nr;
        }
        i += 2;

        //19
        if (p[i]) {
            ++nr;
        }
        i += 4;

        //23
        if (p[i]) {
            ++nr;
        }
        i += 6;

        //29
        if (p[i]) {
            ++nr;
        }
        i += 2;
    }

    for (; i < n; i += 2) {
        if (p[i])
            nr += p[i];
    }

    printf("%d\n", nr);

    ++q;

    while (--q) {
        fastScan(x);
        if (x % 2 || x == 2) {
            printf("%d\n", p[x] ? 1 : 0);
        }
        else
            printf("0\n");
    }

    return 0;
}s