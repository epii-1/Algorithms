//https://liu.kattis.com/problems/knapsack
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
#include <bitset>
#include <bits/stdc++.h>

using namespace std;

//https://www.geeksforgeeks.org/fast-io-for-competitive-programming/
template<typename T>
bool fastScan(T &number)
{
    //variable to indicate sign of input number
    bool negative = false;
    register T c;

    number = 0;

    // extract current character from buffer
    c = getchar_unlocked();
    while (!(c == '-' || (c > 47 && c < 58) || c == EOF))
        c = getchar_unlocked();

    if (c == EOF)
        return false;

    if (c == '-')
    {
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
        for(; (c>47 && c<58); c = getchar_unlocked(), pot*=0.1)
            number += (c - 48)*pot;
    }
    
    // if scanned input has a negative sign, negate the
    // value of the input number
    if (negative)
        number *= -1;
    return true;
}

void knapsack(int c, vector<pair<int, int>> & valueAweight, vector<int>& result) {
    //Contains current value and index vector
    vector<pair<unsigned long long, vector<int>>> dynamicVector(c + 1);

    dynamicVector[0].first = 1; //Only to diff from 0

    int i,j, newIndex;
    unsigned long long newValue;

    //For all objects
    for (i = 0; i < valueAweight.size(); ++i) {
        //For the whole container (backwards to not add same twice)
        for (j = c - 1; j > -1; --j) {
            //Need to already exists
            if (dynamicVector[j].first != 0) {
                newValue = dynamicVector[j].first + valueAweight[i].first;
                newIndex = j + valueAweight[i].second;
                //If better
                if (newIndex <= c && dynamicVector[newIndex].first < newValue) {
                    dynamicVector[newIndex].first = newValue;
                    dynamicVector[newIndex].second = dynamicVector[j].second;
                    dynamicVector[newIndex].second.push_back(i);
                }
            }
        }
    }

    int maxValIndex = c;
    int maxVal = 0;
    for (i = c; i > 0; --i)
        if (dynamicVector[i].first > maxVal) {
            maxValIndex = i;
            maxVal = dynamicVector[i].first;
        }

    result.resize(dynamicVector[maxValIndex].second.size());
    copy(dynamicVector[maxValIndex].second.begin(), dynamicVector[maxValIndex].second.end(), result.begin());
}

int main() {
    //ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    double c;

    int n, i, t1, t2;
    
    while (fastScan(c)) {
        //Input
        fastScan(n);
        
        vector<pair<int, int>> v(n);
        for (i = 0; i < n; ++i) {
            fastScan(t1);
            fastScan(t2);
            v[i] = make_pair(t1, t2);
        }

        //Solve
        vector<int> result;
        knapsack(c, v, result);

        //Output
        printf("%zu\n", result.size());
        copy(result.begin(), result.end(), ostream_iterator<int>(cout, " "));
        printf("\n");
    }

    return 0;

}