//https://liu.kattis.com/problems/turbo
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
    for (; (c>47 && c<58); c = getchar_unlocked())
        number = number * 10 + c - 48;

    // if scanned input has a negative sign, negate the
    // value of the input number
    if (negative)
        number *= -1;
}


template<class T>
class FenwickTree {
    /*            n  --> No. of elements present in input array.
    BITree[0..n] --> Array that represents Binary Indexed Tree.
    arr[0..n-1]  --> Input array for whic prefix sum is evaluated. */
public:

    FenwickTree(int n) : _n{ n }, _v(_n + 1, 0) {}

    // Constructs and returns a Binary Indexed Tree for given
    // array of size n.
    FenwickTree(const vector<T> &v) : _n{ v.size() }, _v(_n + 1, 0) {
        // Store the actual values in BITree[] using update()
        for (int i = 0; i<_n; ++i)
            update(i, v[i]);
    }

    // Constructs and returns a Binary Indexed Tree for given
    // size and value.
    FenwickTree(int n, T value) : _n{ n }, _v(_n + 1, 0) {
        // Store the actual values in BITree[] using update()
        for (int i = 0; i<_n; ++i)
            update(i, value);
    }

    // Returns sum of arr[0..index]. This function assumes
    // that the array is preprocessed and partial sums of
    // array elements are stored in BITree[].
    T sum(int index) {
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
    T sum(int index, int index2) {
        return sum(index2) - sum(index - 1);
    }

    // Updates a node in Binary Index Tree (BITree) at given index
    // in BITree.  The given value 'val' is added to BITree[i] and 
    // all of its ancestors in tree.
    void update(int index, T val) {
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
    int _n;
    vector<T> _v;
};

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    fastScan(n);
    //cin >> n;

    vector<int> v(n);
    vector<int> v2(n);
    FenwickTree<int> ft{ n, 1 };

    int t;
    int i;
    for (i = 0; i < n; ++i) {
        //cin >> t;
        fastScan(t);
        v[i] = t;
        v2[t - 1] = i;
    }

    --n;

    int index;
    int s;
    for (i = 0; i < n; ++i) {
        if (!(i % 2)) {
            index = i / 2;
            s = ft.sum(v2[index]);
            ft.update(v2[index], -1);
            printf("%d \n", s - 1);
            //cout << s-1 << "\n";
        }
        else {
            index = n - i / 2;
            s = ft.sum(v2[index], n);
            ft.update(v2[index], -1);
            //cout << s-1 << "\n";
            printf("%d \n", s - 1);
        }
    }

    //cout << 0 << "\n";
    //put("0\n");
    printf("0\n");

    return 0;

}