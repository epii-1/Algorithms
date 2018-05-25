//https://liu.kattis.com/problems/polygonarea
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
        return -1.0 / getFunc().first;
    }

    pair<long double, long double> ortFunc(const Point& p) const {
        long double k{ ortK() };
        if (isinf(k))
            return { k, p.y };
        long double m{ p.y - k*p.x };
        return { k,m };
    }

    bool on(const Point & p) const {
        pair<long double, long double> f{ getFunc() };
        if (isnan(f.first)) {
            return p == p1;
        }
        if (isinf(abs(f.first))) {
            return p.x == p1.x &&
                ((p.y <= p1.y && p.y >= p2.y)
                    || (p.y <= p2.y && p.y >= p1.y));
        }
        return f.first*p.x + f.second == p.y &&
            ((p.x <= p1.x && p.x >= p2.x) ||
            (p.x >= p1.x && p.x <= p2.x));
    }
    Point intersect(const pair<long double, long double> f, const pair<long double, long double> of) const {
        if (isinf(abs(f.first))) {
            //cout << "f is inf\n";
            return Point(f.second, f.second*of.first + of.second);
        }
        if (isinf(abs(of.first))) {
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
            if (f.second != of.second)
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
        if (on(p) && o.on(p))
            return { p };

        return {};

    }

    long double dist(const Point & p) const {
        long double dist;
        Point inter(intersect(ortFunc(p)));
        if (on(inter))
            dist = p.dist(inter);
        else
            dist = min(p.dist(p1), p.dist(p2));
        return dist;
    }

};

enum InOutOn {
    IN, OUT, ON
};

class Poly {
public:
    vector<Line> lines;

    long double area() const {
        long double area{ 0.0 };

        // Calculate value of shoelace formula
        int j(lines.size() - 1);
        for (int i{ 0 }; i < lines.size(); ++i)
        {
            area += (lines[j].p1.x + lines[i].p1.x) * (lines[j].p1.y - lines[i].p1.y);
            j = i;  // j is previous vertex to i
        }

        // Return absolute value
        return area / 2.0;
    }

    InOutOn in(const Point& p) const {
        int i{ 0 };
        for (; i < lines.size(); ++i) {
            if (lines[i].on(p))
                return ON;
        }
        pair<long double, long double> f{ 0, p.y };
        int intersects{ 0 };
        vector<Point> pv;
        for (i = 0; i < lines.size(); ++i) {
            if (lines[i].getFunc().first != 0) {
                Point inter{ lines[i].intersect(f) };
                //printf("%Le %Le %Le %Le\n", lines[i].p1, lines[i].p2);
                //printf("%Le %Le\n", inter);
                if (inter.x > p.x && lines[i].on(inter)) {
                    pv.push_back(inter);
                    if (inter != lines[i].p1 && inter != lines[i].p2)
                        ++intersects;
                    ++intersects;
                }
            }
        }

        //for (Point pp : pv) 
        //    printf("%Le %Le\n", pp);

        return (intersects / 2) % 2 ? IN : OUT;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);

    int n, m, x1, x2, x3, x4, y1, y2, y3, y4, i;
    long double a;

    Poly p;
    Point po;

    while (true) {
        fastScan(n);
        if (n == 0)
            break;
        p.lines.resize(n);
        fastScan(x1);
        fastScan(y1);
        p.lines[0].p1.x = x1;
        p.lines[0].p1.y = y1;
        for (i = 1; i < n; ++i) {
            fastScan(x1);
            fastScan(y1);
            p.lines[i].p1.x = x1;
            p.lines[i].p1.y = y1;
            p.lines[i - 1].p2.x = x1;
            p.lines[i - 1].p2.y = y1;
        }
        p.lines.back().p2.x = p.lines[0].p1.x;
        p.lines.back().p2.y = p.lines[0].p1.y;

        a = p.area();

        if (a > 0)
            cout << "CW ";
        else
            cout << "CCW ";
        std::cout << std::setprecision(1);
        std::cout << std::fixed;
        cout << abs(a) << "\n";
    }

    system("Pause");
    return 0;
}