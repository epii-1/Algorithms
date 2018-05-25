//https://liu.kattis.com/problems/whacamole
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
#include <bits/stdc++.h>

using namespace std;

//https://www.geeksforgeeks.org/fast-io-for-competitive-programming/
template<typename T>
void fastScan(T &number) {
    register T c;

    number = 0;

    // extract current character from buffer
    c = getchar_unlocked();
    while (!(c > 47 && c < 58))
        c = getchar_unlocked();

    // Keep on extracting characters if they are integers
    // i.e ASCII Value lies from '0'(48) to '9' (57)
    for (; (c > 47 && c < 58); c = getchar_unlocked())
        number = number * 10 + c - 48;
}

int gcd(int a, int b) {
    if (a < b)
        swap(a, b);
    if (b == 0)
        return 1;
    if (a % b == 0)
        return b;
    return gcd(b, a%b);
}

int main() {
    ios::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);

    int n, d, m;
    int t1, t2, t3;
    int i, j, k, l, cn, d1, d2, mm, mt;
    complex<int> c1, c;

    while (true) {
        fastScan(n);
        fastScan(d);
        fastScan(m);

        if (n == 0 && d == 0 && m == 0)
            break;

        n += d * 2;
        vector<vector<vector<int>>> m1(13, vector<vector<int>>(n, vector<int>(n, 0)));
        vector<vector<vector<int>>> m2(13, vector<vector<int>>(n, vector<int>(n, 0)));
        d2 = d;
        d *= d;

        vector<complex<int>> moves{};
        for (i = 0; i*i <= d; ++i)
            for (j = 0; j*j + i * i <= d; ++j)
                if (((i == 0 && j == 1) || (i == 1 && j == 0) || (j >= 1 && i >= 1)) && gcd(i, j) == 1) {
                    moves.push_back({ i, j });
                    if (i > 0)
                        moves.push_back({ -i, j });
                    if (j > 0) {
                        moves.push_back({ i, -j });
                        if (i > 0)
                            moves.push_back({ -i, -j });
                    }
                }


        ++m;
        mt = 0;
        while (--m) {
            fastScan(t1);
            fastScan(t2);
            fastScan(t3);
            m1[--t3][t1 + d2][t2 + d2] = 1;
            if (t3 >= mt)
                mt = t3 + 1;
        }
        mm = 0;
        for (i = 0; i < 12; ++i)
            for (j = 0; j < n; ++j)
                for (k = 0; k < n; ++k) {
                    c1 = { j, k };
                    cn = m2[i][j][k] + m1[i][j][k];
                    m2[i + 1][j][k] = max(m2[i + 1][j][k], cn);
                    if (cn > mm) {
                        mm = cn;
                    }
                    for (l = 0; l < moves.size(); ++l) {
                        cn = m2[i][j][k] + m1[i][j][k];
                        c = c1 + moves[l];
                        d1 = moves[l].real();
                        d2 = moves[l].imag();
                        while (c.imag() > -1 && c.imag() < n && c.real() > -1 && c.real() < n && d1*d1 + d2*d2 <= d) {
                            cn += m1[i][c.real()][c.imag()];
                            m2[i + 1][c.real()][c.imag()] = max(m2[i + 1][c.real()][c.imag()], cn);
                            c += moves[l];
                            d1 += moves[l].real();
                            d2 += moves[l].imag();
                        }
                        if (cn > mm) {
                            mm = cn;
                        }
                    }
                }

        printf("%d\n", mm);

    }

    return 0;
}