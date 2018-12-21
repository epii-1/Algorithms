//Leif Eriksson 
#include <vector>
#include <cmath>
#include "Data Structures\DisjointSets.cpp"
#include "Data Structures\VectorEditableHeap.cpp"

/* Functions returns weight of the MST*/
template <typename C = long long, typename T = size_t>
std::pair<bool, C> minSpanningTree_Kruskal(std::vector<std::pair<C, std::pair<T, T>>> & edges,
	std::vector<std::pair<T, T>> &mstEdges) {
	C mst_wt{ 0 }; // Initialize result

				   // Sort edges in increasing order on basis of cost
	std::sort(edges.begin(), edges.end());

	// Create disjoint sets
	DisjointSets<T> ds(mstEdges.size()+1);

	T u, v, set_u, set_v, count(0);

	// Iterate through all sorted edges
	typename std::vector< std::pair<C, std::pair<T, T>> >::const_iterator it{ edges.begin() };
	for (; it != edges.end(); ++it) {
		u = it->second.first;
		v = it->second.second;

		set_u = ds.find(u);
		set_v = ds.find(v);

		// Check if the selected edge is creating
		// a cycle or not (Cycle is created if u
		// and v belong to same set)
		if (set_u != set_v) {
			// Current edge will be in the MST
			// so print it
			mstEdges[count] = { u,v };
			++count;
			// Update MST weight
			mst_wt += it->first;

			// Merge two sets
			ds.merge(set_u, set_v);
		}
	}

	return { count == mstEdges.size(), mst_wt };
}

//Skeleton taken from https://www.geeksforgeeks.org/greedy-algorithms-set-5-prims-minimum-spanning-tree-mst-2/
//Improved to make use of my editableheap, (node->edge)-vector and some return optimizations

// Function to construct and print MST for a graph represented using adjacency
// matrix representation
// Nodes are on the form {Node(ID), {ID, Cost}}
// Edges on the form {ID1, ID2}, id1<id2;
template <typename C = long long, typename T = size_t>
std::pair<bool, C> minSpanningTree_Prim(std::vector<std::vector<std::pair<T, C>>> & nodes, const T & size, std::vector<std::pair<T, T>> & mstEdges) {
	std::vector<T> parent(size); // Array to store constructed MST

	VectorEditableHeap<C, std::less<C>> key(size);   // Key values used to pick minimum weight edge in cut
	std::vector<bool> mstSet(size);  // To represent set of vertices not yet included in MST

								// Always include first 1st vertex in MST.
								//key.push(0, size);     // Make key 0 so that this vertex is picked as first vertex
	parent[size - 1] = -1; // First node is always root of MST 
	mstSet[size - 1] = true;

	// Update key value and parent index of the adjacent vertices of
	// the picked vertex. Consider only those vertices which are not yet
	// included in MST
	for (std::pair<T, C>& i : nodes[size - 1]) {

		// graph[u][v] is non zero only for adjacent vertices of m
		// mstSet[v] is false for vertices not yet included in MST
		// Update the key only if graph[u][v] is smaller than key[v]
		if (!mstSet[i.first] && key.push(i.second, i.first))
			parent[i.first] = size - 1;
	}

	// The MST will have V vertices
	T minNode;
	mstEdges.resize(size - 1);
	C cost(0);
	T count(1);
	for (; !key.empty(); ++count) {
		// Pick the minimum key vertex from the set of vertices
		// not yet included in MST
		minNode = key.topID();
		cost += key.top();
		key.pop();

		mstEdges[minNode] = { std::min(minNode, parent[minNode]),
			std::max(minNode, parent[minNode]) };

		// Add the picked vertex to the MST Set
		mstSet[minNode] = true;

		// Update key value and parent index of the adjacent vertices of
		// the picked vertex. Consider only those vertices which are not yet
		// included in MST
		for (std::pair<T, C> &i : nodes[minNode]) {

			// graph[u][v] is non zero only for adjacent vertices of m
			// mstSet[v] is false for vertices not yet included in MST
			// Update the key only if graph[u][v] is smaller than key[v]
			if (!mstSet[i.first] && key.push(i.second, i.first))
				parent[i.first] = minNode;
		}
	}

	return { count == size, cost };
}