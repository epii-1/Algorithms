//https://liu.kattis.com/problems/mincostmaxflow
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

using namespace std;

//https://www.geeksforgeeks.org/fast-io-for-competitive-programming/
template<typename T>
void fastScan(T &number) {
    //variable to indicate sign of input number
    bool negative{ false };
    register T c;

    number = 0;

    // extract current character from buffer
    c = getchar();
    while (!(c == '-' || (c > 47 && c < 58)))
        c = getchar();

    if (c == '-') {
        // number is negative
        negative = true;

        // extract the next character from the buffer
        c = getchar();
    }

    // Keep on extracting characters if they are long longegers
    // i.e ASCII Value lies from '0'(48) to '9' (57)
    for (; (c > 47 && c < 58); c = getchar())
        number = number * 10 + c - 48;

    // if scanned input has a negative sign, negate the
    // value of the input number
    if (negative)
        number *= -1;
}

struct Edge {
    Edge(long long u, long long v, long long c, long long rev, long long cf, long long cost, bool b) : u(u), v(v), c(c), rev(rev), cost(cost), orgCost(cost), flow{ cf }, isRev{ b } {}
    long long u, v, c, rev, cost, orgCost;
    long long flow, minFlow;
    bool isRev;
};

struct Node {

    vector<Edge> edges;
    vector<long long> reverse;

    long long dist{ std::numeric_limits<long long>::max() };
    pair<long long, long long> parent;
    bool bad;
    long long cc;
};



//Skeleton taken from https://www.geeksforgeeks.org/dynamic-programming-set-23-bellman-ford-algorithm/
//Changed to class, now actually marks bad cycles and saves parents for path construction
//And now changed to adjanecy list instead of edgelist

// The main function that finds shortest distances from src to
// all other vertices using Bellman-Ford algorithm.  The function
// also detects negative weight cycle
class BellmanFord {
public:
    void solve(vector<Node>& nodes) {
        for (Node &n : nodes) {
            n.dist = std::numeric_limits<long long>::max();
            n.parent.first = -1;
            n.bad = false;
            n.cc = 999999999;
        }

        // Step 1: Initialize distances from src to all other vertices
        // as INFINITE
        nodes[_src].dist = 0;
        nodes[_src].parent = { _src, -1 };

        // Step 2: Relax all edges |V| -1 times. A simple shortest 
        // path from src to any other vertex can have at-most |V| - 1 
        // edges

        long long i, j, size;
        long long u, v, w;
        long long tv{ _V };
        while (--tv) {
            for (i = 0; i < _V; ++i) {
                if (nodes[i].parent.first != -1) {
                    size = nodes[i].edges.size();
                    for (j = 0; j < size; ++j) {
                        u = nodes[i].dist;
                        v = nodes[i].edges[j].v;
                        w = nodes[i].edges[j].cost;
                        if (u + w < nodes[v].dist && nodes[i].edges[j].flow < nodes[i].edges[j].c) {
                            nodes[v].dist = u + w;
                            nodes[v].parent = { i, j };
                            if (nodes[i].edges[j].c - nodes[i].edges[j].flow < nodes[v].cc)
                                nodes[v].cc = nodes[i].edges[j].c - nodes[i].edges[j].flow;
                            if (nodes[i].cc < nodes[v].cc)
                                nodes[v].cc = nodes[i].cc;
                        }
                    }
                }
            }
        }

        // Step 3: check for negative-weight cycles.  The above step 
        // guarantees shortest distances if graph doesn't contain 
        // negative weight cycle. If we get a shorter path, then there
        // is a cycle.

        stack<long long> s;

        //Find cycles
        for (i = 0; i < _V; ++i) {
            if (nodes[i].parent.first != -1) {
                size = nodes[i].edges.size();
                for (j = 0; j < size; ++j) {
                    u = nodes[i].dist;
                    v = nodes[i].edges[j].v;
                    w = nodes[i].edges[j].cost;
                    if ((u + w < nodes[v].dist || nodes[i].bad) && nodes[i].edges[j].flow < nodes[i].edges[j].c) {
                        if (!nodes[v].bad)
                            s.push(v);
                        nodes[v].bad = true;
                        nodes[v].parent = { i, j };
                    }
                }
            }
        }

        while (!s.empty()) {
            //DFS to find all cycle dependant nodes
            i = s.top();
            s.pop();
            size = nodes[i].edges.size();
            for (j = 0; j < size; ++j) {
                if (nodes[i].edges[j].flow < nodes[i].edges[j].c) {
                    v = nodes[i].edges[j].v;
                    if (!nodes[v].bad)
                        s.push(v);
                    nodes[v].bad = true;
                    nodes[v].parent = { i, j };
                }
            }
        }
    }

