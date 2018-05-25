//https://liu.kattis.com/problems/councilling
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
    register T c;

    number = 0;

    // extract current character from buffer
    c = getchar();
    while (!(c == '-' || (c > 47 && c < 58)))
        c = getchar();

    // Keep on extracting characters if they are integers
    // i.e ASCII Value lies from '0'(48) to '9' (57)
    for (; (c > 47 && c < 58); c = getchar())
        number = number * 10 + c - 48;
}

struct Edge {
    Edge(int u, int v, int c, int rev) : u(u), v(v), c(c), rev(rev), flow{ 0 } {}
    int u, v, c, rev;
    long long flow;
};

struct Node {
    vector<Edge> edges;
    vector<int> reverse;
    string name;
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
    }

}


int main() {
    //ios::sync_with_stdio(false);
    //cout.tie(nullptr);
    //cin.tie(nullptr);

    int n, m, s, i, j, k, maxx;
    string tmp;
    fastScan(n);

    ++n;
    while (--n) {
        fastScan(m);
        vector<Node> nodes(m + 2);

        map<string, int> party;
        map<string, int> club;

        maxx = (m - 1) / 2;

        for (i = 0; i < m; ++i) {
            cin >> tmp;
            nodes[i].name = tmp;
            cin >> tmp;
            auto it{ party.insert({ tmp, nodes.size() }) };

            if (it.second) {
                nodes.emplace_back();
                nodes.back().name = tmp;
                nodes[m].edges.emplace_back(m, it.first->second, maxx, nodes[it.first->second].reverse.size());
                nodes[it.first->second].edges.emplace_back(it.first->second, m, 0, nodes[m].reverse.size());

                nodes[it.first->second].reverse.push_back(nodes[m].edges.size() - 1);
                nodes[m].reverse.push_back(nodes[it.first->second].edges.size() - 1);
            }

            nodes[it.first->second].edges.emplace_back(it.first->second, i, 1, nodes[i].reverse.size());
            nodes[i].edges.emplace_back(i, it.first->second, 0, nodes[it.first->second].reverse.size());

            nodes[i].reverse.push_back(nodes[it.first->second].edges.size() - 1);
            nodes[it.first->second].reverse.push_back(nodes[i].edges.size() - 1);

            cin >> k;
            for (j = 0; j < k; ++j) {
                cin >> tmp;
                auto it{ club.insert({ tmp, nodes.size() }) };
                if (it.second) {
                    nodes.emplace_back();
                    nodes.back().name = tmp;
                    nodes[it.first->second].edges.emplace_back(it.first->second, m + 1, 1, nodes[m + 1].reverse.size());
                    nodes[m + 1].edges.emplace_back(m + 1, it.first->second, 0, nodes[it.first->second].reverse.size());

                    nodes[m + 1].reverse.push_back(nodes[it.first->second].edges.size() - 1);
                    nodes[it.first->second].reverse.push_back(nodes[m + 1].edges.size() - 1);
                }

                nodes[i].edges.emplace_back(i, it.first->second, 1, nodes[it.first->second].reverse.size());
                nodes[it.first->second].edges.emplace_back(it.first->second, i, 0, nodes[i].reverse.size());

                nodes[it.first->second].reverse.push_back(nodes[i].edges.size() - 1);
                nodes[i].reverse.push_back(nodes[it.first->second].edges.size() - 1);
            }
        }

        long long a{ maxFlowDinics(m, m + 1, nodes.size(), nodes) };

        if (a < club.size())
            printf("Impossible.\n");

        else {
            for (i = 0; i < m; ++i) {
                for (j = 0; j < nodes[i].edges.size(); ++j) {
                    if (nodes[i].edges[j].flow > 0) {
                        printf("%s %s\n", nodes[i].name.c_str(), nodes[nodes[i].edges[j].v].name.c_str());
                        break;
                    }
                }
            }
        }
    }
    return 0;
}