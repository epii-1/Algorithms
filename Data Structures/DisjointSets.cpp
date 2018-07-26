//Leif Eriksson

#include <vector>

//Taken from https://www.geeksforgeeks.org/kruskals-minimum-spanning-tree-using-stl-in-c/
//Sligthly modified 

// To represent Disjoint Sets
template <typename T = size_t>
class DisjointSets {
private:
	std::vector<T> _parent, _rnk;

	// Union by rank
	T _merge(T x, T y) {
		if (x == y)
			return x;
		/* Make tree with smaller height
		a subtree of the other tree  */
		if (_rnk[x] > _rnk[y]) {
			_parent[y] = x;
			return x;
		}
		_parent[x] = y;
		if (_rnk[x] == _rnk[y])
			++_rnk[y];
		return y;
	}

	T _mergeFind2(T x, T y) {
		/* Make the parent of the nodes in the path
		from u--> parent[u] point to parent[u] */
		if (y != _parent[y])
			return _parent[y] = _mergeFind2(x, _parent[y]);
		return _merge(x, y);
	}

	T _mergeFind1(T x, T y) {
		/* Make the parent of the nodes in the path
		from u--> parent[u] point to parent[u] */
		if (x != _parent[x])
			return _parent[x] = _mergeFind1(_parent[x], y);
		return _mergeFind2(x, y);
	}

public:
	// Constructor.
	DisjointSets(const T& n) : _parent(n), _rnk(n) {
		// Allocate memory
		// Initially, all vertices are in
		// different sets and have rank 0.
		for (T i{ 0 }; i < n; ++i) {
			//every element is parent of itself
			_parent[i] = i;
		}
	}

	// Find the parent of a node 'u'
	// Path Compression
	T find(T u) {
		/* Make the parent of the nodes in the path
		from u--> parent[u] point to parent[u] */
		if (u != _parent[u])
			return _parent[u] = find(_parent[u]);
		return u;
	}

	// Union by rank
	void merge(T x, T y) {
		_mergeFind1(x, y);
	}
};