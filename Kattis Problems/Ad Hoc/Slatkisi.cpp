//https://liu.kattis.com/sessions/prsaxh/problems/slatkisi
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
#include <stack>
#include <map>
#include <bitset>
#include <bits/stdc++.h>

using namespace std;

//https://www.geeksforgeeks.org/fast-io-for-competitive-programming/
template<typename T>
bool fastScan(T &number)
{
    //variable to indicate sign of input number
    bool negative = false;
    register T c;

    number = 0;

    // extract current character from buffer
    c = getchar_unlocked();
    while (!(c == '-' || (c > 47 && c < 58) || c == EOF))
        c = getchar_unlocked();

    if (c == EOF)
        return false;

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
        T pot(0.1);
        for (; (c>47 && c<58); c = getchar_unlocked(), pot *= 0.1)
            number += (c - 48)*pot;
    }

    // if scanned input has a negative sign, negate the
    // value of the input number
    if (negative)
        number *= -1;
    return true;
}


int main() {
    //ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);


    long long c, k;
    fastScan(c);
    fastScan(k);

    long long pot10(pow(10.0, k));
    long long diff1(c%pot10), diff2(pot10 - diff1);

    if (diff1 < diff2)
        printf("%lld\n", c - diff1);
    else
        printf("%lld\n", c + diff2);

    return 0;

}
