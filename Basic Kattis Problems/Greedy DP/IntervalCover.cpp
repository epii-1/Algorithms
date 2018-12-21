//https://liu.kattis.com/problems/intervalcover
//Leif Eriksson
//leier318

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <random>
#include <iterator>
#include <tuple>
#include <string>
#include <functional>
#include <queue>
#include <set>
#include <unordered_set>
#include <iterator>
#include <sstream>
#include <map>
#include <cctype>
#include <bitset>
#include "Implementations\FastScan.cpp"
#include "Greedy DP\IntervalCover.cpp"

using namespace std;

//Main only contains input and output
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    double a, b;
    int n, i;

    vector<myInterval<double>> inIntervals;
    double t1, t2;
    while(fsndb(a)){

        //Input
		fsnd(b);
		fs(n);

        inIntervals.resize(n);
        for(i = 0; i < n; ++i){
            fsnd(t1);
            fsnd(t2);
            inIntervals[i] = myInterval<double>(t1,t2,i);
        }

        //Solve
		vector<int> result(cover<double>({ a,b }, inIntervals));

        //Output
        if(result.size() == 0){
            cout << "impossible\n";
        }else{
            cout << result.size() << "\n";
            std::copy(result.begin(), result.end(), std::ostream_iterator<int>(std::cout, " "));
            cout << "\n";
        }
    }
    return 0;
}