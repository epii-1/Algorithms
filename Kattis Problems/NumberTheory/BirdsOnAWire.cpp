//https://liu.kattis.com/sessions/ghkq7h/problems/birds
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
#include <iomanip>
//#include <bits/stdc++.h>

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
    c = getchar();
    while (!(c == '-' || (c > 47 && c < 58)))
        c = getchar();

    if (c == '-')
    {
        // number is negative
        negative = true;

        // extract the next character from the buffer
        c = getchar();
    }

    // Keep on extracting characters if they are integers
    // i.e ASCII Value lies from '0'(48) to '9' (57)
    for (; (c>47 && c<58); c = getchar())
        number = number * 10 + c - 48;

    // if scanned input has a negative sign, negate the
    // value of the input number
    if (negative)
        number *= -1;
}



int main() {
    //ios::sync_with_stdio(false);
    //cout.tie(nullptr);
    //cin.tie(nullptr);

    long long n, l, d;
    long long t;
    long long z(0);
    long long tz;
    long long i;
    fastScan(l);
    fastScan(d);
    fastScan(n);

    vector<long long> v(n);

    for (i = 0; i < n; ++i) {
        fastScan(v[i]);
    }

    sort(v.begin(), v.end());

    t = 0;
    if (n > 0) {
        z = (v[0] - 6) / d;
        if (z > 0)
            t += z;
        for (i = 1; i < n; ++i) {
            z = (v[i] - v[i - 1] - d) / d;
            if (z > 0)
                t += z;
        }
        z = (l - 6 - v[n - 1]) / d;
        if (z > 0)
            t += z;
    }
    else if (l >= 12) {
        t = (l - 12) / d + 1;
    }

    printf("%lld\n", t);


    system("Pause");
    return 0;
}

