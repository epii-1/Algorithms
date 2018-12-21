//https://liu.kattis.com/problems/ljutnja
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

using namespace std;

//https://www.geeksforgeeks.org/fast-io-for-competitive-programming/
template<typename T>
void fastScan(T &number)
{
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

}

int main() {

    ios::sync_with_stdio(false);
    cout.precision(17);
    cin.tie(nullptr);
    cout.tie(nullptr);

    unsigned long long m, n, a(0), m0, r, p, diff(0);
    unsigned long long missing(0);

    fastScan(m);
    fastScan(n);
    m0 = 0;
    r = n;
    vector<unsigned long long> w(n);

    for (unsigned long long i = 0; i < n; ++i) {
        unsigned long long t;
        fastScan(t);
        w[i] = t;
        diff += t;
    }
    diff -= m;

    sort(w.begin(), w.end(), std::greater<unsigned long long>());

    vector<unsigned long long> now(w);

    p = diff / r;
    while (p > 0 && r > 0) {
        p = diff / r;
        unsigned long long r0 = r;
        for (unsigned long long i = 0; i < r0; ++i) {
            if (now[i] > p) {
                now[i] -= p;
                diff -= p;
            }
            else {
                diff -= now[i];
                --r;
                now[i] = 0;
            }
        }
    }


    for (unsigned long long i = 0; i < diff; ++i) {
        --now[i];
    }


    for (unsigned long long i = 0; i < n; ++i) {
        unsigned long long t = w[i] - now[i];
        a += t*t;
    }

    cout << a << endl;


    return 0;

}
