//https://liu.kattis.com/problems/maxcolinear
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
#include "2D\MaxColinearPoints.cpp"

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);

    int n, m, x1, x2, x3, x4, y1, y2, y3, y4, i;

    vector<Point<int>> p;

    while (true) {
        fsn(n);
        if (n == 0)
            break;
        p.resize(n);
        for (i = 0; i < n; ++i) {
            fsn(x1);
            fsn(y1);
            p[i].x = x1;
            p[i].y = y1;
        }

        printf("%zu\n", number_of_colinear<int>(p));
    }

    system("Pause");
    return 0;
}