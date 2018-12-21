//https://liu.kattis.com/problems/rationalarithmetic
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

using namespace std;

//https://www.geeksforgeeks.org/fast-io-for-competitive-programming/
template<typename T>
void fastScan(T &number) {
    register T c;

    bool negative{ false };
    number = 0;

    // extract current character from buffer
    c = getchar();
    while (!(c > 47 && c < 58) && c != '-')
        c = getchar();

    if (c == '-') {
        negative = true;
        c = getchar();
    }

    // Keep on extracting characters if they are integers
    // i.e ASCII Value lies from '0'(48) to '9' (57)
    for (; (c > 47 && c < 58); c = getchar())
        number = number * 10 + c - 48;

    if (negative)
        number = -number;
}

template<typename T>
T gcd(T u, T v) {
    T r;
    while (v != 0) {
        r = u % v;
        u = v;
        v = r;
    }
    return u;
}

int main() {
    ios::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);

    long long T, x1, x2, y1, y2, g;
    char op;
    fastScan(T);
    ++T;

    while (--T) {
        fastScan(x1);
        fastScan(y1);
        op = getchar();
        fastScan(x2);
        fastScan(y2);

        switch (op) {
        case '-':
            x2 = -x2;
        case '+':
            x1 = x1*y2 + x2*y1;
            y1 *= y2;
            break;
        case '*':
            x1 *= x2;
            y1 *= y2;
            break;
        case '/':
            x1 *= y2;
            y1 *= x2;
            break;
        }

        if (y1 < 0) {
            x1 *= -1;
            y1 *= -1;
        }

        g = gcd(abs(x1), y1);

        printf("%lld / %lld\n", x1 / g, y1 / g);

    }

    return 0;
}
