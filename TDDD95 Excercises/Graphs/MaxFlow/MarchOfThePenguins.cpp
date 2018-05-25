//https://liu.kattis.com/sessions/errnrk/problems/marchofpenguins
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
    for (; (c > 47 && c < 58); c = getchar_unlocked())
        number = number * 10 + c - 48;

    if (c == '.') {
        c = getchar_unlocked();
        long double pot{ 0.1 };
        for (; (c > 47 && c < 58); c = getchar_unlocked(), pot *= 0.1)
            number += (c - 48)*pot;
    }

    // if scanned input has a negative sign, negate the
    // value of the input number
    if (negative)
        number *= -1;
}

struct Edge {
    Edge(int v, int u, int c, int rev) : u(u), v(v), c(c), rev(rev), flow{ 0 } {}
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
    int u, size, i{ 0 };
    long long flow, totalFlow{ 0 };

    for (; i < V; ++i) {
        size = nodes[i].edges.size();
        for (u = 0; u < size; ++u) {
            nodes[i].edges[u].flow = 0;
        }
    }

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
    ios::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);

    int n, m, s, i, i2, j, j2, t, t1, t2, ping{ 0 };
    double d, x, y;

    //input blablabla
    fastScan(n);
    fastScan(d);

    d *= d;

    vector<Node> nodes(2 * n + 1);

    vector<pair<double, double>> v(n);
    s = n * 2;
    for (i = 0, i2 = 0; i < n; ++i, i2 += 2) {
        //input blablabla
        fastScan(x);
        fastScan(y);
        fastScan(t1);
        fastScan(t2);

        ping += t1;

        v[i] = { x, y };

        nodes[i2].edges.emplace_back(i2 + 1, i2, t2, nodes[i2 + 1].reverse.size());
        nodes[i2 + 1].edges.emplace_back(i2, i2 + 1, 0, nodes[i2].reverse.size());
        nodes[i2].reverse.push_back(nodes[i2 + 1].edges.size() - 1);
        nodes[i2 + 1].reverse.push_back(nodes[i2].edges.size() - 1);

        if (t1 > 0) {
            nodes[s].edges.emplace_back(i2, s, t1, nodes[i2].reverse.size());
            nodes[i2].edges.emplace_back(s, i2, 0, nodes[s].reverse.size());
            nodes[i2].reverse.push_back(nodes[s].edges.size() - 1);
            nodes[s].reverse.push_back(nodes[i2].edges.size() - 1);
        }
    }

    for (i = 0, i2 = 0; i < n; ++i, i2 += 2) {
        for (j = i + 1, j2 = i2 + 2; j < n; ++j, j2 += 2) {
            x = v[i].first - v[j].first;
            y = v[i].second - v[j].second;

            if (x*x + y*y <= d) {
                nodes[j2 + 1].edges.emplace_back(i2, j2 + 1, ping, nodes[i2].reverse.size());
                nodes[i2].edges.emplace_back(j2 + 1, i2, 0, nodes[j2 + 1].reverse.size());
                nodes[i2].reverse.push_back(nodes[j2 + 1].edges.size() - 1);
                nodes[j2 + 1].reverse.push_back(nodes[i2].edges.size() - 1);

                nodes[j2].edges.emplace_back(i2 + 1, j2, 0, nodes[i2 + 1].reverse.size());
                nodes[i2 + 1].edges.emplace_back(j2, i2 + 1, ping, nodes[j2].reverse.size());
                nodes[i2 + 1].reverse.push_back(nodes[j2].edges.size() - 1);
                nodes[j2].reverse.push_back(nodes[i2 + 1].edges.size() - 1);
            }
        }
    }

    vector<int> a;

    for (i = 0; i < n; ++i) {
        if (maxFlowDinics(s, i * 2, n * 2 + 1, nodes) == ping)
            a.push_back(i);
    }

    if (a.size()) {
        copy(a.begin(), a.end(), std::ostream_iterator<int>(cout, " "));
        printf("\n");
    }
    else
        printf("-1\n");

    return 0;
}
