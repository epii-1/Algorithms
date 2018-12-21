//https://liu.kattis.com/problems/2naire
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
#include <fstream>
//#include <bits/stdc++.h>

using namespace std;

//https://www.geeksforgeeks.org/fast-io-for-competitive-programming/
template<typename T>
void fastScan(T &number) {
    register T c;

    number = 0;

    // extract current character from buffer
    c = getchar();
    while (!(c > 47 && c < 58))
        c = getchar();
    // Keep on extracting characters if they are integers
    // i.e ASCII Value lies from '0'(48) to '9' (57)
    for (; (c>47 && c<58); c = getchar())
        number = number * 10 + c - 48;

    if (c == '.') {
        long double pot{ 0.1 };
        c = getchar();
        for (; (c>47 && c<58); c = getchar(), pot *= 0.1)
            number += (c - 48)*pot;
    }
}

double ce(int n, double t) {
    double f = pow(2, n);
    double eq, prize;
    for (int i = n - 1; i >= 0; --i) {
        prize = pow(2, i);
        eq = prize / f;
        if (eq <= t)
            f = (t + 1) / 2 * f;
        else
            f = (eq - t) / (1 - t) * prize +
            (1 - eq) / (1 - t) * (eq + 1) / 2 * f;
    }
    return f;
}

int main() {
    ios::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);

    int n;
    double t;

    while (true) {
        fastScan(n);
        fastScan(t);
        if (!n && t == 0)
            break;
        printf("%.3lf\n", ce(n, t));
    }

    system("Pause");
    return 0;
}