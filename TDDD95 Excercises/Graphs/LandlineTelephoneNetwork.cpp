//https://liu.kattis.com/sessions/errnrk/problems/landline
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
#include <unordered_map>
#include <iterator>
#include <sstream>
#include <map>
#include <bitset>
#include <stack>
#include <complex>
#include <iomanip>
#include <fstream>

using namespace std;

#define _UNLOCKED 1
#if _UNLOCKED
#define gc() getchar_unlocked()
#else
#define gc() getchar()
#endif

//https://www.geeksforgeeks.org/fast-io-for-competitive-programming/
template<typename T>
void fastScan(T &number) {
	register T c;

	number = 0;

	// extract current character from buffer
	c = gc();
	while (!(c > 47 && c < 58))
		c = gc();
	// Keep on extracting characters if they are integers
	// i.e ASCII Value lies from '0'(48) to '9' (57)
	for (; (c>47 && c<58); c = gc())
		number = number * 10 + c - 48;
}


template <class T, class Comparator>
class VectorEditableHeap {
public:
	//priority_queue can't change/remove already inserted values, so time to write my own, 
	//editable heap
	VectorEditableHeap(const size_t& size, const Comparator& comp = std::less<T>()) : _comparator(comp), _map(size) {}

	//Push new, or change old, on the heap
	bool push(const T& newValue, const size_t& id, bool force = false) {
		//Insert fails (pair.second is the bool) if key already exists
		//In anycase it allways return the iterator to the key-value-pair

		if (_map[id].index == -1) {
			//Insertion succeded, value did not exist

			_map[id] = { newValue, id };

			//Do we need to increase the vector or not
			if (_heap.size() == _size)
				_heap.push_back(&_map[id]);
			else
				_heap[_size] = &_map[id];

			_heap[_size]->index = _size;
			_balanceUp(_size); //Balance the heap
			++_size;
			return true;
		}
		else return _push(newValue, id, force);
	}

	void erase(const size_t& id) {
		if (_map[id].index != -1) {
			--_size;
			size_t index(_map[id].index);
			_heap[_size]->index = index; //Move tail to index
			_heap[index] = _heap[_size];
			_map[id].index = -1;//Erase from map

								//Rebalance both directions (dont know if better or worse then childs/parent)
			_balanceDown(index);
			_balanceUp(index);
		}
	}

	//Remove top from heap
	void pop() {
		if (_size > 0) {
			--_size;
			_map[_heap[0]->id].index = -1; //Erase from map
			_heap[_size]->index = 0; //Move tail to top
			_heap[0] = _heap[_size];
			_balanceDown(0); //Rebalance from top
		}
		else
			throw 1; //pop called on empty, throw
					 //Fuck
	}

	bool empty() const {
		return !_size;
	}

	T& top() const {
		return _heap[0]->value;
	}

	size_t& topID() const {
		return _heap[0]->id;
	}

private:

	struct _Node;

	//Push new, or change old, on the heap
	bool _push(const T& newValue, const size_t & id, bool force) {
		//Insert fails (pair.second is the bool) if key already exists
		//In anycase it allways return the iterator to the key-value-pair
		if (_comparator(newValue, _map[id].value)) {
			//Change old value
			_map[id].value = newValue;

			//Rebalance
			size_t newHole(_map[id].index);
			_balanceUp(newHole);
			return true;
		}
		else if (force && _comparator(_map[id].value, newValue)) {
			//Change old value
			_map[id].value = newValue;

			//Rebalance
			size_t newHole(_map[id].index);
			_balanceDown(newHole);
			return true;
		}
		return false;
	}

	void _balanceUp(size_t index) {
		//Balance from index, upwards
		size_t parentIndex((index - 1) >> 1);
		if (parentIndex < _size && _comparator(_heap[index]->value, _heap[parentIndex]->value)) {
			//Parent needs to exists (will turn max if < 0, unsigned) and be worse
			//Change their places
			_heap[index]->index = parentIndex;
			_heap[parentIndex]->index = index;
			swap(_heap[index], _heap[parentIndex]);
			_balanceUp(parentIndex); //Continue upwards
		}
	}

	//size_t
	void _balanceDown(size_t index) {
		//Balance from index, Downwards
		size_t childOne(index + index + 1);
		size_t childTwo(childOne + 1);

		if (((childTwo < _size && _comparator(_heap[childOne]->value, _heap[childTwo]->value))
			|| childTwo == _size) && _comparator(_heap[childOne]->value, _heap[index]->value)) {
			//Child one exists, is better than child two and than index
			//Swap them
			_heap[childOne]->index = index;
			_heap[index]->index = childOne;
			swap(_heap[index], _heap[childOne]);
			//return 
			_balanceDown(childOne); //Rebalance downwards
		}
		else if (childTwo < _size && _comparator(_heap[childTwo]->value, _heap[index]->value)) {
			//Child two exists and is better than child one and index
			//Swap them
			_heap[childTwo]->index = index;
			_heap[index]->index = childTwo;
			swap(_heap[index], _heap[childTwo]);
			//return 
			_balanceDown(childTwo); //Rebalance downwards
		}
		//return index; //This is the end, return it (might not be needed)
	}

