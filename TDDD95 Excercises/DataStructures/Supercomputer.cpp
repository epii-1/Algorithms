//https://liu.kattis.com/sessions/prsaxh/problems/supercomputer
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

    FenwickTree(S n) : _n{ n + 1 }, _v(n + 2, 0), _bv(n + 2, false) {}

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
    void flip(S index) {
        // index in BITree[] is 1 more than the index in arr[]
        ++index;

        char val{ 1 };

        if (_bv[index])
            val = -1;

        _bv[index] = !_bv[index];


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
    vector<bool> _bv;
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

    long long N, K, t1, t2;
    char c;

    fastScan(N);
    fastScan(K);

    FenwickTree<long long, long long> ft(N);

    ++K;
    while (--K) {
        c = getchar_unlocked();
        while (c != 'F' && c != 'C') c = getchar_unlocked();
        fastScan(t1);

        if (c == 'F') {
            ft.flip(t1);
        }
        else {
            fastScan(t2);
            printf("%lld\n", ft.sum(t1, t2));
        }

    }

    return 0;
}
