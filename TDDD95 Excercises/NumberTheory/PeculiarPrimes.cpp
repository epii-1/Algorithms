//https://liu.kattis.com/sessions/ghkq7h/problems/primes
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

void createNum(const vector<long long> &p, long long x, long long y, vector<long long> &s, long long c, long long j) {
    if (p.size() == j) {
        if (x <= c && c <= y)
            s.push_back(c);
        return;
    }

    while (c <= y) {
        createNum(p, x, y, s, c, j + 1);
        c *= p[j];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);

    long long n, i, x, y;

    vector<long long> p;
    vector<long long> s;
    string ss;

    while (true) {
        fastScan(n);
        if (n == 0)
            break;
        p.resize(n);
        s.clear();

        for (i = 0; i < n; ++i)
            fastScan(p[i]);

        fastScan(x);
        fastScan(y);

        createNum(p, x, y, s, 1, 0);

        sort(s.begin(), s.end());

        if (s.size()) {
            ss = "";
            for (long long i : s) {
                ss += to_string(i);
                ss += ",";
            }

            cout << ss.substr(0, ss.length() - 1);
        }
        else
            cout << "none";
        cout << "\n";

    }


    system("Pause");
    return 0;
}
