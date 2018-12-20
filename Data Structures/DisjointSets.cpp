//https://open.kattis.com/problems/unionfind
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
#include <memory>
#include <cstring>

template<typename T>
void fastFill(T* v, const T& x, size_t n) {
    if (n == 0)
        return;
    size_t s(1);
    *v = x;
    while (s + s <= n) {
        memcpy((v + s), v, s * sizeof(x));
        s += s;
    }
    memcpy((v + s), v, (n - s) * sizeof(x));
}

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
//Sligthly modified 

#define DISJOINT_SET_SIZE 1

// To represent Disjoint Sets
//negative rank indicate parent, with semi-height -i
//positive rank indicate child with parent i
template <typename T = size_t>
struct DisjointSets {
    T *parent, *rnk;
    T n;
#if DISJOINT_SET_SIZE == 1
    T size;
#endif

    // Constructor.
    DisjointSets(T n) : rnk(new T(n)), n(n)
#if DISJOINT_SET_SIZE == 1
        , size(n)
#endif
    {//, parent(n), rnk(n) {
     // Allocate memory
     // Initially, all vertices are in
     // different sets and have rank 0.
     //parent = new T[n];
        fastFill(rnk, -1, n);
    }

    ~DisjointSets() {
        delete[] rnk;
    }

    // Find the parent of a node 'u'
    // Path Compression
    T find(T x) {
        /* Make the parent of the nodes in the path
        from u--> parent[u] point to parent[u] */
        if (rnk[x] > -1)
            return rnk[x] = find(rnk[x]);
        //Should we upate the rnk of x if the graph gets flatter?
        //How should we detect that?
        return x;
    }

    // Union by rank
    void merge(T x, T y) {
        if ((x = find(x)) == (y = find(y)))
            return;
#if DISJOINT_SET_SIZE == 1
        --size;
#endif
        /* Make tree with smaller height
        a subtree of the other tree  */
        if (rnk[x] > rnk[y])
            swap(x, y);

        if (rnk[x] == rnk[y])
            --rnk[x];
        rnk[y] = x;
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
    DisjointSets<int> ds(n);

    ++q;
    int u, v;
    char t;
    while (--q) {
        t = gc();
        while (t != '=' && t != '?')
            t = gc();

        fastScan(u);
        fastScan(v);
        if (t == '=') {
            ds.merge(u, v);
        }
        else if (t == '?') {
            u = ds.find(u);
            v = ds.find(v);
            if (u == v)
                printf("yes\n");
            else
                printf("no\n");
        }
    }

    return 0;
}