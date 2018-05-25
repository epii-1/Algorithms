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
//#include <bits/stdc++.h>

using namespace std;

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

    if (c == '.') {
        long double pot{ 0.1 };
        c = getchar();
        for (; (c>47 && c<58); c = getchar(), pot *= 0.1)
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

void merge(vector<Point>& a, vector<Point>& aux, long long lo, long long mid, long long hi) {
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

pair<long double, pair<Point, Point>> leastDist(vector<Point>& pointsByX, vector<Point>& pointsByY, vector<Point>& aux, long long lo, long long hi) {
    if (hi <= lo)
        return { numeric_limits<double>::infinity(),{} };

    long long mid{ lo + (hi - lo) / 2 };
    pair<long double, pair<Point, Point>> delta{ leastDist(pointsByX, pointsByY, aux, lo, mid) };
    pair<long double, pair<Point, Point>> dist{ leastDist(pointsByX, pointsByY, aux, mid + 1, hi) };
    if (dist.first < delta.first)
        delta = dist;

    merge(pointsByY, aux, lo, mid, hi);

    long long M{ 0 }, i, j;
    long double dx;
    for (i = lo; i <= hi; ++i) {
        dx = pointsByY[i].x - pointsByX[mid].x;
        if (dx*dx < delta.first)
            aux[M++] = pointsByY[i];
    }
    long double distance, t;
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

/*long double bruteForce(vector<Point> & P, Point &p1, Point &p2) {
long long n(P.size());
long long i, j;
long double min = DBL_MAX, t;
for (i = 0; i < n; ++i)
for (j = i + 1; j < n; ++j) {
t = P[i].sDist(P[j]);
if (t < min) {
min = t;
p1 = P[i];
p2 = P[j];
}
}
return min;
}*/

int main() {
    ios::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);

    std::srand(std::time(nullptr)); // use current time as seed for random generator
                                    // Seed with a real random value, if available
    std::random_device r;

    // Choose a random mean between 1 and 6
    std::minstd_rand re(r());
    std::uniform_int_distribution<int> uid(0, 20000000);
    long double t;

    int n, i;
    vector<Point> points, pointsByY, aux, P;
    Point p1, p2;

    //n = 2;
    while (true) {
        //n = 100000;
        //cout << n << "\n";
        fastScan(n);

        if (n <= 0)
            break;
        points.resize(n);
        pointsByY.resize(n);
        aux.resize(n);
        //P.resize(n);

        for (i = 0; i < n; ++i) {
            fastScan(points[i].x);
            fastScan(points[i].y);
            //cout << uid(re) << "\n";
            //points[i].x = (-10000000 + uid(re)) / 100.0;
            //points[i].y = (-10000000 + uid(re)) / 100.0;
            //cout << points[i].x << " " << points[i].y << "\n";
        }

        sort(points.begin(), points.end());
        //P = points;
        pointsByY = points;

        pair<long double, pair<Point, Point>> bestPair{ leastDist(points, pointsByY, aux, 0, n - 1) };
        /*if (bestPair.first != bruteForce(P, p1, p2)) {
        cout << bestPair.second.first.x << " " << bestPair.second.first.y << " " << bestPair.second.second.x << " " << bestPair.second.second.y << "\n";
        cout << p1.x << " " << p1.y << " " << p2.x << " " << p2.y << "\n";

        cout << bruteForce(points, p1, p2) << " " << bestPair.first << "\n";
        cout << n << "\n";
        for (Point p : points)
        cout << p.x << " " << p.y << "\n";
        system("Pause");
        }*/
        //printf("%.2Le %.2Le %.2Le %.2Le\n", bestPair.second.first.x, bestPair.second.first.y, bestPair.second.second.x, bestPair.second.second.y);
        std::cout << std::setprecision(2);
        std::cout << std::fixed;
        cout << bestPair.second.first.x << " " << bestPair.second.first.y << " " << bestPair.second.second.x << " " << bestPair.second.second.y << "\n";
    }

    system("Pause");
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