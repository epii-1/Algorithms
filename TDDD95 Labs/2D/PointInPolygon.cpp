//https://liu.kattis.com/problems/pointinpolygon
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
#include "Implementations\FastScan.cpp"
#include "2D\Poly.cpp"
#include "2D\Point.cpp"

using namespace std;


int main() {
    ios::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);

    int n, m, x1, x2, x3, x4, y1, y2, y3, y4, i;

	//Have to go with float as the 2D's lack some pure integer support
    Poly<float> p;
    Point<float> po;

    while (true) {
        fs(n);
        if (n == 0)
            break;
        p.lines.resize(n);
		fsn(x1);
		fsn(y1);
        p.lines[0].p1.x = x1;
        p.lines[0].p1.y = y1;
        for (i = 1; i < n; ++i) {
			fsn(x1);
			fsn(y1);
            p.lines[i].p1.x = x1;
            p.lines[i].p1.y = y1;
            p.lines[i - 1].p2.x = x1;
            p.lines[i - 1].p2.y = y1;
        }
        p.lines.back().p2.x = p.lines[0].p1.x;
        p.lines.back().p2.y = p.lines[0].p1.y;

		fs(m);
        ++m;
        while (--m) {
			fsn(x1);
			fsn(y1);
            po.x = x1;
            po.y = y1;

            switch (p.in(po)) {
            case IN:
                printf("in\n");
                break;
            case OUT:
                printf("out\n");
                break;
            case ON:
                printf("on\n");
                break;
            }
        }
    }

    return 0;
}