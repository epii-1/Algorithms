//https://liu.kattis.com/sessions/prsaxh/problems/walrusweights
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

int knapsack(int c, vector<int> & valueAweight) {
    //Contains current value and index vector
    vector<bool> dynamicVector(c + 1, false);

    dynamicVector[0] = true; //Only to diff from 0

    int i, j, newIndex;

    //For all objects
    for (i = 0; i < valueAweight.size(); ++i) {
        //For the whole container (backwards to not add same twice)
        for (j = c - 1; j > -1; --j) {
            //Need to already exists
            if (dynamicVector[j]) {
                newIndex = j + valueAweight[i];
                //If better
                if (newIndex < 2001)
                    dynamicVector[newIndex] = true;
            }
        }
    }

    int val{ 0 };

    for (i = c; i > 0; --i) {
        if (dynamicVector[i] && abs(1000 - i) < abs(1000 - val)) {
            val = i;
        }
    }

    return val;
}

int main() {
    //ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    double c;

    int n, t;

    fastScan(n);

    vector<int> v(n);
    while (n) {
        //Input
        fastScan(t);
        v[--n] = t;
    }

    printf("%d\n", knapsack(2000, v));

    return 0;

}
