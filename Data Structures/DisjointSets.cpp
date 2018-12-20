//Leif Eriksson

#include <vector>
#include "Implementations\fastFill.cpp"

#define DISJOINT_SET_SIZE 1
// To represent Disjoint Sets
template <typename T = int>
struct DisjointSets {

	// Constructor.
    DisjointSets(T n) : rnk(new T(n)),
#if DISJOINT_SET_SIZE == 1
        , size(n)
#endif
    {
     // Allocate memory
     // Initially, all vertices are in
     // different sets and have rank 0.
     //parent = new T[n];
        fastFill(rnk, -1, n);
    }

	~DisjointSets() {
		delete[] rnk;
	}

	// Find the parent of a node 'u'
	// Path Compression
	T find(T x) {
		// Make the parent of the nodes in the path
		//from u--> parent[u] point to parent[u] 
		if (rnk[x] > -1)
			return rnk[x] = find(rnk[x]);
		//while (rnk[x] > -1) {
		//	if (rnk[rnk[x]] > -1)
		//		rnk[x] = rnk[rnk[x]];
		//	x = rnk[x];
		//}
		return x;
	}

	// Union by rank
	void merge_old(T x, T y) {
		if ((x = find(x)) == (y = find(y)))
			return;
			
#if DISJOINT_SET_SIZE == 1
        --size;
#endif
		//Make tree with smaller height
		//a subtree of the other tree 
		if (rnk[x] > rnk[y])
			swap(x, y);
		else if (rnk[x] == rnk[y])
			--rnk[x];
        //Should we upate the rnk of x if the graph gets flatter?
        //How should we detect that?
		rnk[y] = x;
	}

	// Union by rank
	void merge(T x, T y) {
		mergeFind1(x, y);
	}

#if DISJOINT_SET_SIZE == 1
    T size() { return size; }
#endif

private:
#if DISJOINT_SET_SIZE == 1
    T size;
#endif
	T * rnk;

	// Union by rank
	T _merge(T x, T y) {
		if (x == y)
			return x;
		//Make tree with smaller height
		//a subtree of the other tree 
		if (rnk[x] > rnk[y])
			swap(x, y);
		else if (rnk[x] == rnk[y])
			--rnk[x];
		return rnk[y] = x;
	}

	T mergeFind2(T x, T y) {
		/* Make the parent of the nodes in the path
		from u--> parent[u] point to parent[u] */
		if (rnk[y] > -1)
			return rnk[y] = mergeFind2(x, rnk[y]);
		return _merge(x, y);
	}

	T mergeFind1(T x, T y) {
		/* Make the parent of the nodes in the path
		from u--> parent[u] point to parent[u] */
		if (rnk[x] > -1)
			return rnk[x] = mergeFind1(rnk[x], y);
		return mergeFind2(x, y);
	}
};
