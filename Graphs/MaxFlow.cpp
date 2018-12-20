//Leif Eriksson

#include <vector>
#include <queue>
#include <map>
#include "TakenImplementations\fastFill.cpp"

template<typename C = int, typename T = int>
class MaxFlowDinics {
	//Basic version
public:

	MaxFlowDinics(T _V) : _V(_V), _nodes(_V) {}

	void add(T from, T to, C capacity) {
		_nodes[from].edges.emplace_back(from, to, capacity, _nodes[to].edges.size());
		_nodes[to].edges.emplace_back(to, from, 0, _nodes[from].edges.size() - 1);
	}

	void reset() {
		for (auto &n : _nodes)
			for (auto &e : n.edges)
				e.flow = 0;
		//for (T i{ 0 }, u, size; i < _V; ++i) {
		//	size = _nodes[i].edges.size();
		//	for (u = 0; u < size; ++u)
		//		_nodes[i].edges[u].flow = 0;
		//}
	}

	//nput: A network{ \displaystyle G = ((V,E),c,s,t) } G = ((V, E), c, s, t).
	//Output : An{ \displaystyle s - t } s - t flow{ \displaystyle f } f of maximum value.
	C solve(T s, T t) {
		//Set f(e) = 0 for each e in E.
		//Construct G_L from G_f of G. If dist(t) = infty stop and output f.
		T u, size, i;
		C totalFlow{ 0 }, flow;
		std::vector<T> v(_V);
		std::vector<T> level(_V);
		std::queue<T> q;
		T _level;
		while (true) {
			fastFill(&level[0], -1, _V);
			//BFS
			level[s] = 0;  // Level of source vertex
			q.push(s);
			while (!q.empty()) {
				u = q.front(), q.pop();
				_level = level[u] + 1;
				for (auto &e : _nodes[u].edges) {
					//size = _nodes[u].edges.size();
					//for (i = 0; i < size; ++i) {
					//_Edge &e(_nodes[u].edges[i]);
					if (level[e.v] == -1 && e.flow < e.c) {
						level[e.v] = _level;
						q.push(e.v);
					}
				}
			}
			if (level[t] == -1)
				return totalFlow;

			fastFill(&v[0], T(0), _V);
			//Find a blocking flow f' in G_L.
			flow = send(s, std::numeric_limits<C>::max(), t, v, level);
			while (flow) {
				totalFlow += flow;
				flow = send(s, std::numeric_limits<C>::max(), t, v, level);
			}
		}
	}


	void findMinCut(set<T> & minCut, T s) {
		//T size(_nodes[s].edges.size());
		for (auto &e : _nodes[s].edges) {
			//for (T i{ 0 }; i < size; ++i) {
			//_Edge* e{ &_nodes[s].edges[i] };
			if (e.c > e.flow) {
				if (minCut.insert(e.v).second) {
					findMinCut(minCut, e.v);
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
		std::vector<_Edge> edges;
		std::vector<_Edge*> reverse;
	};

	//Dinic's Algorithm
	C send(T u, C flow, T t, std::vector<T> & currEdge, std::vector<T> & level) {
		if (u == t)
			return flow;
		_Node* n{ &_nodes[u] };
		std::vector<_Edge>* nue{ &n->edges };
		T size(nue->size());
		C currFlow, tmpFlow;
		T currCurrEdge;
		_Edge *e;
		if (!n->reverse.size()) {
			for (auto &e : *nue) {
				//for (T i{ 0 }; i < size; ++i) {
				//e = &nue->at(i);
				n->reverse.push_back(&_nodes[e.v].edges[e.rev]);
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

	T _V;
	std::vector<_Node> _nodes;
};

template<typename C = int, typename T = int>
class MaxFlowDinics_Map {
	//Version with better handeling of multiple edges between u and v
	//Simply merges them
	//(Adds a O(log(E)) cost to adding edges)
public:

	MaxFlowDinics_Map(T _V) : _V(_V), _nodes(_V) {}

	void add(T from, T to, C capacity) {
		auto it(_nodes[from].edgeMap.insert({ to, _nodes[from].edges.size() }));
		if (it.second) {
			_nodes[from].edges.emplace_back(from, to, capacity, _nodes[to].edges.size());
			_nodes[to].edges.emplace_back(to, from, 0, _nodes[from].edges.size() - 1);
		}
		else
			_nodes[from].edges[it.first->first].c += capacity;
	}

	void reset() {
		for (auto &n : _nodes)
			for (auto &e : n.edges)
				e.flow = 0;
		//for (T i{ 0 }, u, size; i < _V; ++i) {
		//	size = _nodes[i].edges.size();
		//	for (u = 0; u < size; ++u)
		//		_nodes[i].edges[u].flow = 0;
		//}
	}

	//nput: A network{ \displaystyle G = ((V,E),c,s,t) } G = ((V, E), c, s, t).
	//Output : An{ \displaystyle s - t } s - t flow{ \displaystyle f } f of maximum value.
	C solve(T s, T t) {
		//Set f(e) = 0 for each e in E.
		//Construct G_L from G_f of G. If dist(t) = infty stop and output f.
		T u, size, i;
		C totalFlow{ 0 }, flow;
		std::vector<T> v(_V);
		std::vector<T> level(_V);
		std::queue<T> q;
		T _level;
		while (true) {
			fastFill(&level[0], -1, _V);
			//BFS
			level[s] = 0;  // Level of source vertex
			q.push(s);
			while (!q.empty()) {
				u = q.front(), q.pop();
				_level = level[u] + 1;
				for (auto &e : _nodes[u].edges) {
					//size = _nodes[u].edges.size();
					//for (i = 0; i < size; ++i) {
					//_Edge &e(_nodes[u].edges[i]);
					if (level[e.v] == -1 && e.flow < e.c) {
						level[e.v] = _level;
						q.push(e.v);
					}
				}
			}
			if (level[t] == -1)
				return totalFlow;

			fastFill(&v[0], T(0), _V);
			//Find a blocking flow f' in G_L.
			flow = send(s, std::numeric_limits<C>::max(), t, v, level);
			while (flow) {
				totalFlow += flow;
				flow = send(s, std::numeric_limits<C>::max(), t, v, level);
			}
		}
	}


	void findMinCut(set<T> & minCut, T s) {
		//T size(_nodes[s].edges.size());
		for (auto &e : _nodes[s].edges) {
			//for (T i{ 0 }; i < size; ++i) {
			//_Edge* e{ &_nodes[s].edges[i] };
			if (e.c > e.flow) {
				if (minCut.insert(e.v).second) {
					findMinCut(minCut, e.v);
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

	struct Node {
		std::vector<Edge> edges;
		std::map<T, T> edgeMap;
		std::vector<Edge*> reverse;
	};

	//Dinic's Algorithm
	C send(T u, C flow, T t, std::vector<T> & currEdge, std::vector<T> & level) {
		if (u == t)
			return flow;
		_Node* n{ &_nodes[u] };
		std::vector<_Edge>* nue{ &n->edges };
		T size(nue->size());
		C currFlow, tmpFlow;
		T currCurrEdge;
		_Edge *e;
		if (!n->reverse.size()) {
			for (auto &e : *nue) {
				//for (T i{ 0 }; i < size; ++i) {
				//e = &nue->at(i);
				n->reverse.push_back(&_nodes[e.v].edges[e.rev]);
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

	T _V;
	std::vector<_Node> _nodes;
};