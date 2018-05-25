//https://liu.kattis.com/problems/risk
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
#include <complex>
#include <bits/stdc++.h>

using namespace std;

//https://www.geeksforgeeks.org/fast-io-for-competitive-programming/
template<typename T>
void fastScan(T &number) {
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

struct Edge {
    Edge(int u, int v, int c, int rev) : u(u), v(v), c(c), rev(rev), flow{ 0 } {}
    int u, v, c, rev;
    long long flow;
};

struct Node {
    int start;
    bool bad{ false };
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
    vector<int> level(V);
    vector<int> v(V);
    while (true) {
        fill(level.begin(), level.end(), -1);
        //BFS
        level[s] = 0;  // Level of source vertex
        queue<int> q; //Sadly no good way to clear an queue without creating a new queue
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
        fill(v.begin(), v.end(), 0);
        flow = send(s, std::numeric_limits<long long>::max(), t, nodes, v, level);
        while (flow) {
            totalFlow += flow;
            flow = send(s, std::numeric_limits<long long>::max(), t, nodes, v, level);
        }
    }
}


int main() {
    ios::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);

    int N, n, i, i3, j, j3, t1, source, sinc, low, high, minFound, curr;
    int oldCurr;
    char c;
    vector<Node> nodes;
    vector<pair<int, int>> markedEdges;
    fastScan(N);
    ++N;
    while (--N) {
        fastScan(n);
        source = n * 3;
        sinc = source + 1;
        nodes.resize(sinc + 1);
        fill(nodes.begin(), nodes.end(), Node());
        markedEdges.clear();

        for (i = 0, i3 = 0; i < n; ++i, i3 += 3) {
            fastScan(t1);
            nodes[i3].start = t1;
            if (t1 > 0) {
                nodes[i3 + 1].edges.emplace_back(i3 + 1, i3, 1, nodes[i3].reverse.size());
                nodes[i3].edges.emplace_back(i3, i3 + 1, 0, nodes[i3 + 1].reverse.size());
                nodes[i3 + 1].reverse.push_back(nodes[i3].edges.size() - 1);
                nodes[i3].reverse.push_back(nodes[i3 + 1].edges.size() - 1);

                if (t1 > 1) {
                    nodes[source].edges.emplace_back(source, i3, t1 - 1, nodes[i3].reverse.size());
                    nodes[i3].edges.emplace_back(i3, source, 0, nodes[source].reverse.size());
                    nodes[source].reverse.push_back(nodes[i3].edges.size() - 1);
                    nodes[i3].reverse.push_back(nodes[source].edges.size() - 1);
                }
            }
        }

        for (i = 0, i3 = 0; i < n; ++i, i3 += 3) {
            for (j = 0, j3 = 0; j < n; ++j, j3 += 3) {
                c = getchar_unlocked();
                while (c != 'N' && c != 'Y') c = getchar_unlocked();

                if (c == 'Y') {
                    if (nodes[i3].start) {
                        if (nodes[j3].start == 0) {
                            if (!nodes[i3].bad) {
                                nodes[i3].edges.emplace_back(i3, i3 + 2, 10000, nodes[i3 + 2].reverse.size());
                                nodes[i3 + 2].edges.emplace_back(i3 + 2, i3, 0, nodes[i3].reverse.size());
                                nodes[i3 + 2].reverse.push_back(nodes[i3].edges.size() - 1);
                                nodes[i3].reverse.push_back(nodes[i3 + 2].edges.size() - 1);

                                nodes[i3 + 1].edges.emplace_back(i3 + 1, i3 + 2, 10000, nodes[i3 + 2].reverse.size());
                                nodes[i3 + 2].edges.emplace_back(i3 + 2, i3 + 1, 0, nodes[i3 + 1].reverse.size());
                                nodes[i3 + 2].reverse.push_back(nodes[i3 + 1].edges.size() - 1);
                                nodes[i3 + 1].reverse.push_back(nodes[i3 + 2].edges.size() - 1);

                                nodes[i3 + 2].edges.emplace_back(i3 + 2, sinc, 1, nodes[sinc].reverse.size());
                                nodes[sinc].edges.emplace_back(sinc, i3 + 2, 0, nodes[i3 + 2].reverse.size());
                                nodes[i3 + 2].reverse.push_back(nodes[sinc].edges.size() - 1);
                                nodes[sinc].reverse.push_back(nodes[i3 + 2].edges.size() - 1);

                                markedEdges.push_back({ i3 + 2, nodes[i3 + 2].edges.size() - 1 });

                            }
                            nodes[i3].bad = true;
                        }
                        else {
                            nodes[i3].edges.emplace_back(i3, j3 + 1, nodes[i3].start, nodes[j3 + 1].reverse.size());
                            nodes[j3 + 1].edges.emplace_back(j3 + 1, i3, 0, nodes[i3].reverse.size());
                            nodes[j3 + 1].reverse.push_back(nodes[i3].edges.size() - 1);
                            nodes[i3].reverse.push_back(nodes[j3 + 1].edges.size() - 1);
                        }
                    }
                }
            }
        }

        curr = 1;
        for (i = 0; i < markedEdges.size(); ++i)
            nodes[markedEdges[i].first].edges[markedEdges[i].second].c = curr;

        for (Node & node : nodes)
            for (Edge & edge : node.edges) {
                edge.flow = 0;
            }
        while (maxFlowDinics(source, sinc, sinc + 1, nodes) == markedEdges.size() * curr) {
            curr *= 2;
            for (i = 0; i < markedEdges.size(); ++i)
                nodes[markedEdges[i].first].edges[markedEdges[i].second].c = curr;

            for (Node & node : nodes)
                for (Edge & edge : node.edges) {
                    edge.flow = 0;
                }
        }

        low = curr / 2;
        high = curr - 1;
        curr = low + (high - low + 1) / 2;
        while (low != high) {
            for (i = 0; i < markedEdges.size(); ++i)
                nodes[markedEdges[i].first].edges[markedEdges[i].second].c = curr;

            for (Node & node : nodes)
                for (Edge & edge : node.edges) {
                    edge.flow = 0;
                }

            if (maxFlowDinics(source, sinc, sinc + 1, nodes) == markedEdges.size() * curr) {
                low = curr;
            }
            else {
                high = curr - 1;
            }
            curr = low + (high - low + 1) / 2;
        }

        printf("%d\n", curr + 1);
    }
    system("Pause");
    return 0;
}



/*

2
3
1 1 0
NYN
YNY
NYN
7
7 3 3 2 0 0 5
NYNNNNN
YNYYNNN
NYNYYNN
NYYNYNN
NNYYNNN
NNNNNNY
NNNNNYN


*/