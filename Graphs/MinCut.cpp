//https://liu.kattis.com/problems/mincut
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
//#include <bits/stdc++.h>

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
    c = getchar();
    while (!(c == '-' || (c > 47 && c < 58)))
        c = getchar();

    if (c == '-')
    {
        // number is negative
        negative = true;

        // extract the next character from the buffer
        c = getchar();
    }

    // Keep on extracting characters if they are integers
    // i.e ASCII Value lies from '0'(48) to '9' (57)
    for (; (c > 47 && c < 58); c = getchar())
        number = number * 10 + c - 48;

    // if scanned input has a negative sign, negate the
    // value of the input number
    if (negative)
        number *= -1;
}

struct Edge {
    Edge(int u, int v, int c, int rev) : u(u), v(v), c(c), rev(rev), flow{ 0 } {}
    int u, v, c, rev;
    long long flow;
};

struct Node {
    vector<Edge> edges;
    vector<int> reverse;
};

//Dinic's Algorithm

long long send(int u, long long flow, int t, vector<Node> & nodes, vector<int> & currEdge, vector<int> & level) {
    if (u == t)
        return flow;
    int size(nodes[u].edges.size());
    long long currFlow, tmpFlow, currCurrEdge;
    for (; currEdge[u] < size; ++currEdge[u]) {
        Edge *e{ &nodes[u].edges[currEdge[u]] };
        if (level[e->v] == level[u] + 1 && e->flow < e->c) {
            currFlow = min(flow, e->c - e->flow);
            currCurrEdge = currEdge[u];
            tmpFlow = send(e->v, currFlow, t, nodes, currEdge, level);
            if (tmpFlow > 0) {
                e->flow += tmpFlow;
                nodes[e->v].edges[nodes[u].reverse[currCurrEdge]].flow -= tmpFlow;
                return tmpFlow;
            }
        }
    }
    return 0;
}

//nput: A network{ \displaystyle G = ((V,E),c,s,t) } G = ((V, E), c, s, t).
//Output : An{ \displaystyle s - t } s - t flow{ \displaystyle f } f of maximum value.
long long maxFlowDinics(int s, int t, size_t V, vector<Node> & nodes) {
    //Set f(e) = 0 for each e in E.
    //Construct G_L from G_f of G. If dist(t) = infty stop and output f.
    int u, size, i, totalFlow{ 0 }, flow;
    while (true) {
        vector<int> level(V, -1);
        //BFS
        level[s] = 0;  // Level of source vertex
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            u = q.front(), q.pop();
            size = nodes[u].edges.size();
            for (i = 0; i < size; ++i) {
                Edge &e(nodes[u].edges[i]);
                if (level[e.v] == -1 && e.flow < e.c) {
                    level[e.v] = level[u] + 1;
                    q.push(e.v);
                }
            }
        }
        if (level[t] == -1)
            return totalFlow;

        //Find a blocking flow f' in G_L.
        vector<int> v(V, 0);
        flow = send(s, std::numeric_limits<long long>::max(), t, nodes, v, level);
        while (flow) {
            totalFlow += flow;
            flow = send(s, std::numeric_limits<long long>::max(), t, nodes, v, level);
        }
        //system("Pause");
    }

}

void findMinCut(vector<Node> & nodes, set<int> & minCut, int s) {
    int size(nodes[s].edges.size());

    for (int i{ 0 }; i < size; ++i) {
        Edge* e{ &nodes[s].edges[i] };
        if (e->c > e->flow) {
            if (minCut.insert(e->v).second) {
                findMinCut(nodes, minCut, e->v);
            }
        }
    }
}


int main() {
    ios::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);

    int n, m, s, i, j, t, t1, t2, t3;
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
        nodes[t1].edges.emplace_back(t1, t2, t3, nodes[t1].reverse.size());
        nodes[t2].edges.emplace_back(t2, t1, 0, nodes[t1].reverse.size());
        nodes[t1].reverse.push_back(nodes[t2].edges.size() - 1);
        nodes[t2].reverse.push_back(nodes[t1].edges.size() - 1);
    }

    maxFlowDinics(s, t, n, nodes);

    set<int> minCut;
    minCut.insert(s);

    findMinCut(nodes, minCut, s);

    cout << minCut.size() << "\n";
    copy(minCut.begin(), minCut.end(), std::ostream_iterator<int>(cout, "\n"));


    return 0;
}