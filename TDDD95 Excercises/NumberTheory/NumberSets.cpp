//https://liu.kattis.com/sessions/ghkq7h/problems/numbersetseasy
//Leif Eriksson
//leier318
//Ugly bruteforce, but works
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
#include <complex>
#include <iomanip>

using namespace std;

#define _UNLOCKED 1
#if _UNLOCKED
#define gc() getchar_unlocked()
#else
#define gc() getchar()
#endif

//https://www.geeksforgeeks.org/fast-io-for-competitive-programming/
template<typename T>
void fastScan(T &number) {
    //variable to indicate sign of input number
    bool negative{ false };
    register T c;

    number = 0;

    // extract current character from buffer
    c = gc();
    while (!(c == '-' || (c > 47 && c < 58)))
        c = gc();

    if (c == '-')
    {
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
        for (T p(0.1); (c>47 && c<58); c = gc(), p *= 0.1)
            number += (c - 48)*p;
    }

    // if scanned input has a negative sign, negate the
    // value of the input number
    if (negative)
        number *= -1;
}


// To represent Disjoint Sets
struct DisjointSets {
    vector<int> parent, rnk;
    int n;

    // Constructor.
    DisjointSets(int n) : n(n), parent(n + 1), rnk(n + 1, 0) {
        // Allocate memory
        ++n;

        // Initially, all vertices are in
        // different sets and have rank 0.
        for (int i = 0; i < n; ++i) {
            //every element is parent of itself
            parent[i] = i;
        }
    }

    // Find the parent of a node 'u'
    // Path Compression
    int find(int u) {
        /* Make the parent of the nodes in the path
        from u--> parent[u] point to parent[u] */
        if (u != parent[u])
            parent[u] = find(parent[u]);
        return parent[u];
    }

    // Union by rank
    void merge(int x, int y) {
        x = find(x), y = find(y);

        /* Make tree with smaller height
        a subtree of the other tree  */
        if (rnk[x] > rnk[y])
            parent[y] = x;
        else // If rnk[x] <= rnk[y]
            parent[x] = y;

        if (rnk[x] == rnk[y])
            ++rnk[y];
    }

    int size() {
        int s(0);
        for (int i = 0; i < n; ++i) {
            if (i == find(i)) {
                ++s;
            }
        }
        return s;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int a, b, p, i, j, l, c, k, t;
    vector<bool> pr(1001, 1);
    pr[0] = 0;
    pr[1] = 0;

    for (i = 4; i < 1001; i += 2) {
        pr[i] = 0;
    }

    for (i = 3; i*i < 1001; i += 2) {
        if (pr[i]) {
            for (j = i*i; j < 1001; j += i + i)
                pr[j] = 0;
        }
    }

    fastScan(t);
    for (int t2(1); t2 <= t; ++t2) {

        fastScan(a);
        fastScan(b);
        fastScan(p);


        DisjointSets ds(b - a + 1);

        vector<vector<int>> m(b - a + 1);
        for (i = a, j = 0; i <= b; ++i, ++j) {
            for (l = p; l <= b && l <= i; ++l) {
                if (pr[l] && i % l == 0) {
                    m[j].push_back(l);
                }
            }
        }

        for (i = 0; i < b - a; ++i) {
            c = ds.find(i);
            for (j = i + 1; j < b - a + 1; ++j) {
                if (c != ds.find(j)) {
                    for (l = 0; l < m[i].size(); ++l) {
                        for (k = 0; k < m[j].size(); ++k) {
                            if (m[i][l] == m[j][k]) {
                                ds.merge(i, j);
                                c = ds.find(i);
                                break;
                            }
                        }
                    }
                }
            }
        }

        printf("Case #%d: %d\n", t2, ds.size());
    }

    return 0;
}