//https://liu.kattis.com/problems/maxflow
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

#define _UNLOCKED 0
#if _UNLOCKED
#define gc() getchar_unlocked()
#else
#define gc() getchar()
#endif

//https://www.geeksforgeeks.org/fast-io-for-competitive-programming/
template<typename T>
void fastScan(T &number) {
	//variable to indicate sign of input number
	bool negative{ false };
	register T c;

	number = 0;

	// extract current character from buffer
	c = gc();
	while (!(c == '-' || (c > 47 && c < 58)))
		c = gc();

	if (c == '-') {
		// number is negative
		negative = true;

		// extract the next character from the buffer
		c = gc();
	}

	// Keep on extracting characters if they are integers
	// i.e ASCII Value lies from '0'(48) to '9' (57)
	for (; (c > 47 && c < 58); c = gc())
		number = number * 10 + c - 48;

	// if scanned input has a negative sign, negate the
	// value of the input number
	if (negative)
		number *= -1;
}

class MaxFlowDinics_Map {
    //Version with better handeling of multiple edges between u and v
    //Simply merges them
    //(Adds a O(log(E)) cost to adding edges)
public:

    MaxFlowDinics_Map(size_t _V) : _V(_V), _nodes(_V) {}

    void add(int from, int to, int capacity) {
        auto it(_nodes[from].edgeMap.insert({to, _nodes[from].edges.size() }));
        if (it.second) {
            _nodes[from].edges.emplace_back(from, to, capacity, _nodes[to].edges.size());
            _nodes[to].edges.emplace_back(to, from, 0, _nodes[from].edges.size() - 1);
        }
        else 
            _nodes[from].edges[it.first->first].c += capacity;
    }

    void reset() {
        for (size_t i{ 0 }, u, size; i < _V; ++i) {
            size = _nodes[i].edges.size();
            for (u = 0; u < size; ++u)
                _nodes[i].edges[u].flow = 0;
        }
    }

    //nput: A network{ \displaystyle G = ((V,E),c,s,t) } G = ((V, E), c, s, t).
    //Output : An{ \displaystyle s - t } s - t flow{ \displaystyle f } f of maximum value.
    long long solve(int s, int t) {
        //Set f(e) = 0 for each e in E.
        //Construct G_L from G_f of G. If dist(t) = infty stop and output f.
        int u, size, i, totalFlow{ 0 }, flow;
        vector<size_t> v(_V);
        vector<int> level(_V);
        queue<int> q;
        while (true) {
            fill(level.begin(), level.end(), -1);
            //BFS
            level[s] = 0;  // Level of source vertex
            q.push(s);
            while (!q.empty()) {
                u = q.front(), q.pop();
                size = _nodes[u].edges.size();
                for (i = 0; i < size; ++i) {
                    Edge &e(_nodes[u].edges[i]);
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
            flow = send(s, std::numeric_limits<long long>::max(), t, v, level);
            while (flow) {
                totalFlow += flow;
                flow = send(s, std::numeric_limits<long long>::max(), t, v, level);
            }
        }
    }


    void findMinCut(set<int> & minCut, int s) {
        int size(_nodes[s].edges.size());

        for (int i{ 0 }; i < size; ++i) {
            Edge* e{ &_nodes[s].edges[i] };
            if (e->c > e->flow) {
                if (minCut.insert(e->v).second) {
                    findMinCut(minCut, e->v);
                }
            }
        }
    }

    //private:
    struct Edge {
        Edge(int u, int v, int c, int rev) : u(u), v(v), c(c), rev(rev), flow{ 0 } {}
        int u, v, c, rev;
        long long flow;
    };

    struct Node {
        vector<Edge> edges;
        map<int,int> edgeMap;
        vector<Edge*> reverse;
    };

    //Dinic's Algorithm
    long long send(int u, long long flow, int t, vector<size_t> & currEdge, vector<int> & level) {
        if (u == t)
            return flow;
        Node* n{ &_nodes[u] };
        vector<Edge>* nue{ &n->edges };
        size_t size(nue->size());
        long long currFlow, tmpFlow, currCurrEdge;
        Edge *e;
        if (!n->reverse.size()) {
            for (size_t i{ 0 }; i < size; ++i) {
                e = &nue->at(i);
                n->reverse.push_back(&_nodes[e->v].edges[e->rev]);
            }
        }

        for (; currEdge[u] < size; ++currEdge[u]) {
            e = &nue->at(currEdge[u]);
            if (level[e->v] == level[u] + 1 && e->flow < e->c) {
                currFlow = min(flow, e->c - e->flow);
                currCurrEdge = currEdge[u];
                tmpFlow = send(e->v, currFlow, t, currEdge, level);

                if (tmpFlow) {
                    e->flow += tmpFlow;
                    n->reverse[currCurrEdge]->flow -= tmpFlow;
                    return tmpFlow;
                }
            }
        }
        return 0;
    }

    size_t _V;
    vector<Node> _nodes;
};

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


    MaxFlowDinics_Map maxFlow(n);

    ++m;
    while (--m) {
        //input blablabla
        fastScan(t1);
        fastScan(t2);
        fastScan(t3);
        maxFlow.add(t1, t2, t3);
    }

    long long mflow(maxFlow.solve(s, t));

    vector<int> a;

    for (i = 0; i < maxFlow._nodes.size(); ++i) {
        for (j = 0; j < maxFlow._nodes[i].edges.size(); ++j) {
            if (maxFlow._nodes[i].edges[j].c > 0 && maxFlow._nodes[i].edges[j].flow > 0) {
                a.push_back(maxFlow._nodes[i].edges[j].u);
                a.push_back(maxFlow._nodes[i].edges[j].v);
                a.push_back(maxFlow._nodes[i].edges[j].flow);
            }
        }
    }

    printf("%d %lld %zu\n", n, mflow, a.size() / 3);

    for (i = 0; i < a.size(); i += 3)
        printf("%d %d %d\n", a[i], a[i + 1], a[i + 2]);

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