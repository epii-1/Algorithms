//https://liu.kattis.com/sessions/zbhcac/problems/princeandprincess
//Leif Eriksson
//With Teo Tiefenbacher and Olav Övrebö
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
#include <bits/stdc++.h>

using namespace std;

//https://www.geeksforgeeks.org/fast-io-for-competitive-programming/
template<typename T>
void fastScan(T &number)
{
    //variable to indicate sign of input number
    bool negative = false;
    register T c;

    number = 0;

    // extract current character from buffer
    c = getchar_unlocked();
    while (!(c == '-' || (c > 47 && c < 58)))
        c = getchar_unlocked();

    if (c == '-')
    {
        // number is negative
        negative = true;

        // extract the next character from the buffer
        c = getchar_unlocked();
    }

    // Keep on extracting characters if they are integers
    // i.e ASCII Value lies from '0'(48) to '9' (57)
    for (; (c > 47 && c < 58); c = getchar_unlocked())
        number = number * 10 + c - 48;

    if (c == '.') {
        c = getchar_unlocked();
        long double pot{ 0.1 };
        for (; (c > 47 && c < 58); c = getchar_unlocked(), pot *= 0.1)
            number += (c - 48)*pot;
    }

    // if scanned input has a negative sign, negate the
    // value of the input number
    if (negative)
        number *= -1;
}

//All hail wikipedia :)
//https://en.wikipedia.org/wiki/Longest_increasing_subsequence
void lis(int n, vector<int> & list) {
    //list is X
    vector<int> predecessor(n); //P
    vector<int> m(n + 1); //M : index of biggest for size i

    int l{ 0 }, i, low, high, mid, newL;
    for (i = 0; i < n; ++i) {
        // Binary search for the largest positive i <= L
        // such that X[M[j]] < X[i]
        low = 1;
        high = l;
        while (low <= high) {
            mid = ceil((low + high) / 2.0);
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
    int k(m[l]);
    for (i = l - 1; i > -1; --i) {
        list[i] = k;
        k = predecessor[k];
    }

}

int main() {
    //ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, i, t, N, m, s;

    fastScan(N);
    ++N;
    s = 0;
    while (--N) {
        ++s;
        fastScan(n);
        fastScan(m);
        fastScan(t);
        ++m;
        ++t;
        map<int, int> ma;
        vector<int> v;
        for (i = 0; i < m; ++i) {
            fastScan(n);
            ma[n] = i;
            //cout << n << "\n";
        }
        for (i = 0; i < t; ++i) {
            fastScan(n);
            auto it(ma.find(n));
            //cout << n << "\n";
            if (it != ma.end()) {
                //cout << it->first << " " << it->second << "\n";
                v.push_back(it->second);
            }
        }
        //copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
        //Solve
        lis(v.size(), v);
        //Output
        printf("Case %d: %zu\n", s, v.size());
    }

    return 0;

}