	struct _Node {
		//Class/Node for keeping track of existance and position in heap
		_Node() : index(-1) { }
		_Node(const T& val, const size_t& id) : value(val), id(id) {}
		size_t index;
		T value;
		size_t id;
	};

	Comparator _comparator;
	vector<_Node> _map;
	size_t _size{ 0 };
	vector<_Node*> _heap;
};

//Skeleton taken from https://www.geeksforgeeks.org/greedy-algorithms-set-5-prims-minimum-spanning-tree-mst-2/
//Improved to make use of my editableheap, (node->edge)-vector and some return optimizations

// Function to construct and print MST for a graph represented using adjacency
// matrix representation
pair<bool, int> primMST(const vector<vector<pair<int, int>>> & nodes, const int &size, int start, int fullSize) {

	VectorEditableHeap<int, std::less<int>> key(fullSize);   // Key values used to pick minimum weight edge in cut
	vector<bool> mstSet(fullSize, false);  // To represent set of vertices not yet included in MST

										   // Always include first 1st vertex in MST.
										   //key.push(0, size);     // Make key 0 so that this vertex is picked as first vertex
	mstSet[start] = true;

	// Update key value and parent index of the adjacent vertices of
	// the picked vertex. Consider only those vertices which are not yet
	// included in MST
	for (const pair<int, int>& i : nodes[start]) {

		// graph[u][v] is non zero only for adjacent vertices of m
		// mstSet[v] is false for vertices not yet included in MST
		// Update the key only if graph[u][v] is smaller than key[v]
		key.push(i.second, i.first);
	}

	// The MST will have V vertices
	int minNode;
	int cost(0);
	int count(1);
	for (; !key.empty(); ++count) {
		// Pick the minimum key vertex from the set of vertices
		// not yet included in MST
		minNode = key.topID();
		cost += key.top();
		if (cost < 0)
			throw 1;
		key.pop();
		// Add the picked vertex to the MST Set
		mstSet[minNode] = true;

		// Update key value and parent index of the adjacent vertices of
		// the picked vertex. Consider only those vertices which are not yet
		// included in MST
		for (const pair<int, int>& i : nodes[minNode]) {
			// graph[u][v] is non zero only for adjacent vertices of m
			// mstSet[v] is false for vertices not yet included in MST
			// Update the key only if graph[u][v] is smaller than key[v]
			if (!mstSet[i.first])
				key.push(i.second, i.first);
		}
	}

	return { count == size, cost };
}


int main() {
	ios::sync_with_stdio(false);
	cout.tie(nullptr);
	cin.tie(nullptr);

	int n, m, u, v, c, p, p0, s{ 0 };
	int x, r;

	fastScan(n);
	if (n == 1) {
		printf("0\n");
		return 0;
	}
	fastScan(m);
	if (m + 1 < n) {
		printf("impossible\n");
		return 0;
	}
	fastScan(p0);

	vector<vector<pair<int, int>>> nodes(n);
	vector<bool> badHouse(n, false);
	vector<int> badHouses;

	p = p0 + 1;
	while (--p) {
		fastScan(u);
		badHouse[--u] = true;
		badHouses.push_back(u);
	}

	if (n == p0) {
		if (m * 2 == p0 * (p0 - 1)) {
			++m;
			r = 0;
			while (--m) {
				fastScan(u);
				fastScan(v);
				fastScan(c);
				r += c;
			}
			printf("%d\n", r);
			return 0;
		}
		else if (m * 2 < p0 * (p0 - 1)) {
			printf("impossible\n");
			return 0;
		}
		else
			throw 1;
	}

	++m;
	while (--m) {
		fastScan(u);
		fastScan(v);
		fastScan(c);
		--u;
		--v;

		if (!badHouse[v] && !badHouse[u]) {
			nodes[v].emplace_back(u, c);
			nodes[u].emplace_back(v, c);
		}
		else if (badHouse[v] && !badHouse[u]) {
			nodes[v].emplace_back(u, c);
		}
		else if (!badHouse[v] && badHouse[u]) {
			nodes[u].emplace_back(v, c);
		}
	}
	for (int i(0); i < n; ++i) {
		if (!badHouse[i]) {
			s = i;
			break;
		}
	}
	pair<bool, int> success(primMST(nodes, n - p0, s, n));

	if (success.first) {
		int min;
		for (int u : badHouses) {
			if (nodes[u].size() > 0) {
				min = std::numeric_limits<int>::max();
				for (const pair<int, int> & p : nodes[u])
					if (p.second < min)
						min = p.second;
				success.second += min;
			}
			else {
				success.first = false;
				break;
			}
		}
	}


	if (!success.first) {
		printf("impossible\n");
	}
	else {
		printf("%d\n", success.second);
	}

	return 0;
}