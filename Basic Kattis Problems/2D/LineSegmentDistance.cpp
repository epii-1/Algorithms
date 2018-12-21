//https://liu.kattis.com/problems/segmentdistance
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
#include "2D\Point.cpp"
#include "2D\Line.cpp"

using namespace std;


int main() {
	ios::sync_with_stdio(false);
	cout.tie(nullptr);
	cin.tie(nullptr);

	int n, n1, n2, x1, x2, x3, x4, y1, y2, y3, y4, i, j;


	long double minD;
	Line<long double> l1, l2;

	fs(n);
	++n;
	while (--n) {
		fsn(x1);
		fsn(y1);
		fsn(x2);
		fsn(y2);
		fsn(x3);
		fsn(y3);
		fsn(x4);
		fsn(y4);

		l1.p1.x = x1;
		l1.p1.y = y1;
		l1.p2.x = x2;
		l1.p2.y = y2;
		l2.p1.x = x3;
		l2.p1.y = y3;
		l2.p2.x = x4;
		l2.p2.y = y4;

		minD = min(l1.dist(l2.p1), l1.dist(l2.p2));
		minD = min(minD, l2.dist(l1.p1));
		minD = min(minD, l2.dist(l1.p2));

		if (l1.p1 != l1.p2 && l2.p1 != l2.p2) {
			Point<long double> p(l1.intersect(l2));
			if (l1.on(p) && l2.on(p))
				minD = 0;
		}

		printf("%.2f\n", minD);

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
