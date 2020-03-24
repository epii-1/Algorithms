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
#include <cstring>

using namespace std;

//https://www.geeksforgeeks.org/fast-io-for-competitive-programming/
template<typename T>
bool fastScan(T &number) {
    //variable to indicate sign of input number
    bool negative{ false };
    register T c;

    number = 0;

    // extract current character from buffer
    c = gc();
    while (!(c == '-' || (c > 47 && c < 58) || c == EOF))
        c = gc();

    if (c == EOF)
        return false;

    if (c == '-') {
        // number is negative
        negative = true;

        // extract the next character from the buffer
        c = gc();
    }

    // Keep on extracting characters if they are integers
    // i.e ASCII Value lies from '0'(48) to '9' (57)
    for (; (c>47 && c<58); c = gc())
        number = number * 10 + c - 48;

    if (c == '.') {
        c = gc();
        for(T pot(0.1); (c>47 && c<58); c = gc(), pot*=0.1)
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
    vector<pair<int, vector<int>>> dynamicVector(c + 1);

    dynamicVector[0].first = 1; //Only to diff from 0

    int i,j, newIndex;
    int newValue;

    int maxValIndex = c;
    int maxVal = 0;

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
                    dynamicVector[newIndex].second.resize(dynamicVector[j].second.size() + 1);
                    memcpy(&dynamicVector[newIndex].second[0], &dynamicVector[j].second[0], dynamicVector[j].second.size() * sizeof(0));
                    dynamicVector[newIndex].second.back() = i;
                    if (newValue > maxVal) {
                        maxValIndex = newIndex;
                        maxVal = newValue;
                    }
                }
            }
        }
    }

    result.resize(dynamicVector[maxValIndex].second.size());
    memcpy(&result[0], &dynamicVector[maxValIndex].second[0], result.size() * sizeof(0));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    double c;

    int n, i;
    vector<pair<int, int>> v;

    while (fastScan(c)) {
        //Input
        fastScan(n);
        
        v.resize(n);
        for (i = 0; i < n; ++i) {
            fastScan(v[i].first);
            fastScan(v[i].second);
        }

        //Solve
        vector<int> result;
        knapsack(c, v, result);

        //Output
        cout << result.size() << "\n";
        copy(result.begin(), result.end(), ostream_iterator<int>(cout, " "));
        cout << "\n";
    }

    return 0;
}