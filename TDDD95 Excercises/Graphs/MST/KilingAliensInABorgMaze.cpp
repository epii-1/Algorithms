//https://liu.kattis.com/problems/borg
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
//#include <bits/stdc++.h>

using namespace std;

//https://www.geeksforgeeks.org/fast-io-for-competitive-programming/
template<typename T>
void fastScan(T &number)
{
    register T c;

    number = 0;

    // extract current character from buffer
    c = getchar_unlocked();
    while (!(c > 47 && c < 58))
        c = getchar_unlocked();

    // Keep on extracting characters if they are integers
    // i.e ASCII Value lies from '0'(48) to '9' (57)
    for (; (c>47 && c<58); c = getchar_unlocked())
        number = number * 10 + c - 48;
}
//Taken from https://www.geeksforgeeks.org/kruskals-minimum-spanning-tree-using-stl-in-c/
//Sligthly modified to be able to return the tree

// To represent Disjoint Sets
struct DisjointSets
{
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

long long kruskalMST(vector<pair<int, pair<int, int>>> & edges, int V) {
    int mst_wt{ 0 }; // Initialize result

                     // Sort edges in increasing order on basis of cost
    sort(edges.begin(), edges.end());

    // Create disjoint sets
    DisjointSets ds(V);

    int u, v, set_u, set_v;

    // Iterate through all sorted edges
    vector< pair<int, pair<int, int>> >::iterator it;
    for (it = edges.begin(); it != edges.end(); ++it)
    {
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
            // Update MST weight
            mst_wt += it->first;

            // Merge two sets
            ds.merge(set_u, set_v);
        }
    }

    return mst_wt;
}

struct Node {
    Node(int x, int y, int t) : x(x), y(y), t(t) {}
    int x, y;
    int t;
};

int main() {
    ios::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);

    int N, x, y, i, j, nodes, cost;
    char c;
    fastScan(N);
    ++N;
    pair<int, int> start;
    while (--N) {
        fastScan(x);
        fastScan(y);

        vector<vector<char>> matrix(y, vector<char>(x, ' '));
        map<pair<int, int>, int> posToI;
        vector<pair<int, int>> aliens;
        vector<int> distanceToStart;
        nodes = 1;
        c = getchar_unlocked();
        for (i = 0; i < y; ++i) {
            for (j = 0; j < x; ++j) {
                while (c != '#' && c != ' ' && c != 'A' && c != 'S') c = getchar_unlocked();
                matrix[i][j] = c;
                if (c == 'A') {
                    posToI.insert(make_pair(make_pair(i, j), aliens.size()));
                    aliens.emplace_back(i, j), ++nodes;
                    distanceToStart.push_back(std::numeric_limits<int>::max() - 1);
                }
                else if (c == 'S')
                    start = make_pair(i, j);
                c = getchar_unlocked();
            }
        }

        vector<pair<int, pair<int, int>>> edges;

        --nodes;

        vector<vector<int>> visited(y, vector<int>(x, -1));

        for (i = 0; i < nodes; ++i) {
            queue<Node> q;
            q.emplace(aliens[i].first, aliens[i].second, 0);
            visited[aliens[i].first][aliens[i].second] = i;
            //int cont(std::numeric_limits<int>::max());
            while (!q.empty() && q.front().t < distanceToStart[i]) {
                Node neighbor(q.front());
                q.pop();
                if (matrix[neighbor.x][neighbor.y] == 'A' && (neighbor.x != aliens[i].first
                    || neighbor.y != aliens[i].second)) {
                    int alienIndex(posToI[make_pair(neighbor.x, neighbor.y)]);
                    edges.push_back({ neighbor.t,{ i, alienIndex } });
                    distanceToStart[i] = max(min(distanceToStart[i], distanceToStart[alienIndex] + 1), neighbor.t + 1);
                    //distanceToStart[alienIndex] = min(min(distanceToStart[i]+1, distanceToStart[alienIndex]),std::numeric_limits<int>::max()-1);
                }

                ++neighbor.t;
                ++neighbor.x;
                if (neighbor.x < y && matrix[neighbor.x][neighbor.y] != '#'
                    && visited[neighbor.x][neighbor.y] != i) {
                    if (matrix[neighbor.x][neighbor.y] == 'S') {
                        edges.push_back({ neighbor.t,{ i, nodes } });
                        distanceToStart[i] = min(neighbor.t, distanceToStart[i]);
                    }
                    visited[neighbor.x][neighbor.y] = i;
                    q.push(neighbor);
                }
                neighbor.x -= 2;
                if (neighbor.x > -1 && matrix[neighbor.x][neighbor.y] != '#'
                    && visited[neighbor.x][neighbor.y] != i) {
                    if (matrix[neighbor.x][neighbor.y] == 'S') {
                        edges.push_back({ neighbor.t,{ i, nodes } });
                        distanceToStart[i] = min(neighbor.t, distanceToStart[i]);
                    }
                    visited[neighbor.x][neighbor.y] = i;
                    q.push(neighbor);
                }
                ++neighbor.x;
                ++neighbor.y;
                if (neighbor.y < x && matrix[neighbor.x][neighbor.y] != '#'
                    && visited[neighbor.x][neighbor.y] != i) {
                    if (matrix[neighbor.x][neighbor.y] == 'S') {
                        edges.push_back({ neighbor.t,{ i, nodes } });
                        distanceToStart[i] = min(neighbor.t, distanceToStart[i]);
                    }
                    visited[neighbor.x][neighbor.y] = i;
                    q.push(neighbor);
                }
                neighbor.y -= 2;
                if (neighbor.y > -1 && matrix[neighbor.x][neighbor.y] != '#'
                    && visited[neighbor.x][neighbor.y] != i) {
                    if (matrix[neighbor.x][neighbor.y] == 'S') {
                        edges.push_back({ neighbor.t,{ i, nodes } });
                        distanceToStart[i] = min(neighbor.t, distanceToStart[i]);
                    }
                    visited[neighbor.x][neighbor.y] = i;
                    q.push(neighbor);
                }
            }
        }

        long long success(kruskalMST(edges, ++nodes));

        printf("%lld\n", success);

    }

    return 0;
}