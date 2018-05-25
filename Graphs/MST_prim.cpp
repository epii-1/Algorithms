//https://liu.kattis.com/problems/minspantree
//Leif Eriksson 
//leier318

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <random>
#include <iterator>
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
#include <bits/stdc++.h>

using namespace std;

//https://www.geeksforgeeks.org/fast-io-for-competitive-programming/
template<typename T>
void fastScan(T &number)
{
    //variable to indicate sign of input number
    bool negative = false;
    register T c;

    number = 0;

    // extract current character from buffer
    c = getchar_unlocked();
    while (!(c == '-' || (c > 47 && c < 58)))
        c = getchar_unlocked();

    if (c == '-')
    {
        // number is negative
        negative = true;

        // extract the next character from the buffer
        c = getchar_unlocked();
    }

    // Keep on extracting characters if they are integers
    // i.e ASCII Value lies from '0'(48) to '9' (57)
    for (; (c>47 && c<58); c = getchar_unlocked())
        number = number * 10 + c - 48;

    // if scanned input has a negative sign, negate the
    // value of the input number
    if (negative)
        number *= -1;
}


template <class T, typename Identifier, class Comparator>
class EditableHeap {
public:
    //priority_queue can't change/remove already inserted values, so time to write my own, 
    //editable heap
    EditableHeap(const Comparator& comp) : _comparator(comp) {}
    EditableHeap() : _comparator(std::less<T>()) {}

    //Push new, or change old, on the heap
    bool push(const T& newValue, const Identifier& id) {
        //Insert fails (pair.second is the bool) if key already exists
        //In anycase it allways return the iterator to the key-value-pair
        auto pair(_map.insert(make_pair(id, _Node(newValue, id)))); //This should (Maybe) be a 
                                                                    //try_emplace but we lack c++17 support 
        auto it(pair.first);
        if (pair.second) {
            //Insertion succeded, value did not exist

            //Do we need to increase the vector or not
            if (_heap.size() == _size)
                _heap.push_back(&it->second);
            else
                _heap[_size] = &it->second;

            _heap[_size]->index = _size;
            _balanceUp(_size); //Balance the heap
            ++_size;
            return true;
        }
        else if (_comparator(newValue, it->second.value)) {
            //Change old value
            it->second.value = newValue;

            //This is not needed as we can never change to something worse in this case
            //Rebalance (ignoring the changed one)
            //size_t newHole = _balanceDown(_m[i].index);

            //All this should be done by controlls in the case of potential "worsenings"

            size_t newHole(it->second.index);

            //Rebalance (the changed one)
            //_m[i].index = newHole;
            //_v[newHole] = &_m[i];
            _balanceUp(newHole);
            return true;
        }
        return false;
    }

    void erase(const Identifier& id) {
        auto it(_map.find(id));
        if (it != _map.end()) {
            --_size;
            size_t index(it->second.index);
            _heap[_size]->index = index; //Move tail to index
            _heap[index] = _heap[_size];
            _map.erase(it);//Erase from map

                           //Rebalance both directions (dont know if better or worse then childs/parent)
            _balanceDown(index);
            _balanceUp(index);
        }
    }

    //Remove top from heap
    void pop() {
        if (_size > 0) {
            --_size;
            _map.erase(_heap[0]->id); //Erase from map
            _heap[_size]->index = 0; //Move tail to top
            _heap[0] = _heap[_size];
            _balanceDown(0); //Rebalance from top
        }
        else
            throw 1; //pop called on empty, throw
                     //Fuck
    }

    bool empty() const {
        return _size == 0;
    }

    T& top() const {
        return _heap[0]->value;
    }

    Identifier& topID() const {
        return _heap[0]->id;
    }

private:
    void _balanceUp(size_t index) {
        //Balance from index, upwards
        size_t parentIndex((index - 1) / 2);
        if (parentIndex < _size && _comparator(_heap[index]->value, _heap[parentIndex]->value)) {
            //Parent needs to exists (will turn negative if < 0, unsigned) and be worse
            //Change their places
            _heap[index]->index = parentIndex;
            _heap[parentIndex]->index = index;
            swap(_heap[index], _heap[parentIndex]);
            _balanceUp(parentIndex); //Continue upwards
        }
    }

