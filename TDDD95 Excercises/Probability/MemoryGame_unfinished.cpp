//https://liu.kattis.com/sessions/ghkq7h/problems/memory2
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

long double rec(vector<vector<long double>> &m, int n, int k) {
    if (n < 0 || k < 0)
        return 0;
    if (m[n][k] != -1)
        return m[n][k];

    long double a;

    a = rec(m, n - 2, k - 1) * 2 * k / (n - k + 0.0);
    a += rec(m, n - 2, k) * (k + 1 / (n - k - 1.0));
    a += rec(m, n, k + 2) * (1 - 2 * k / (n - k + 0.0) - (k + 1 / (n - k - 1.0)));
    m[n][k] = a;
    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);

    int n, n1, n2, x1, x2, x3, x4, y1, y2, y3, y4, i, j;


    fastScan(n);
    vector<vector<long double>> m(n * 2, vector<long double>(n * 2, -1));

    m[0][0] = 0;

    cout << rec(m, n * 2, 0) << "\n";

    system("Pause");
    return 0;
}

