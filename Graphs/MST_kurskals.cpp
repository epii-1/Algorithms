//https://liu.kattis.com/problems/minspantree
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
void fastScan(T &number) {
    //variable to indicate sign of input number
    bool negative{ false };
    register T c;

    number = 0;

    // extract current character from buffer
    c = getchar_unlocked();
    while (!(c == '-' || (c > 47 && c < 58)))
        c = getchar_unlocked();

    if (c == '-')    {
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
};

/* Functions returns weight of the MST*/

pair<bool, long long> kruskalMST(vector<pair<int, pair<int, int>>> & edges,
    vector<pair<int, int>> &mstEdges) {
    int mst_wt{ 0 }; // Initialize result

                     // Sort edges in increasing order on basis of cost
    sort(edges.begin(), edges.end());

    // Create disjoint sets
    DisjointSets ds(mstEdges.size());

    int u, v, set_u, set_v, count(0);

    // Iterate through all sorted edges
    vector< pair<int, pair<int, int>> >::const_iterator it{ edges.begin() };
    for (; it != edges.end(); ++it) {
        u = it->second.first;
        v = it->second.second;

        set_u = ds.find(u);
        set_v = ds.find(v);

        // Check if the selected edge is creating
        // a cycle or not (Cycle is created if u
        // and v belong to same set)
        if (set_u != set_v) {
            // Current edge will be in the MST
            // so print it
            mstEdges[count] = { u,v };
            ++count;
            // Update MST weight
            mst_wt += it->first;

            // Merge two sets
            ds.merge(set_u, set_v);
        }
    }

    return { count == mstEdges.size(), mst_wt };
}

int main() {
    ios::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);

    int n, m, u, v, c;
    long long x, r;
    vector<pair<int, pair<int, int>>> edges;
    vector<pair<int, int>> mstEdges;
    while (true) {
        fastScan(n);
        fastScan(m);

        if (n == 0 && m == 0)
            break;

        edges.resize(m);

        //++m;
        while (m) {
            fastScan(u);
            fastScan(v);
            fastScan(c);
            if (u > v)
                swap(u, v);
            edges[--m] = { c,{ u, v } };
        }

        mstEdges.resize(n - 1);

        pair<bool, long long> success(kruskalMST(edges, mstEdges));

        if (!success.first) {
            printf("Impossible\n");
        }
        else {
            printf("%lld\n", success.second);
            sort(mstEdges.begin(), mstEdges.end(),
                [](const pair<int, int>& lhs, const pair<int, int>& rhs)->
                bool {return lhs.first < rhs.first ||
                (lhs.first == rhs.first && lhs.second < rhs.second); });
            for (pair<int, int> p : mstEdges)
                printf("%d %d\n", p.first, p.second);
        }

    }

    return 0;
}