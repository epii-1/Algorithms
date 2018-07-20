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
#include <cstring>

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

template<typename T>
void fastFill(T* v, const T& x, size_t n) {
	if (n == 0)
		return;
	size_t s(1);
	*v = x;
	while (s + s <= n) {
		memcpy((v + s), v, s * sizeof(x));
		s += s;
	}
	memcpy((v + s), v, (n - s) * sizeof(x));
}

template<typename C = int, typename T = int>
class MaxFlowDinics {
	//Basic version
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
			fastFill(&level[0], -1, _V);
			//BFS
			level[s] = 0;  // Level of source vertex
			q.push(s);
			while (!q.empty()) {
				u = q.front(), q.pop();
				size = _nodes[u].edges.size();
				for (i = 0; i < size; ++i) {
					_Edge &e(_nodes[u].edges[i]);
					if (level[e.v] == -1 && e.flow < e.c) {
						level[e.v] = level[u] + 1;
						q.push(e.v);
					}
				}
			}
			if (level[t] == -1)
				return totalFlow;

			fastFill(&v[0], size_t(0), _V);
			//Find a blocking flow f' in G_L.
			flow = send(s, std::numeric_limits<long long>::max(), t, v, level);
			while (flow) {
				totalFlow += flow;
				flow = send(s, std::numeric_limits<long long>::max(), t, v, level);
			}
		}
	}


	void findMinCut(set<T> & minCut, T s) {
		T size(_nodes[s].edges.size());

		for (T i{ 0 }; i < size; ++i) {
			_Edge* e{ &_nodes[s].edges[i] };
			if (e->c > e->flow) {
				if (minCut.insert(e->v).second) {
					findMinCut(minCut, e->v);
				}
			}
		}
	}

	//private:
	struct _Edge {
		_Edge(T u, T v, C c, T rev) : u(u), v(v), c(c), rev(rev), flow{ 0 } {}
		T u, v, rev;
		C c;
		C flow;
	};

	struct _Node {
		vector<_Edge> edges;
		vector<_Edge*> reverse;
	};

	//Dinic's Algorithm
	C send(T u, C flow, T t, vector<size_t> & currEdge, vector<T> & level) {
		if (u == t)
			return flow;
		_Node* n{ &_nodes[u] };
		vector<_Edge>* nue{ &n->edges };
		size_t size(nue->size());
		C currFlow, tmpFlow;
		T currCurrEdge;
		_Edge *e;
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
	vector<_Node> _nodes;
};

int main() {
	ios::sync_with_stdio(false);
	cout.tie(nullptr);
	cin.tie(nullptr);

	int n, m, s, i, j, t, t1, t2;
	long long t3;

	//input blablabla
	fastScan(n);
	fastScan(m);
	fastScan(s);
	fastScan(t);


	MaxFlowDinics<long long, int> maxFlow(n);

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
			if (maxFlow._nodes[i].edges[j].flow > 0) {
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