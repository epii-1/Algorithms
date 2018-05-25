//https://liu.kattis.com/sessions/tgp7wb/problems/cd
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
#include <stdio.h>
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

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;

    int sell;
    int t;
    int i;
    while (true) {
        unordered_set<int> s;

        sell = 0;
        fastScan(n);
        fastScan(m);

        if (n == 0 && m == 0)
            return 0;

        while (--n > -1) {
            fastScan(t);
            s.insert(t);
        }

        while (--m > -1) {
            fastScan(t);
            sell += (s.find(t) != s.end());
        }

        printf("%d\n", sell);
    }
}

