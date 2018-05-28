//https://liu.kattis.com/problems/generalchineseremainder
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
        c = getchar_unlocked();

    if (c == '-') {
        negative = true;
        c = getchar_unlocked();
    }

    // Keep on extracting characters if they are integers
    // i.e ASCII Value lies from '0'(48) to '9' (57)
    for (; (c > 47 && c < 58); c = getchar_unlocked())
        number = number * 10 + c - 48;

    if (negative)
        number = -number;
}

pair<long long, long long> extended_gcd(long long a, long long b){
    long long s{ 0 }, old_s{ 1 }, t{ 1 }, old_t{ 0 }, r{ b }, old_r{ a }, tt{ 0 }, q;
    while (r != 0) {
        q = old_r / r;
        tt = r;
        r = old_r - q * r;
        old_r = tt;
        tt = s;
        s = old_s - q * s;
        old_s = tt;
        tt = t;
        t = old_t - q * t;
        old_t = tt;
    }
    
    return { old_s, old_t };
}

long long gcd(long long a, long long b) {
    long long b1;
    if (a < b){
        b1 = b;
        b = a;
        a = b1;
    }
    while (b > 0) {
        b1 = a%b;
        a = b;
        b = b1;
    }
    return a;
}

pair<long long, long long> chinese_reminder(long long a, long long b, long long n, long long m) {
    long long g{ gcd(n, m) };

    if (a % g != b % g)
        return { -1, -1 };

    n /= g;
    m /= g;

    pair<long long, long long> c{ extended_gcd(n, m) };
    long long k{ n*m*g }, x;
    x = ((b*c.first*n) % k + k) % k;
    x += ((a*c.second*m) % k + k) % k;
    x = (x % k + k) % k;
    return { x, k };
}


int main() {
    ios::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);

    long long t;
    fastScan(t);

    ++t;
    long long a, b, n, m;
    pair<long long, long long> ans;

    while (--t) {
        fastScan(a);
        fastScan(n);
        fastScan(b);
        fastScan(m);

        ans = chinese_reminder(a, b, n, m);

        if (ans.first == -1 && ans.second == -1)
            printf("no solution\n");
        else
            printf("%lld %lld\n", ans.first, ans.second);
    }
    return 0;
}
    
