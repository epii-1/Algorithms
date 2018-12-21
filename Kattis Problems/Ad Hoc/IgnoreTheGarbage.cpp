//https://liu.kattis.com/problems/ignore
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

    // if scanned input has a negative sign, negate the
    // value of the input number
    if (negative)
        number *= -1;
    return true;
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout.precision(17);

    long long k;
    vector<char> v{ '0','1','2','5','9','8','6' };
    string o;
    while (fastScan(k)) {
        o = "";
        while (k > 0) {
            o += v[k % 7];
            k /= 7;
        }
        printf("%s\n", o.c_str());
    }
    return 0;
}