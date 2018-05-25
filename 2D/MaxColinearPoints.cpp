//https://liu.kattis.com/problems/maxcolinear
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


long long gcd(long long a, long long b) {
    if (a < b)
        swap(a, b);
    long long c;
    while (b != 0) {
        c = b;
        b = a % b;
        a = c;
    }
    return a;
}

class Point {
public:
    long double x, y;

    Point() {}
    Point(long double x, long double y) : x(x), y(y) {}

    bool operator==(const Point& o) const {
        return abs(x - o.x) < 0.000000001 && abs(y - o.y) <  0.000000001;
    }

    bool operator!=(const Point& o) const {
        return !operator==(o);
    }

    template<typename K>
    Point& operator*(const K& o) {
        x *= o;
        y *= o;
        return *this;
    }

    template<typename K>
    Point& operator/(const K& o) {
        K t{ 1.0 / o };
        return operator*(t);
    }

    Point& operator+(const Point& o) {
        x += o.x;
        y += o.y;
        return *this;
    }

    Point& operator-(const Point& o) {
        x -= o.x;
        y -= o.y;
        return *this;
    }

    long double dist(const Point& o) const {
        long double tx(x - o.x);
        long double ty(y - o.y);
        return sqrt(tx * tx + ty * ty);
    }

    long double crossProduct(const Point& o) const {
        return x * o.y - y * o.x;
    }

    long double scalarProduct(const Point& o) const {
        return x * o.x + y * o.y;
    }

    long double angl(const Point& o) const {
        return atan2(x - o.x, y - o.y);
    }

    pair<long long, long long> getSlope(const Point& o) const {
        long long dy(y - o.y);
        long long dx(x - o.x);
        if ((dy < 0 && dx < 0) || (dy > 0 && dx < 0)) {
            dy = -dy;
            dx = -dx;
        }
        long long g{ gcd(abs(dy),abs(dx)) };
        //cout << dy << " " << dx << " " << g << "\n";
        return { dy / g, dx / g };
    }
};

long long number_of_colinear(const vector<Point> & v) {
    map<pair<long long, long long>, long long> m;
    long long maxN{ 0 };
    unsigned long i, j;
    long long c;
    if (v.size() == 1)
        return 1;
    for (i = 0; i < v.size(); ++i) {
        for (j = i + 1; j < v.size(); ++j) {
            c = ++m[v[i].getSlope(v[j])];
            if (c > maxN)
                maxN = c;
        }
        m.clear();
    }
    return maxN + 1;
}

int main() {
    ios::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);

    int n, m, x1, x2, x3, x4, y1, y2, y3, y4, i;

    vector<Point> p;

    while (true) {
        fastScan(n);
        if (n == 0)
            break;
        p.resize(n);
        for (i = 0; i < n; ++i) {
            fastScan(x1);
            fastScan(y1);
            p[i].x = x1;
            p[i].y = y1;
        }

        printf("%lld\n", number_of_colinear(p));
    }

    system("Pause");
    return 0;
}