    BellmanFord(long long V, long long src) : _V(V), _src(src) {}

    pair<long long, long long> shortestPath(long long target, vector<Node>& nodes) {
        if (nodes[target].bad)
            return { -1, 0 };
        if (nodes[target].parent.first == -1)
            return { 1, 0 };
        return { 0, nodes[target].dist };
    }

private:
    long long _V, _src;
};


//Reduce Cost()
void reduceCost(vector<Node> & nodes) {
    //For each(i, j) in Ex do
    size_t _V{ nodes.size() };
    for (long long i = 0; i < _V; ++i) {
        size_t size = nodes[i].edges.size();
        for (long long j = 0; j < size; ++j) {
            if (!nodes[i].edges[j].isRev) {
                nodes[i].edges[j].cost += nodes[i].dist - nodes[nodes[i].edges[j].v].dist;
                nodes[nodes[i].edges[j].v].edges[nodes[i].edges[j].rev].cost = 0;
            }
        }
    }
}


//Successive Shortest Path with potentials
pair<long long, long long> minCostMaxFlow(long long s, long long t, size_t V, vector<Node> & nodes) {
    //Transform network G by adding source and sink

    //Initial flow x is zero
    long long flow{ 0 };
    long long cost{ 0 };

    //Use Bellman - Ford's algorithm to establish potentials
    //BellmanFord<long long> bf(V, s);
    //bf.solve(nodes);


    //Reduce Cost()
    //reduceCost(nodes);

    //while (Gx contains a path from s to t) do
    BellmanFord bf(nodes.size(), s);

    reduceCost(nodes);

    while (true) {
        //Find any shortest path P from s to t
        bf.solve(nodes);
        long long a{ bf.shortestPath(t, nodes).second };

        if (a <= 0)
            break;

        a = nodes[t].cc;
        //Reduce Cost()
        //reduceCost(nodes);

        //Augment current flow x along P
        pair<long long, long long> prev{ nodes[t].parent };
        long long curr{ t };
        while (curr != s) {
            nodes[prev.first].edges[prev.second].flow += a;
            nodes[curr].edges[nodes[prev.first].edges[prev.second].rev].flow -= a;
            cost += a * nodes[prev.first].edges[prev.second].orgCost;
            curr = prev.first;
            prev = nodes[prev.first].parent;
        }

        //update Gx
        flow += a;
    }
    return { flow, cost };
}


int main() {
    ios::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);

    long long n, m, s, i, j, t, t1, t2, t3, t4;
    //while (true) {
    //input blablabla
    fastScan(n);
    fastScan(m);
    fastScan(s);
    fastScan(t);


    vector<Node> nodes(n);

    ++m;
    while (--m) {
        //input blablabla
        fastScan(t1);
        fastScan(t2);
        fastScan(t3);
        fastScan(t4);
        nodes[t1].edges.emplace_back(t1, t2, t3, nodes[t2].reverse.size(), 0, t4, false);
        nodes[t2].edges.emplace_back(t2, t1, t3, nodes[t1].reverse.size(), t3, -t4, true);
        nodes[t1].reverse.push_back(nodes[t2].edges.size() - 1);
        nodes[t2].reverse.push_back(nodes[t1].edges.size() - 1);
    }


    pair<long long, long long> ans{ minCostMaxFlow(s, t, n, nodes) };
    cout << ans.first << " " << ans.second << "\n";

    system("Pause");
    return 0;
}