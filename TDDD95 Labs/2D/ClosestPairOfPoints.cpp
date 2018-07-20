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
#include "Implementations\FastScan.cpp"
#include "2D\ClosestPairOfPoints.cpp"
#include "2D\Point.cpp"

using namespace std;

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

    //std::srand(std::time(nullptr)); // use current time as seed for random generator
                                    // Seed with a real random value, if available
    //std::random_device r;

    // Choose a random mean between 1 and 6
    //std::minstd_rand re(r());
    //std::uniform_int_distribution<int> uid(0, 20000000);
    long double t;

    int n, i;
    vector<Point<long double>> points, pointsByY, aux, P;
    Point p1, p2;

    //n = 2;
    while (true) {
        //n = 100000;
        //cout << n << "\n";
        fs(n);

        if (n <= 0)
            break;
        points.resize(n);
        pointsByY.resize(n);
        aux.resize(n);
        //P.resize(n);

        for (i = 0; i < n; ++i) {
            fsnd(points[i].x);
            fsnd(points[i].y);
            //cout << uid(re) << "\n";
            //points[i].x = (-10000000 + uid(re)) / 100.0;
            //points[i].y = (-10000000 + uid(re)) / 100.0;
            //cout << points[i].x << " " << points[i].y << "\n";
        }

        sort(points.begin(), points.end());
        //P = points;
        pointsByY = points;

        pair<long double, pair<Point<long double>, Point<long double>>> bestPair{ leastDist<long double, long long>(points, pointsByY, aux, 0, n - 1) };
        /*if (bestPair.first != bruteForce(P, p1, p2)) {
        cout << bestPair.second.first.x << " " << bestPair.second.first.y << " " << bestPair.second.second.x << " " << bestPair.second.second.y << "\n";
        cout << p1.x << " " << p1.y << " " << p2.x << " " << p2.y << "\n";

        cout << bruteForce(points, p1, p2) << " " << bestPair.first << "\n";
        cout << n << "\n";
        for (Point p : points)
        cout << p.x << " " << p.y << "\n";
        system("Pause");
        }*/
        printf("%.2f %.2f %.2f %.2f\n", bestPair.second.first.x, bestPair.second.first.y, bestPair.second.second.x, bestPair.second.second.y);
        //std::cout << std::setprecision(2);
        //std::cout << std::fixed;
        //cout << bestPair.second.first.x << " " << bestPair.second.first.y << " " << bestPair.second.second.x << " " << bestPair.second.second.y << "\n";
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