//https://liu.kattis.com/sessions/zbhcac/problems/escapeplan
//Leif Eriksson
//With Teo Tiefenbacher and Olav Övrebö
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


int main() {
    ios::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);

    int n, m, s, i, j, t;
    long double t1, t2, t3;
    long double x, y;
    vector<int> a{ 5,10,20 };
    s = 0;
    while (true) {
        ++s;
        //input blablabla
        fastScan(n);
        if (n == 0)
            return 0;

        vector<pair<long double, long double>> r(n);

        for (i = 0; i < n; ++i) {
            fastScan(t1);
            fastScan(t2);
            r[i] = { t1, t2 };
        }

        fastScan(m);
        vector<pair<long double, long double>> h(m);

        for (i = 0; i < m; ++i) {
            fastScan(t1);
            fastScan(t2);
            h[i] = { t1, t2 };
        }

        printf("Scenario %d\n", s);
        for (int t : a) {
            vector<Node> nodes(n + m + 2);


            for (j = 0; j < n; ++j) {
                nodes[j].edges.emplace_back(j, m + n, 0, nodes[m + n].reverse.size());
                nodes[m + n].edges.emplace_back(m + n, j, 1, nodes[j].reverse.size());
                nodes[j].reverse.push_back(nodes[m + n].edges.size() - 1);
                nodes[m + n].reverse.push_back(nodes[j].edges.size() - 1);
            }
            for (i = 0; i < m; ++i) {
                nodes[n + i].edges.emplace_back(n + i, m + n + 1, 1, nodes[m + n + 1].reverse.size());
                nodes[m + n + 1].edges.emplace_back(m + n + 1, n + i, 0, nodes[n + i].reverse.size());
                nodes[n + i].reverse.push_back(nodes[m + n + 1].edges.size() - 1);
                nodes[m + n + 1].reverse.push_back(nodes[n + i].edges.size() - 1);

                for (j = 0; j < n; ++j) {

                    x = h[i].first - r[j].first;
                    y = h[i].second - r[j].second;
                    if (x*x + y*y <= t*t * 10 * 10) {
                        nodes[j].edges.emplace_back(j, n + i, 1, nodes[n + i].reverse.size());
                        nodes[n + i].edges.emplace_back(n + i, j, 0, nodes[j].reverse.size());
                        nodes[j].reverse.push_back(nodes[n + i].edges.size() - 1);
                        nodes[n + i].reverse.push_back(nodes[j].edges.size() - 1);
                    }
                }
            }

            long long mflow(maxFlowDinics(m + n, m + n + 1, m + n + 2, nodes));
            printf("In %d seconds %d robot(s) can escape\n", t, mflow);

        }


    }

    return 0;
}

/*
3
0.0 0.0
10.0 0.0
0.0 10.0
3
99.0 0.0
0.0 1000.0
1000.0 1000.0
3
0.0 0.0
100.0 0.0
200.0 0.0
2
95.0 50.0
105.0 50.0
0
*/

