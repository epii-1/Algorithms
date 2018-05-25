//https://liu.kattis.com/problems/rafting
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


class Point {
public:
    long double x, y;

    Point() {}
    Point(long double x, long double y) : x(x), y(y) {}

    bool operator==(const Point& o) const {
        return x == o.x && y == o.y;
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
        K t{ 1 / o };
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
        return sqrt(tx*tx + ty*ty);
    }

    long double crossProduct(const Point& o) const {
        return x*o.y - y*o.x;
    }

    long double scalarProduct(const Point& o) const {
        return x*o.x + y*o.y;
    }

    long double angl(const Point& o) const {
        return atan2(x - o.x, y - o.y);
    }
};

bool operator<(const Point& lhs, const Point& rhs) {
    return lhs.x < rhs.x || (lhs.x == rhs.x && lhs.y < rhs.y);
}

class Line {
public:
    Point p1, p2;

    long double length() const {
        return p1.dist(p2);
    }

    pair<long double, long double> getFunc() const {
        long double k{ (p2.y - p1.y) / (p2.x - p1.x) };
        if (isinf(k))
            return { k, p1.x };
        long double m{ p1.y - k*p1.x };
        return { k, m };
    }

    long double ortK() const {
        return -1 / getFunc().first;
    }

    pair<long double, long double> ortFunc(const Point& p) const {
        long double k{ ortK() };
        if (isinf(k))
            return { k, p.x };
        long double m{ p.y - k*p.x };
        return { k,m };
    }

    bool on(const Point & p) const {
        pair<long double, long double> f{ getFunc() };
        if (isnan(f.first)) {
            return p == p1;
        }
        if (isinf(f.first)) {
            return p.x == p1.x &&
                ((p.y <= p1.y && p.y >= p2.y)
                    || (p.y <= p2.y && p.y >= p1.y));
        }
        return f.first*p.x + f.second == p.y &&
            ((p.x <= p1.x && p.x >= p2.x) ||
            (p.x >= p1.x && p.x <= p2.x));
    }
    Point intersect(const pair<long double, long double> f, const pair<long double, long double> of) const {
        if (isinf(f.first)) {
            //cout << "f is inf\n";
            return Point(f.second, f.second*of.first + of.second);
        }
        if (isinf(of.first)) {
            //cout << "of is inf\n";
            //cout << of.second << " " << of.second * f.first << "\n";
            return Point(of.second, of.second*f.first + f.second);
        }
        long double x{ (f.second - of.second) / (of.first - f.first) };
        return Point(x, f.first*x + f.second);
    }

    Point intersect(const pair<long double, long double> of) const {
        return intersect(getFunc(), of);
    }

    Point intersect(const Line& o) const {
        return intersect(o.getFunc());
    }

    vector<Point> fullIntersect(const Line& o) const {
        pair<long double, long double> f{ getFunc() };
        pair<long double, long double> of{ o.getFunc() };

        if (isnan(f.first)) {
            if (o.on(p1))
                return { p1 };
            return {};
        }
        if (isnan(of.first)) {
            if (on(o.p1))
                return { o.p1 };
            return {};
        }

        //cout << f.first << " " << of.first << "\n";

        if (f.first == of.first || (isinf(f.first) && isinf(of.first))) {
            //cout << "same\n";
            if (f.second != of.second && f.first != 0)
                return {};

            if (on(o.p1)) {
                //cout << "o.p1 on\n";
                if (o.p1 != p1 && o.on(p1)) {
                    return { o.p1, p1 };
                }
                if (o.p1 != p2 && o.on(p2)) {
                    return { o.p1, p2 };
                }
                if (on(o.p2)) {
                    return { o.p1, o.p2 };
                }
                return { o.p1 };
            }
            if (on(o.p2)) {
                //cout << "o.p2 on\n";
                if (o.p2 != p1 && o.on(p1)) {
                    return { o.p2, p1 };
                }
                if (o.p2 != p2 && o.on(p2)) {
                    return { o.p2, p2 };
                }
                return { o.p2 };
            }
            return { p1, p2 };
        }

        Point p(intersect(f, of));
        if (!on(p) || !o.on(p))
            return {};

        return { p };

    }

    long double dist(const Point & p) const {
        long double dist;
        Point inter(intersect(ortFunc(p)));
        //printf("%Le %Le %Le %Le\n", p1.x, p1.y, p2.x, p2.y);
        //printf("%Le %Le\n", p.x, p.y);
        if (on(inter)) {
            //printf("on\n");
            //printf("%Le %Le %Le %Le\n", p.x, p.y, inter.x, inter.y);
            dist = p.dist(inter);
        }
        else
            dist = min(p.dist(p1), p.dist(p2));
        //printf("%Le\n\n", dist);
        return dist;
    }

};

int main() {
    ios::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);

    int n, n1, n2, x1, x2, x3, x4, y1, y2, y3, y4, i, j;


    long double minD;
    Line l1, l2;

    fastScan(n);
    ++n;
    vector<Line> inner;
    vector<Line> outer;
    while (--n) {
        minD = 99999999;

        fastScan(n1);
        inner.resize(n1);
        fastScan(x1);
        fastScan(y1);
        inner[0].p1.x = x1;
        inner[0].p1.y = y1;
        for (i = 1; i < n1; ++i) {
            fastScan(x1);
            fastScan(y1);
            inner[i].p1.x = x1;
            inner[i].p1.y = y1;
            inner[i - 1].p2.x = x1;
            inner[i - 1].p2.y = y1;
        }
        inner[n1 - 1].p2.x = inner[0].p1.x;
        inner[n1 - 1].p2.y = inner[0].p1.y;


        fastScan(n2);
        outer.resize(n2);
        fastScan(x1);
        fastScan(y1);
        outer[0].p1.x = x1;
        outer[0].p1.y = y1;
        for (i = 1; i < n2; ++i) {
            fastScan(x1);
            fastScan(y1);
            outer[i].p1.x = x1;
            outer[i].p1.y = y1;
            outer[i - 1].p2.x = x1;
            outer[i - 1].p2.y = y1;
        }
        outer[n2 - 1].p2.x = outer[0].p1.x;
        outer[n2 - 1].p2.y = outer[0].p1.y;

        for (i = 0; i < n1; ++i) {
            for (j = 0; j < n2; ++j) {
                minD = min(minD, outer[j].dist(inner[i].p1));
                minD = min(minD, inner[i].dist(outer[j].p1));
            }
        }

        printf("%Le\n", minD / 2);
    }

    system("Pause");
    return 0;
}


/*

5
-10 0 10 0 0 -10 0 10
-10 0 10 0 -5 0 5 0
1 1 1 1 1 1 2 1
1 1 1 1 2 1 2 1
1871 5789 216 -517 189 -518 3851 1895

10
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 1
0 0 0 0 0 1 0 0
0 0 0 0 1 0 0 0
0 0 0 0 0 0 1 0
0 0 0 0 0 1 0 1
0 0 0 0 1 0 0 1
0 0 0 0 -1 0 1 0
0 0 0 0 0 -1 0 1
0 0 0 0 0 1 0 1

0 0 0 1 0 0 0 1
0 0 1 0 0 0 0 1

-1 0 1 0 -1 -1 1 1


*/