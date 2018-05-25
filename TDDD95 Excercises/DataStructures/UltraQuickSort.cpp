//https://liu.kattis.com/sessions/prsaxh/problems/ultraquicksort
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
#include <stdio.h>
#include <bits/stdc++.h>

using namespace std;


template<typename T, typename S = int>
class FenwickTree {
    /*            n  --> No. of elements present in input array.
    BITree[0..n] --> Array that represents Binary Indexed Tree.
    arr[0..n-1]  --> Input array for whic prefix sum is evaluated. */
public:

    FenwickTree(S n) : _n{ n }, _v(n + 1, 0) {}

    // Constructs and returns a Binary Indexed Tree for given
    // array of size n.
    FenwickTree(const vector<T> &v) : _n{ v.size() }, _v(v.size() + 1, 0) {
        // Store the actual values in BITree[] using update()
        for (S i(0); i < _n; ++i)
            update(i, v[i]);
    }

    // Constructs and returns a Binary Indexed Tree for given
    // size and value.
    FenwickTree(S n, T value) : _n{ n }, _v(n + 1, 0) {
        // Store the actual values in BITree[] using update()
        //++n;
        while (n)
            update(--n, value);
    }

    // Returns sum of arr[0..index]. This function assumes
    // that the array is preprocessed and partial sums of
    // array elements are stored in BITree[].
    T sum(S index) {
        T sum{ 0 }; // Iniialize result

                    // index in BITree[] is 1 more than the index in arr[]
        ++index;

        // Traverse ancestors of BITree[index]
        while (index>0) {
            // Add current element of BITree to sum
            sum += _v[index];

            // Move index to parent node in getSum View
            index -= index & (-index);
        }
        return sum;
    }

    //Including
    T sum(S index, S index2) {
        return sum(index2) - sum(index - 1);
    }

    // Updates a node in Binary Index Tree (BITree) at given index
    // in BITree.  The given value 'val' is added to BITree[i] and
    // all of its ancestors in tree.
    void update(S index, T val) {
        // index in BITree[] is 1 more than the index in arr[]
        ++index;

        // Traverse all ancestors and add 'val'
        while (index <= _n) {
            // Add 'val' to current node of BI Tree
            _v[index] += val;

            // Update index to that of parent in update View
            index += index & (-index);
        }
    }

private:
    S _n;
    vector<T> _v;
};

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
    for (; (c>47 && c<58); c = getchar_unlocked())
        number = number * 10 + c - 48;

    // if scanned input has a negative sign, negate the
    // value of the input number
    if (negative)
        number *= -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    long long n, t, o{ 0 };
    fastScan(n);

    FenwickTree<long long, long long> ft(n, 1);
    //priority_queue<pair<long long, int>, vector<pair<long long, int>>, [](const pair<long long, int> & lhs, const pair<long long, int> & rhs)->bool{return lhs.first < rhs.first;}> pq;
    vector<pair<long long, int>> v(n);

    for (int i(0); i < n; ++i) {
        fastScan(t);
        //pq.push(make_pair(t,i));
        v[i] = make_pair(t, i);
    }

    stable_sort(v.begin(), v.end(), [](const pair<long long, int> & lhs, const pair<long long, int> & rhs)->bool {return lhs.first < rhs.first; });

    //while(!pq.empty()){
    //    pair<long long, int> curr = pq.top(), pq.pop();
    //    ft.update(curr.second, -1);
    //    o += ft.sum(curr.second);
    //}

    for (int i{ 0 }; i < n; ++i) {
        ft.update(v[i].second, -1);
        o += ft.sum(v[i].second);
    }

    printf("%lld\n", o);

    return 0;
}
