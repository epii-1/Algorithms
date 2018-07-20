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
#include "Implementations\FastScan.cpp"
#include "2D\Point.cpp"
#include "2D\Line.cpp"

using namespace std;


int main() {
    ios::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);

    int n, x1, x2, x3, x4, y1, y2, y3, y4;

    Line<long double> l1, l2;

    fs(n);
    ++n;
    //ofstream f;
    //f.open("outfile.txt");
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

        vector<Point<long double>> intersection{ l1.fullIntersect(l2) };

        //f << std::setprecision(2);
        //f << std::fixed;
		if (intersection.size() == 2) {
			sort(intersection.begin(), intersection.end());
			//f << intersection[0].x << " " << intersection[0].y << " " <<
			//    intersection[1].x << " " << intersection[1].y << "\n";
			printf("%0.2f %0.2f %0.2f %0.2f\n", intersection[0].x, intersection[0].y,
				intersection[1].x, intersection[1].y);
        }
        else if (intersection.size()) {
            //f << intersection[0].x << " " << intersection[0].y << "\n";
			printf("%0.2f %0.2f\n", intersection[0].x, intersection[0].y);
        }
        else {
            //f << "none\n";
            printf("none\n");
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