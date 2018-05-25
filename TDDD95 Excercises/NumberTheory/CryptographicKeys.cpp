//https://liu.kattis.com/sessions/ghkq7h/problems/crypto
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

    long long n;
    long long t;
    long long z(0);
    long long tz;
    long long i;
    fastScan(n);

    if (n % 2 == 0) {
        tz = 0;
        while (n % 2 == 0) {
            ++tz;
            n /= 2;
        }
        z = tz;
        t = 2;
    }

    for (i = 3; i * i <= n; i += 2) {
        if (n % i == 0) {
            tz = 0;
            while (n % i == 0) {
                ++tz;
                n /= i;
            }
            if (tz > z) {
                z = tz;
                t = i;
            }
        }
    }
    if (n != 1 && z == 0)
        t = n;

    printf("%lld\n", t);


    system("Pause");
    return 0;
}
