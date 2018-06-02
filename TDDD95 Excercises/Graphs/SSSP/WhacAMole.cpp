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
#include <cstring>

using namespace std;

#define _UNLOCKED 1
#if _UNLOCKED
#define gc() getchar_unlocked()
#else
#define gc() getchar()
#endif

//https://www.geeksforgeeks.org/fast-io-for-competitive-programming/
template<typename T>
void fastScan(T &number) {
    register T c;

    number = 0;

    // extract current character from buffer
    c = gc();
    while (!(c > 47 && c < 58))
        c = gc();

    // Keep on extracting characters if they are integers
    // i.e ASCII Value lies from '0'(48) to '9' (57)
    for (; (c > 47 && c < 58); c = gc())
        number = number * 10 + c - 48;
}

int gcd(int a, int b) {
    if (a < b)
        swap(a, b);
    int c;
    while (b > 0) {
        c = b;
        b = a%b;
        a = c;
    }
    return a;
}

template<typename T>
void fastFill(T* v, const T& x, size_t n) {
    if (n == 0)
        return;
    size_t s(1);
    *v = x;
    while (s + s <= n) {
        memcpy((v + s), v, s * sizeof(x));
        s += s;
    }
    memcpy((v + s), v, (n - s) * sizeof(x));
}

int main() {
    ios::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);

    int n, d, m, oldD;
    int t1, t2, t3;
    int i, j, k, l, cn, d1, d2, mm, mt;
    complex<char> c1, c;

    vector<vector<vector<int>>> m1(11, vector<vector<int>>(30, vector<int>(30)));
    vector<vector<vector<int>>> m2(11, vector<vector<int>>(30, vector<int>(30)));
    vector<pair<char, complex<char>>> moves;


    for (i = 0; i*i <= 25; ++i)
        for (j = 0; j*j + i * i <= 25; ++j)
            if (((i == 0 && j == 1) || (i == 1 && j == 0) || (j >= 1 && i >= 1)) && gcd(i, j) == 1) {
                moves.push_back({ i*i + j*j, complex<char>{ i, j } });
                if (i > 0)
                    moves.push_back({ i*i + j*j, complex<char>{ -i, j } });
                if (j > 0) {
                    moves.push_back({ i*i + j*j, complex<char>{ i, -j } });
                    if (i > 0)
                        moves.push_back({ i*i + j*j, complex<char>{ -i, -j } });
                }
            }

    sort(moves.begin(), moves.end(), [](const pair<char, complex<char>>& l, const pair<char, complex<char>>& r)->bool { return l.first < r.first; });


    while (true) {
        fastScan(n);
        fastScan(d);
        fastScan(m);

        if (n == 0 && d == 0 && m == 0)
            break;

        n += d * 2;

        for (i = 0; i < 11; ++i) {
            for (j = 0; j < n; ++j) {
                fastFill(&m1[i][j][0], 0, n);
                fastFill(&m2[i][j][0], 0, n);
            }
        }

        d2 = d;
        d *= d;


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
        for (i = 0; i < 10; ++i)
            for (j = 0; j < n; ++j)
                for (k = 0; k < n; ++k) {
                    c1 = { j, k };
                    cn = m2[i][j][k] + m1[i][j][k];
                    m2[i + 1][j][k] = max(m2[i + 1][j][k], cn);
                    if (cn > mm) {
                        mm = cn;
                    }
                    for (l = 0; l < moves.size() && moves[l].first <= d; ++l) {
                        cn = m2[i][j][k] + m1[i][j][k];
                        c = c1 + moves[l].second;
                        d1 = moves[l].second.real();
                        d2 = moves[l].second.imag();
                        while (c.imag() > -1 && c.imag() < n && c.real() > -1 && c.real() < n && d1*d1 + d2*d2 <= d) {
                            cn += m1[i][c.real()][c.imag()];
                            m2[i + 1][c.real()][c.imag()] = max(m2[i + 1][c.real()][c.imag()], cn);
                            c += moves[l].second;
                            d1 += moves[l].second.real();
                            d2 += moves[l].second.imag();
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