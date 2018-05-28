//https://liu.kattis.com/problems/longincsubseq
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

    // if scanned input has a negative sign, negate the
    // value of the input number
    if (negative)
        number *= -1;
        
    return true;
}

//All hail wikipedia :)
//https://en.wikipedia.org/wiki/Longest_increasing_subsequence
void lis(int n, vector<int> & list) {
    //list is X
    vector<int> predecessor(n); //P
    vector<int> m(n + 1); //M : index of biggest for size i

    int l{ 0 }, i{ 0 }, low, high, mid, newL;
    for (; i < n; ++i) {
        // Binary search for the largest positive i <= L
        // such that X[M[j]] < X[i]
        low = 1;
        high = l;
        while (low <= high) {
            mid = (low + high + 1) >> 1;
            if (list[m[mid]] < list[i])
                low = mid + 1;
            else
                high = mid - 1;
        }

        // After searching, lo is 1 greater than the
        // length of the longest prefix of X[i]
        newL = low;

        // The predecessor of X[i] is the last index of 
        // the subsequence of length newL-1
        predecessor[i] = m[newL - 1];
        m[newL] = i;

        // If we found a subsequence longer than any we've
        // found yet, update L
        if (newL > l)
            l = newL;

    }

    // Reconstruct the longest increasing subsequence
    //vector<int> result(l);
    list.resize(l);
    int k( m[l] );
    for (i = l-1; i > -1; --i){
        list[i] = k;
        k = predecessor[k];
    }

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n,i,t;

    while (fastScan(n)) {
        //Input
        vector<int> v;
        v.reserve(n);
        for (i = 0; i < n; ++i) {
            fastScan(t);
            v.push_back(t);
        }

        //Solve
        lis(n, v);

        //Output
        cout << v.size() <<"\n";
        copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
        cout << "\n";
    }

    return 0;

}