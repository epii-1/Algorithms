//Leif Eriksson
#include <vector>
#include <stack>
#include <tuple>

//Skeleton taken from https://www.geeksforgeeks.org/dynamic-programming-set-23-bellman-ford-algorithm/
//Changed to class, now actually marks bad cycles and saves parents for path construction
//And now changed to adjanecy list instead of edgelist

// The main function that finds shortest distances from src to
// all other vertices using Bellman-Ford algorithm.  The function
// also detects negative weight cycle
template<typename C = long long, typename T = size_t>
class BellmanFord {
private:
	struct Node;
public:
    std::vector<Node> nodes;

    void solve() {
        // Step 1: Initialize distances from src to all other vertices
        // as INFINITE
        nodes[_src].dist = 0;
        nodes[_src].parent = _src;

        // Step 2: Relax all edges |V| -1 times. A simple shortest 
        // path from src to any other vertex can have at-most |V| - 1 
        // edges

        T i, j, size;
        T v;
		C u, w;
        T tv{ _V };
        while (--tv != -1) {
            for (i = 0; i < _V; ++i) {
                if (nodes[i].parent != -1) {
					u = nodes[i].dist;
					for(std::pair<T,C>& e : nodes[i].edge){
                        Node& n = nodes[e.first];
                        w = e.second;
                        if (u + w < n.dist) {
                            n.dist = u + w;
                            n.parent = i;
                        }
                    }
                }
            }
        }

        // Step 3: check for negative-weight cycles.  The above step 
        // guarantees shortest distances if graph doesn't contain 
        // negative weight cycle. If we get a shorter path, then there
        // is a cycle.

        std::stack<T> s;

		for (i = 0; i < _V; ++i) {
			if (nodes[i].parent != -1) {
				size = nodes[i].edge.size();
				for (j = 0; j < size; ++j) {
					u = nodes[i].dist;
					v = nodes[i].edge[j].first;
					w = nodes[i].edge[j].second;
					if (u + w < nodes[v].dist || nodes[i].bad) {
						if (!nodes[v].bad)
							s.push(v);
						nodes[v].bad = true;
						nodes[v].parent = i;
					}
				}
			}
		}

        //Find cycles
		for (i = 0; i < _V; ++i) {
			if (nodes[i].parent != -1) {
				size = nodes[i].edge.size();
				if (nodes[i].bad)
					s.push(i);
				else {
					u = nodes[i].dist;
					for (j = 0; j < size; ++j) {
						v = nodes[i].edge[j].first;
						w = nodes[i].edge[j].second;
						if (u + w < nodes[v].dist) {
							if (!nodes[v].bad)
								s.push(v);
							nodes[v].bad = true;
							nodes[v].parent = i;
						}
					}
				}
			}
		}

        while (!s.empty()) {
            //DFS to find all cycle dependant nodes
            i = s.top();
            s.pop();
			for (std::pair<T, C>& e : nodes[i].edge) {
				Node& n = nodes[e.first];
                if (!n.bad)
                    s.push(e.first);
                n.bad = true;
                n.parent = i;
            }
        }
    }

    BellmanFord(T V, T src) : _V(V), _src(src), nodes(V) {}

	std::pair<short, C> shortestPath(T target) {
        if (nodes[target].bad)
            return { -1, 0 };
        if (nodes[target].parent == -1)
            return { 1, 0 };
        return { 0, nodes[target].dist };
    }

private:
    T _V, _src;

	struct Node {
		C dist{ std::numeric_limits<C>::max() };
		T parent{ -1 };
		bool bad{ false };
		std::vector<std::pair<T, C>> edge;
	};
};
