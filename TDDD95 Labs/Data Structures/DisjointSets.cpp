//https://liu.kattis.com/problems/unionfind
//Leif Eriksson
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

using namespace std;

#define _UNLOCKED 0
#if _UNLOCKED
#define gc() getchar_unlocked()
#else
#define gc() getchar()
#endif

//https://www.geeksforgeeks.org/fast-io-for-competitive-programming/
template<typename T>
void fastScan(T &number) {
	register T c;

	number = 0;

	// extract current character from buffer
	c = gc();
	while (!(c > 47 && c < 58))
		c = gc();

	// Keep on extracting characters if they are integers
	// i.e ASCII Value lies from '0'(48) to '9' (57)
	for (; (c>47 && c<58); c = gc())
		number = number * 10 + c - 48;
}

//Taken from https://www.geeksforgeeks.org/kruskals-minimum-spanning-tree-using-stl-in-c/
//Sligthly modified (There is an older version (2573617) that I wrote from scratch myself, but you know, speed)

// To represent Disjoint Sets
template <typename T = size_t>
struct DisjointSets {
    vector<T> parent, rnk;
    T n;

    // Constructor.
    DisjointSets(T n) : n(n), parent(n + 1), rnk(n + 1, 0) {
        // Allocate memory
        ++n;

        // Initially, all vertices are in
        // different sets and have rank 0.
		for (T i{ 0 }; i < n; ++i) {
            //every element is parent of itself
            parent[i] = i;
        }
    }

    // Find the parent of a node 'u'
    // Path Compression
    T find(T u) {
        /* Make the parent of the nodes in the path
        from u--> parent[u] point to parent[u] */
        if (u != parent[u])
            parent[u] = find(parent[u]);
        return parent[u];
    }

    // Union by rank
    void merge(T x, T y) {
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
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, q;
    fastScan(n);
    fastScan(q);

    // Create disjoint sets
    DisjointSets ds(n);

    ++q;
    int set_u, set_v, u, v;
    char t;
    while (--q) {
        t = getchar_unlocked();
        while (t != '=' && t != '?')
            t = getchar_unlocked();

        fastScan(u);
        fastScan(v);
        set_u = ds.find(u);
        set_v = ds.find(v);
        if (t == '=') {
            ds.merge(set_u, set_v);
        }
        else if (t == '?') {
            if (set_u == set_v)
                puts("yes\n");
            else
                puts("no\n");
        }
    }

    return 0;
}