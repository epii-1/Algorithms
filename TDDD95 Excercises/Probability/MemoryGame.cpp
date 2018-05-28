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
    for (; (c>47 && c<58); c = getchar_unlocked())
        number = number * 10 + c - 48;
}

float rec(vector<vector<float>> &m, int n, int k) {
    if (n < 0 || k < 0)
        return 0;
    if (k + k >= n) {
        if (k + k == n)
            m[n >> 1][k] = n >> 1;
        return n >> 1;
    }
    if (m[n >> 1][k] != -1)
        return m[n >> 1][k];


    float a{ 1 };

    //cout << n << " " << k << "\n";
    //cout << k/(n-k+0.0) << " " << (n-k-k)/(n-k+0.0) * (1/(n-k-1.0)) << " " <<
    //        (1-(k/(n-k+0.0))-((n-k-k)/(n-k+0.0) * (1/(n-k-1.0)))-((n-k-k)/(n-k+0.0) * k/(n-k-1.0))) << " " <<
    //        (n-k-k)/(n-k+0.0) * k/(n-k-1.0) << "\n";
    float c1(k / (n - k + 0.0));
    float ct((n - k - k) / (n - k + 0.0));
    float c2(ct * (1 / (n - k - 1.0)));
    float c3(ct * k / (n - k - 1.0));
    if (c1 > 0)
        a += rec(m, n - 2, k - 1) * c1;
    if (c2 > 0)
        a += rec(m, n - 2, k) * c2;
    if (c1 - c2 - c3 < 1)
        a += rec(m, n, k + 2) * (1.0L - c1 - c2 - c3);//(n-k-k)/(n-k+0.0) * (n-k-k-1)/(n-k-1.0) * (1-(n-k-k)/(n-k+0.0) * (1/(n-k-1.0)));
    if (c3 > 0)
        a += (rec(m, n - 2, k) + 1) * c3;
    //cout << n << " " << k << " " << a << "\n";
    m[n >> 1][k] = a;
    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);

    int n, n1, n2, x1, x2, x3, x4, y1, y2, y3, y4, i, j;

    fastScan(n);
    vector<vector<float>> m(n + 1);
    for (i = 0; i <= n; ++i)
        m[i].resize(i * 2 + 1, -1);

    m[0][0] = 0;

    printf("%0.7f\n", rec(m, n * 2, 0));

    return 0;
}

