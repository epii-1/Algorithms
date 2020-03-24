//https://liu.kattis.com/problems/closestpair1
//https://liu.kattis.com/problems/closestpair2
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
#include <ctime>
#include <cstdlib>

using namespace std;

#define _UNLOCKED 1
#if _UNLOCKED
#define gc() getchar_unlocked()
#else
#define gc() getchar()
#endif

template<typename T>
void fastScan(T &number) {
    //variable to indicate sign of input number
    bool negative{ false };
    register T c;

    number = 0;

    // extract current character from buffer
    c = gc();
    while (!(c == '-' || (c > 47 && c < 58)))
        c = gc();

    if (c == '-') {
        // number is negative
        negative = true;

        // extract the next character from the buffer
        c = gc();
    }

    // Keep on extracting characters if they are integers
    // i.e ASCII Value lies from '0'(48) to '9' (57)
    for (; (c>47 && c<58); c = gc())
        number = number * 10 + c - 48;

    if (c == '.') {
        c = gc();
        for (T pot(0.1); (c>47 && c<58); c = gc(), pot *= 0.1)
            number += (c - 48)*pot;
    }

    // if scanned input has a negative sign, negate the
    // value of the input number
    if (negative)
        number *= -1;
}

class Point;

bool operator<(const Point& lhs, const Point& rhs);

class Point {
public:
    long double x, y;

    Point() {}
    Point(long double x, long double y) : x(x), y(y) {}

    bool operator==(const Point& o) const {
        return x == o.x && y == o.y;
    }

    bool operator<=(const Point& o) const {
        return operator==(o) || *this < o;
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

    long double sDist(const Point& o) const {
        long double tx(x - o.x);
        long double ty(y - o.y);
        return tx*tx + ty*ty;
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

bool compY(const Point& lhs, const Point& rhs) {
    return lhs.y < rhs.y || (lhs.y == rhs.y && lhs.x < rhs.x);
}

void merge(vector<Point>& a, vector<Point>& aux, const long long lo, const long long mid, const long long hi) {
    //Move points to only have the current x part in the current y-list
    //And sorted according to y
    long long i, j, k;
    for (k = lo; k <= hi; ++k)
        aux[k] = a[k];

    i = lo; j = mid + 1; k = lo;
    while (i <= mid && j <= hi)
        a[k++] = compY(aux[i], aux[j]) ? aux[i++] : aux[j++];

    // Copy the rest of the left side of the array into the target array
    while (i <= mid)
        a[k++] = aux[i++];
}

//Find a pair of paints with least distance from pointsByX and pointsByY (Should be the same points, but different ordering)
pair<long double, pair<Point, Point>> leastDist(const vector<Point>& pointsByX, vector<Point>& pointsByY,
    vector<Point>& aux, const long long lo, const long long hi) {

    //No pair possible
    if (hi <= lo)
        return { numeric_limits<long double>::infinity(),{} };

    long long mid{ lo + (hi - lo) / 2 };
    //Divide and conquer
    pair<long double, pair<Point, Point>> delta{ leastDist(pointsByX, pointsByY, aux, lo, mid) };
    pair<long double, pair<Point, Point>> dist{ leastDist(pointsByX, pointsByY, aux, mid + 1, hi) };
    if (dist.first < delta.first)
        delta = dist;

    merge(pointsByY, aux, lo, mid, hi);

    long long M{ 0 }, i, j;
    long double dx;
    //Find points closer than delta from midline
    for (i = lo; i <= hi; ++i) {
        dx = pointsByY[i].x - pointsByX[mid].x;
        if (dx*dx < delta.first)
            aux[M++] = pointsByY[i];
    }
    long double distance, t;
    //try to find pairs
    for (i = 0; i + 1 < M; ++i) {
        for (j = i + 1, dx = aux[i + 1].y - aux[i].y; j < M; ++j) {
            dx = aux[j].y - aux[i].y;
            if (dx*dx >= delta.first)
                break;
            distance = aux[i].sDist(aux[j]);
            if (distance < delta.first) {
                delta.first = distance;
                delta.second.first.x = aux[i].x;
                delta.second.first.y = aux[i].y;
                delta.second.second.x = aux[j].x;
                delta.second.second.y = aux[j].y;
            }
        }
    }
    return delta;
}

int main() {
    ios::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);


    int n, i;
    vector<Point> points, pointsByY, aux, P;
    Point p1, p2;

    while (true) {
        fastScan(n);

        if (n <= 0)
            break;
        points.resize(n);
        pointsByY.resize(n);
        aux.resize(n);

        for (i = 0; i < n; ++i) {
            fastScan(points[i].x);
            fastScan(points[i].y);
        }

        sort(points.begin(), points.end());
        pointsByY = points;

        pair<long double, pair<Point, Point>> bestPair{ leastDist(points, pointsByY, aux, 0, n - 1) };

        printf("%.2f %.2f %.2f %.2f\n", bestPair.second.first.x, bestPair.second.first.y, bestPair.second.second.x, bestPair.second.second.y);
    }
    return 0;
}

/*

4
-78291.4 -22840.8
-56159.9 64500.4
-31456.2 21406.9
55789.5 -53311.5

8
-78357.5 -92988.5
-62215.8 97949.3
-56670.1 48533.1
-49646 23601.5
-31717.7 13917.6
-25599.6 70542.7
-3359.27 -23414.7
53862.9 95618.5


*/