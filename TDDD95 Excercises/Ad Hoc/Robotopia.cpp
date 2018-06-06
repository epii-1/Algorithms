//https://liu.kattis.com/problems/robotopia
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
    for (; (c>47 && c<58); c = gc())
        number = number * 10 + c - 48;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, l1, a1, l2, a2, l, a, l3, a3;
    int s, s1, s2;
    int i, j;
    fastScan(N);
    ++N;
    while (--N) {
        fastScan(l1);
        fastScan(a1);
        fastScan(l2);
        fastScan(a2);
        fastScan(l);
        fastScan(a);
        s = 0;
        for (i = 1, l3 = l1, a3 = a1; l3 <= l && a3 <= a; ++i, l3 += l1, a3 += a1) {
            j = (l - l3) / l2;
            if (l3 + j*l2 == l && a3 + j*a2 == a && j > 0) {
                ++s;
                s1 = i; s2 = j;
            }
        }
        if (s == 1)
            printf("%d %d\n", s1, s2);
        else
            printf("?\n");
    }

    return 0;
}