//https://liu.kattis.com/problems/unfairplay
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
#include <complex>
//#include <bits/stdc++.h>

using namespace std;

//https://www.geeksforgeeks.org/fast-io-for-competitive-programming/
template<typename T>
bool fastScan(T &number) {
    register T c;

    number = 0;

    // extract current character from buffer
    c = getchar();
    while (!(c > 47 && c < 58 || c == '-'))
        c = getchar();

    if (c == '-')
        return false;

    // Keep on extracting characters if they are integers
    // i.e ASCII Value lies from '0'(48) to '9' (57)
    for (; (c > 47 && c < 58); c = getchar())
        number = number * 10 + c - 48;
    return true;
}

struct Edge {
    Edge(int u, int v, int c, int rev) : u(u), v(v), c(c), rev(rev), flow{ 0 } {}
    int u, v, c, rev;
    long long flow;
};

struct Node {
    vector<Edge> edges;
    vector<int> reverse;
    int c = 1;
};

//Dinic's Algorithm
long long send(int u, long long flow, int t, vector<Node> & nodes, vector<int> & currEdge, vector<int> & level) {
    if (u == t)
        return flow;
    int size(nodes[u].edges.size());
    long long currFlow, tmpFlow, currCurrEdge;
    Edge *e;
    for (; currEdge[u] < size; ++currEdge[u]) {
        e = &nodes[u].edges[currEdge[u]];
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
    vector<int> v(V);
    vector<int> level(V);
    while (true) {
        fill(level.begin(), level.end(), -1);
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

        fill(v.begin(), v.end(), 0);
        //Find a blocking flow f' in G_L.
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

    int n, m, s, i, j, t, t1, t2, t3;
    long long sum, sum2;
    while (true) {
        //input blablabla
        if (!fastScan(n))
            break;
        fastScan(m);


        vector<Node> nodes(n + 2 + m);
        sum = 0;
        sum2 = m * 2;

        for (i = 0; i < n; ++i) {
            fastScan(t1);

            nodes[i].edges.emplace_back(i, n, 0, nodes[n].reverse.size());
            nodes[n].edges.emplace_back(n, i, t1, nodes[i].reverse.size());
            nodes[i].reverse.push_back(nodes[n].edges.size() - 1);
            nodes[n].reverse.push_back(nodes[i].edges.size() - 1);

            sum = t1 - 1;

            sum2 += t1;
        }
        for (i = 0; i < m; ++i) {
            fastScan(t1);
            fastScan(t2);
            if (t1 != n && t2 != n) {

                --t1;
                --t2;

                nodes[i + n + 2].edges.emplace_back(i + n + 2, n, 0, nodes[n].reverse.size());
                nodes[n].edges.emplace_back(n, i + n + 2, 2, nodes[i + n + 2].reverse.size());
                nodes[i + n + 2].reverse.push_back(nodes[n].edges.size() - 1);
                nodes[n].reverse.push_back(nodes[i + n + 2].edges.size() - 1);

                nodes[i + n + 2].edges.emplace_back(i + n + 2, t1, 2, nodes[t1].reverse.size());
                nodes[t1].edges.emplace_back(t1, i + n + 2, 0, nodes[i + n + 2].reverse.size());
                nodes[i + n + 2].reverse.push_back(nodes[t1].edges.size() - 1);
                nodes[t1].reverse.push_back(nodes[i + n + 2].edges.size() - 1);

                nodes[i + n + 2].edges.emplace_back(i + n + 2, t2, 2, nodes[t2].reverse.size());
                nodes[t2].edges.emplace_back(t2, i + n + 2, 0, nodes[i + n + 2].reverse.size());
                nodes[i + n + 2].reverse.push_back(nodes[t2].edges.size() - 1);
                nodes[t2].reverse.push_back(nodes[i + n + 2].edges.size() - 1);
            }
            else {
                sum += 2;
                nodes[n].edges[n - 1].c += 2;
                nodes[i + n + 2].c = t1 == n ? 0 : 2;
            }
        }


        for (i = 0; i < n - 1; ++i) {

            nodes[i].edges.emplace_back(i, n + 1, sum, nodes[n + 1].reverse.size());
            nodes[n + 1].edges.emplace_back(n + 1, i, 0, nodes[i].reverse.size());
            nodes[i].reverse.push_back(nodes[n + 1].edges.size() - 1);
            nodes[n + 1].reverse.push_back(nodes[i].edges.size() - 1);

        }

        nodes[n - 1].edges.emplace_back(n - 1, n + 1, sum + 1, nodes[n + 1].reverse.size());
        nodes[n + 1].edges.emplace_back(n + 1, n - 1, 0, nodes[i].reverse.size());
        nodes[n - 1].reverse.push_back(nodes[n + 1].edges.size() - 1);
        nodes[n + 1].reverse.push_back(nodes[n - 1].edges.size() - 1);

        if (sum >= 0) {
            long long mflow(maxFlowDinics(n, n + 1, n + 2 + m, nodes));
            //printf("%lld %lld\n", mflow, sum2);
            if (mflow == sum2) {
                for (i = 0; i < m; ++i) {
                    if (nodes[i + n + 2].c == 1)
                        printf("%lld ", nodes[i + n + 2].edges[2].flow);
                    else
                        printf("%d ", nodes[i + n + 2].c);
                }
                printf("\n");


                //for (i = 0; i < n; ++i) {
                //   printf("%d ", nodes[i].edges.back().flow);
                //}
                //printf("\n");
            }
            else
                printf("NO\n");
        }
        else
            printf("NO\n");
    }

    return 0;
}

/*
4 5 0 3
0 1 10
1 2 1
1 3 1
0 2 1
2 3 10
*/

