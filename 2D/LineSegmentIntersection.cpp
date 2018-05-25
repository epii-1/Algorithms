//https://liu.kattis.com/problems/segmentintersection
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


class Point {
public:
    long double x, y;

    Point() {}
    Point(long double x, long double y) : x(x), y(y) {}

    bool operator==(const Point& o) const {
        return abs(x - o.x) <0.000000001 && abs(y - o.y) <  0.000000001;
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
        //cout << f.first << "\n";
        if (isnan(f.first)) {
            return p == p1;
        }
        if (isinf(f.first)) {
            return abs(p.x - p1.x) < 0.000000001 &&
                ((p.y - p1.y < 0.000000001 && p.y - p2.y > -0.000000001)
                    || (p.y - p2.y < 0.000000001 && p.y - p1.y > -0.000000001));
        }
        //cout << (abs(f.first*p.x + f.second - p.y) < 0.000000001) << " " <<
        //    (p.x <= p1.x && p.x >= p2.x) << " " <<
        //    (p.x >= p1.x && p.x <= p2.x) << "\n";
        return abs(f.first*p.x + f.second - p.y) < 0.000000001 &&
            ((p.x - p1.x < 0.000000001 && p.x - p2.x > -0.000000001) ||
            (p.x - p1.x > -0.000000001 && p.x - p2.x < 0.000000001));
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

        //cout << f.first << " " << f.second << "\n";
        //cout << of.first << " " << of.second << "\n";

        if (abs(f.first - of.first) < 0.000000001 || (isinf(f.first) && isinf(of.first))) {
            //cout << "same\n";
            if (abs(f.second - of.second) > 0.000000001)
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
            if (o.on(p1)) {
                //cout << "p1 on\n";
                if (o.on(p2))
                    return { p1, p2 };
                return { p1 };
            }
            if (o.on(p2)) {
                //cout << "p2 on\n";
                return { p2 };
            }
            return {};
        }

        Point p(intersect(f, of));
        //cout << p.x << " " << p.y << "\n";
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

int main() {
    ios::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);

    int n, x1, x2, x3, x4, y1, y2, y3, y4;

    Line l1, l2;

    fastScan(n);
    ++n;
    //ofstream f;
    //f.open("outfile.txt");
    while (--n) {
        fastScan(x1);
        fastScan(y1);
        fastScan(x2);
        fastScan(y2);
        fastScan(x3);
        fastScan(y3);
        fastScan(x4);
        fastScan(y4);

        l1.p1.x = x1;
        l1.p1.y = y1;
        l1.p2.x = x2;
        l1.p2.y = y2;
        l2.p1.x = x3;
        l2.p1.y = y3;
        l2.p2.x = x4;
        l2.p2.y = y4;

        vector<Point> intersection{ l1.fullIntersect(l2) };

        //f << std::setprecision(2);
        //f << std::fixed;
        std::cout << std::setprecision(2);
        std::cout << std::fixed;
        if (intersection.size() == 2) {
            sort(intersection.begin(), intersection.end());
            //f << intersection[0].x << " " << intersection[0].y << " " <<
            //    intersection[1].x << " " << intersection[1].y << "\n";
            cout << intersection[0].x << " " << intersection[0].y << " " <<
                intersection[1].x << " " << intersection[1].y << "\n";
        }
        else if (intersection.size()) {
            //f << intersection[0].x << " " << intersection[0].y << "\n";
            cout << intersection[0].x << " " << intersection[0].y << "\n";
        }
        else {
            //f << "none\n";
            cout << "none\n";
        }

    }
    //f.close();
    system("Pause");
    return 0;
}


/*

1
1758 829 1758 348 1758 1895 1758 830


*/