    size_t _balanceDown(size_t index) {
        //Balance from index, Downwards
        size_t childOne(index * 2 + 1);
        size_t childTwo(childOne + 1);

        if (((childTwo < _size && _comparator(_heap[childOne]->value, _heap[childTwo]->value))
            || childTwo == _size) && _comparator(_heap[childOne]->value, _heap[index]->value)) {
            //Child one exists, is better than child two and than index
            //Swap them
            _heap[childOne]->index = index;
            _heap[index]->index = childOne;
            swap(_heap[index], _heap[childOne]);
            return _balanceDown(childOne); //Rebalance downwards
        }
        else if (childTwo < _size && _comparator(_heap[childTwo]->value, _heap[index]->value)) {
            //Child two exists is better than child one and index
            //Swap them
            _heap[childTwo]->index = index;
            _heap[index]->index = childTwo;
            swap(_heap[index], _heap[childTwo]);
            return _balanceDown(childTwo); //Rebalance downwards
        }
        return index; //This is the end, return it (might not be needed)
    }

    struct _Node {
        //Class/Node for keeping track of existance and position in heap
        _Node() { throw 1; } //The compiler demands it, but it's never used :)
        _Node(const T& val, const Identifier& id) : value(val), id(id) {}
        size_t index;
        T value;
        Identifier id;
    };

    Comparator _comparator;
    map<Identifier, _Node> _map;
    size_t _size{ 0 };
    vector<_Node*> _heap;
};

//Skeleton taken from https://www.geeksforgeeks.org/greedy-algorithms-set-5-prims-minimum-spanning-tree-mst-2/
//Improved to make use of my editableheap, (node->edge)-vector and some return optimizations

// Function to construct and print MST for a graph represented using adjacency
// matrix representation
pair<bool, long long> primMST(vector<vector<pair<int, int>>> & nodes, size_t size, vector<pair<int, int>> & mstEdges)
{
    vector<int> parent(size); // Array to store constructed MST

    EditableHeap<int, int, std::less<int>> key;   // Key values used to pick minimum weight edge in cut
    vector<bool> mstSet(size, false);  // To represent set of vertices not yet included in MST

    --size;

    // Always include first 1st vertex in MST.
    //key.push(0, size);     // Make key 0 so that this vertex is picked as first vertex
    parent[size] = -1; // First node is always root of MST 
    mstSet[size] = true;

    // Update key value and parent index of the adjacent vertices of
    // the picked vertex. Consider only those vertices which are not yet
    // included in MST
    for (pair<int, int> i : nodes[size]) {

        // graph[u][v] is non zero only for adjacent vertices of m
        // mstSet[v] is false for vertices not yet included in MST
        // Update the key only if graph[u][v] is smaller than key[v]
        if (!mstSet[i.first] && key.push(i.second, i.first))
            parent[i.first] = size;
    }

    // The MST will have V vertices
    int minNode;
    mstEdges.resize(size);
    long long cost(0);
    int count(0);
    for (; !key.empty(); ++count) {
        // Pick the minimum key vertex from the set of vertices
        // not yet included in MST
        minNode = key.topID();
        cost += key.top();
        key.pop();

        mstEdges[minNode] = make_pair(min(minNode, parent[minNode]),
            max(minNode, parent[minNode]));

        // Add the picked vertex to the MST Set
        mstSet[minNode] = true;

        // Update key value and parent index of the adjacent vertices of
        // the picked vertex. Consider only those vertices which are not yet
        // included in MST
        for (pair<int, int> i : nodes[minNode]) {

            // graph[u][v] is non zero only for adjacent vertices of m
            // mstSet[v] is false for vertices not yet included in MST
            // Update the key only if graph[u][v] is smaller than key[v]
            if (!mstSet[i.first] && key.push(i.second, i.first))
                parent[i.first] = minNode;
        }
    }

    return make_pair(count == size, cost);
}


int main() {
    ios::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);

    int n, m, u, v, c;
    long long x, r;
    while (true) {
        fastScan(n);
        fastScan(m);

        if (n == 0 && m == 0)
            break;

        vector<vector<pair<int, int>>> nodes(n);

        ++m;
        while (--m) {
            fastScan(u);
            fastScan(v);
            fastScan(c);
            nodes[u].emplace_back(v, c);
            nodes[v].emplace_back(u, c);
        }

        vector<pair<int, int>> mstEdges;

        pair<bool, long long> success(primMST(nodes, n, mstEdges));

        if (!success.first) {
            printf("Impossible\n");
        }
        else {
            printf("%lld\n", success.second);
            sort(mstEdges.begin(), mstEdges.end(),
                [](const pair<int, int>& lhs, const pair<int, int>& rhs)->
                bool {return lhs.first < rhs.first ||
                (lhs.first == rhs.first && lhs.second < rhs.second); });
            for (pair<int, int> p : mstEdges)
                printf("%d %d\n", p.first, p.second);
        }

    }

    return 0;
}