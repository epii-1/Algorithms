//https://liu.kattis.com/problems/shortestpath3
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
#include "Implementations\FastScan.cpp"
#include "Graphs\SSSP.cpp"

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);

    int n, m, s, i, q, t1, t2;
    int t3;
    while (true) {
        //input blablabla
        fs(n);
        fs(m);
        fs(q);
        fs(s);

        if (n == 0 && m == 0 && q == 0 && s == 0)
            break;

        BellmanFord<int,int> bf(n, s);

        ++m;
        while (--m) {
            //input blablabla
            fs(t1);
            fs(t2);
            fsn(t3);
            bf.nodes[t1].edge.push_back({ t2,t3 });
        }

        bf.solve();

        ++q;
        while (--q) {
            fastScan(t1);

            //Finaly calculate and output distance!
            pair<short, int> solution(bf.shortestPath(t1));
            if (solution.first == -1)
                puts("-Infinity");
            else {
                if (solution.first == 1)
                    puts("Impossible");
                else
                    printf("%d\n", solution.second);
            }
        }
        printf("\n");
    }

    return 0;
}