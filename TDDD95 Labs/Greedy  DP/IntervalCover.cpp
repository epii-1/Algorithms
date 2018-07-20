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

using namespace std;

//https://www.geeksforgeeks.org/fast-io-for-competitive-programming/
template<typename T>
bool fastScan(T &number) {
    //variable to indicate sign of input number
    bool negative{ false };
    register T c;

    number = 0;

    // extract current character from buffer
    c = getchar_unlocked();
    while (!(c == '-' || c == EOF || (c > 47 && c < 58)))
        c = getchar_unlocked();

    if(c == EOF)
        return false;

    if (c == '-') {
        // number is negative
        negative = true;

        // extract the next character from the buffer
        c = getchar_unlocked();
    }

    // Keep on extracting characters if they are integers
    // i.e ASCII Value lies from '0'(48) to '9' (57)
    for (; (c>47 && c<58); c = getchar_unlocked())
        number = number * 10 + c - 48;

    if (c == '.') {
        c = getchar_unlocked();
        T pot(0.1);
        for (; (c>47 && c<58); c = getchar_unlocked(), pot *= 0.1)
            number += (c - 48)*pot;
    }

    // if scanned input has a negative sign, negate the
    // value of the input number
    if (negative)
        number *= -1;
        
    return true;
}

struct myInterval{
    double a, b;
    int i;
    myInterval(){}
    myInterval(double a, double b, int i) : a{a}, b{b}, i{i} {}
};

bool operator< (const myInterval & lhs, const myInterval & rhs){
    return lhs.a < rhs.a;
}

vector<int> cover(pair<double, double> interval, vector<myInterval> intervals){
    sort(intervals.begin(), intervals.end());

    vector<int> result;

    //Quick sanitycheck
    if(intervals[0].a > interval.first){
        return result;
    }

    myInterval curr = intervals[0];

    //loop untill whole interval covered
    int i{ 1 };
    bool found{ true };
    do{
        for(; i < intervals.size() && intervals[i].a <= interval.first; ++i){
            if(curr.b < intervals[i].b){
                curr = intervals[i];
                found = true;
            }
        }

        //Controll
        if(!found || found && (curr.a > interval.first || curr.b < interval.first)){
            result.clear();
            return result;
        }

        result.push_back(curr.i);
        interval.first = curr.b;
        found = false;
    }while(interval.first < interval.second);

    return result;
}

//Main only contains input and output
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout.precision(17);

    double a, b;
    int n, i;

    vector<myInterval> inIntervals;
    double t1, t2;
    while(fastScan(a)){

        //Input
        fastScan(b);
        fastScan(n);

        inIntervals.resize(n);
        for(i = 0; i < n; ++i){
            fastScan(t1);
            fastScan(t2);
            inIntervals[i] = myInterval(t1,t2,i);
        }

        //Solve
        vector<int> result = cover(make_pair(a,b), inIntervals);

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