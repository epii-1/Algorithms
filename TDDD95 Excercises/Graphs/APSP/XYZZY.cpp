//https://liu.kattis.com/problems/xyzzy
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
    for (; (c>47 && c<58); c = getchar_unlocked())
        number = number * 10 + c - 48;

    // if scanned input has a negative sign, negate the
    // value of the input number
    if (negative)
        number *= -1;
}

struct Node {
    long long dist{ std::numeric_limits<long long>::max() };
    int parent{ -1 };
    bool bad{ false };
    vector<int> edge;
    int e;
};

//Skeleton taken from https://www.geeksforgeeks.org/dynamic-programming-set-23-bellman-ford-algorithm/
//Changed to class, now actually marks bad cycles and saves parents for path construction
//And now changed to adjanecy list instead of edgelist

// The main function that finds shortest distances from src to
// all other vertices using Bellman-Ford algorithm.  The function
// also detects negative weight cycle
template<typename T>
class BellmanFord {
public:
    vector<Node> nodes;
    vector<int> parent;

    void solve() {
        // Step 1: Initialize distances from src to all other vertices
        // as INFINITE
        nodes[_src].dist = -100;
        nodes[_src].parent = _src;

        // Step 2: Relax all edges |V| -1 times. A simple shortest 
        // path from src to any other vertex can have at-most |V| - 1 
        // edges

        int i, j, size;
        int u, v, w;
        int tv{ _V };
        while (--tv) {
            for (i = 0; i < _V; ++i) {
                if (nodes[i].parent != -1) {
                    size = nodes[i].edge.size();
                    for (j = 0; j < size; ++j) {
                        u = nodes[i].dist;
                        v = nodes[i].edge[j];
                        w = nodes[v].e;
                        if (u + w < nodes[v].dist && u + w < 0) {
                            nodes[v].dist = u + w;
                            nodes[v].parent = i;
                        }
                    }
                }
            }
        }

        // Step 3: check for negative-weight cycles.  The above step 
        // guarantees shortest distances if graph doesn't contain 
        // negative weight cycle. If we get a shorter path, then there
        // is a cycle.

        stack<int> s;

        //Find cicles
        for (i = 0; i < _V; ++i) {
            if (nodes[i].parent != -1) {
                size = nodes[i].edge.size();
                for (j = 0; j < size; ++j) {
                    u = nodes[i].dist;
                    v = nodes[i].edge[j];
                    w = nodes[v].e;
                    if ((u + w < nodes[v].dist  && u + w < 0) || nodes[i].bad) {
                        if (!nodes[v].bad)
                            s.push(v);
                        nodes[v].bad = true;
                        nodes[v].parent = i;
                    }
                }
            }
        }

        while (!s.empty()) {
            //DFS to find all cycle dependant nodes
            i = s.top();
            s.pop();
            size = nodes[i].edge.size();
            for (j = 0; j < size; ++j) {
                v = nodes[i].edge[j];
                if (!nodes[v].bad)
                    s.push(v);
                nodes[v].bad = true;
                nodes[v].parent = i;
            }
        }
    }

    BellmanFord(int V, int src) : _V(V), _src(src), nodes(V) {}

    pair<int, T> shortestPath(int target) {
        if (nodes[target].bad)
            return { -1, 0 };
        if (nodes[target].parent == -1)
            return { 1, 0 };
        return { 0, nodes[target].dist };
    }

private:
    int _V, _src;
};

int main() {
    ios::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);

    int n, m, s, i, j, q, t1, t2, t3;
    while (true) {
        //input blablabla
        fastScan(n);

        if (n == -1)
            break;


        BellmanFord<long long> bf(n, 0);

        for (i = 0; i < n; ++i) {
            fastScan(t1);
            fastScan(t2);
            bf.nodes[i].e = -t1;
            for (j = 0; j < t2; ++j) {
                fastScan(t1);
                --t1;
                bf.nodes[i].edge.push_back(t1);
            }
        }
        bf.solve();
        pair<int, long long> solution(bf.shortestPath(n - 1));
        if (solution.first == -1)
            printf("winnable\n");
        else {
            if (solution.first == 1)
                printf("hopeless\n");
            else
                printf("winnable\n");
        }
    }

    return 0;
}