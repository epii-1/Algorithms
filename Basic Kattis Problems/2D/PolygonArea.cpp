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
#include "Implementations\FastScan.cpp"
#include "2D\Poly.cpp"
#include "2D\Point.cpp"

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);

    int n, m, x1, x2, x3, x4, y1, y2, y3, y4, i;
    long double a;

    Poly<long double> p;
    Point<long double> po;

    while (true) {
        fs(n);
        if (n == 0)
            break;
        p.lines.resize(n);
        fsn(p.lines[0].p1.x);
		fsn(p.lines[0].p1.y);
        for (i = 1; i < n; ++i) {
			fsn(p.lines[i].p1.x);
			fsn(p.lines[i].p1.y);
            p.lines[i - 1].p2.x = p.lines[i].p1.x;
            p.lines[i - 1].p2.y = p.lines[i].p1.y;
        }
        p.lines.back().p2.x = p.lines[0].p1.x;
        p.lines.back().p2.y = p.lines[0].p1.y;

        a = p.area();

        if (a > 0)
            cout << "CW";
        else
            cout << "CCW";
		printf(" %0.2f\n", abs(a));
    }

    return 0;
}