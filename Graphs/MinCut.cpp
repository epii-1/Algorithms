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
	for (; (c>47 && c<58); c = gc())
		number = number * 10 + c - 48;

	// if scanned input has a negative sign, negate the
	// value of the input number
	if (negative)
		number *= -1;
}

template <typename C = int, typename T>
class MaxFlowDinics {
public:

    MaxFlowDinics(size_t _V) : _V(_V), _nodes(_V) {}

    void add(T from, T to, C capacity) {
        _nodes[from].edges.emplace_back(from, to, capacity, _nodes[to].edges.size());
        _nodes[to].edges.emplace_back(to, from, 0, _nodes[from].edges.size() - 1);
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
    C solve(T s, T t) {
        //Set f(e) = 0 for each e in E.
        //Construct G_L from G_f of G. If dist(t) = infty stop and output f.
		T u, size, i;
		C totalFlow{ 0 }, flow;
        vector<size_t> v(_V);
        vector<T> level(_V);
        queue<T> q;
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
            flow = send(s, std::numeric_limits<C>::max(), t, v, level);
            while (flow) {
                totalFlow += flow;
                flow = send(s, std::numeric_limits<C>::max(), t, v, level);
            }
        }
    }

    void findMinCut(set<T> & minCut, T s) {
        T size(_nodes[s].edges.size());

        for (T i{ 0 }; i < size; ++i) {
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
        Edge(T u, T v, C c, T rev) : u(u), v(v), c(c), rev(rev), flow{ 0 } {}
        T u, v, rev;
        C flow, c;
    };

    struct Node {
        vector<Edge> edges;
        vector<Edge*> reverse;
    };

    //Dinic's Algorithm
    C send(T u, C flow, T t, vector<size_t> & currEdge, vector<T> & level) {
        if (u == t)
            return flow;
        Node* n{ &_nodes[u] };
        vector<Edge>* nue{ &n->edges };
        size_t size(nue->size());
		C currFlow, tmpFlow;
		T currCurrEdge;
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

    MaxFlowDinics maxFlow(n);

    ++m;
    while (--m) {
        //input blablabla
        fastScan(t1);
        fastScan(t2);
        fastScan(t3);
        maxFlow.add(t1, t2, t3);
    }

    maxFlow.solve(s, t)

    set<int> minCut;
    minCut.insert(s);

    maxFlow.findMinCut(minCut, s);

    cout << minCut.size() << "\n";
    copy(minCut.begin(), minCut.end(), std::ostream_iterator<int>(cout, "\n"));

    return 0;
}