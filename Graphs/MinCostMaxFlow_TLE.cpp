//https://liu.kattis.com/problems/mincostmaxflow
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
//#include <bits/stdc++.h>

using namespace std;

const long long BIG{ 10000000 };

//https://www.geeksforgeeks.org/fast-io-for-competitive-programming/
template<typename T>
void fastScan(T &number)
{
    //variable to indicate sign of input number
    bool negative = false;
    register T c;

    number = 0;

    // extract current character from buffer
    c = getchar();
    while (!(c == '-' || (c > 47 && c < 58)))
        c = getchar();

    if (c == '-')
    {
        // number is negative
        negative = true;

        // extract the next character from the buffer
        c = getchar();
    }

    // Keep on extracting characters if they are integers
    // i.e ASCII Value lies from '0'(48) to '9' (57)
    for (; (c > 47 && c < 58); c = getchar())
        number = number * 10 + c - 48;

    // if scanned input has a negative sign, negate the
    // value of the input number
    if (negative)
        number *= -1;
}

struct Edge {
    Edge(int u, int v, int c, int rev, int cf, int cost) :
        u(u), v(v), c(c), rev(rev), cost(cost), orgCost(cost), flow{ cf } {}
    int u, v, c, rev, cost, orgCost;
    long long flow, minFlow;
    //bool isRev;
};

struct Node {

    vector<Edge> edges;
    vector<int> reverse;

    long long dist{ BIG };
    int parent{ -1 };
};




//Skeleton taken from https://www.geeksforgeeks.org/dynamic-programming-set-23-bellman-ford-algorithm/
//Changed to class, now actually marks bad cycles and saves parents for path construction
//And now changed to adjanecy list instead of edgelist

// The main function that finds shortest distances from src to
// all other vertices using Bellman-Ford algorithm.  The function
// also detects negative weight cycle
/*template<typename T>
class BellmanFord {
public:
vector<int> parent;

void solve(vector<Node> & nodes) {


int i, j, size;

for (i = 0; i < _V; ++i) {
nodes[i].dist = std::numeric_limits<long long>::max();
nodes[i].parent = -1;
//nodes[i].bad = false;
}

// Step 1: Initialize distances from src to all other vertices
// as INFINITE
nodes[_src].dist = 0;
nodes[_src].parent = _src;

// Step 2: Relax all edges |V| -1 times. A simple shortest
// path from src to any other vertex can have at-most |V| - 1
// edges

int u, v, w;
int tv{ _V };
while (--tv) {
for (i = 0; i < _V; ++i) {
if (nodes[i].parent != -1) {
size = nodes[i].edges.size();
for (j = 0; j < size; ++j) {
if (!nodes[i].edges[j].isRev) {
u = nodes[i].dist;
v = nodes[i].edges[j].v;
w = nodes[i].edges[j].cost;
if (u + w < nodes[v].dist) {
nodes[v].dist = u + w;
nodes[v].parent = i;
}
}
}
}
}
}

// Step 3: check for negative-weight cycles.  The above step
// guarantees shortest distances if graph doesn't contain
// negative weight cycle. If we get a shorter path, then there
// is a cycle.

/*stack<int> s;

//Find cycles
for (i = 0; i < _V; ++i) {
if (nodes[i].parent != -1) {
size = nodes[i].edge.size();
for (j = 0; j < size; ++j) {
u = nodes[i].dist;
v = nodes[i].edge[j].v;
w = nodes[i].edge[j].cost;
if (u + w < nodes[v].dist || nodes[i].bad) {
if (!nodes[v].bad)
s.push(v);
nodes[v].bad = true;
nodes[v].parent = i;
}
}
}
}

while (!s.empty()) {
//DFS to find all cycle dependant nodes
i = s.top();
s.pop();
size = nodes[i].edge.size();
for (j = 0; j < size; ++j) {
v = nodes[i].edge[j].first;
if (!nodes[v].bad)
s.push(v);
nodes[v].bad = true;
nodes[v].parent = i;
}
}*/
/*}

BellmanFord(int V, int src) : _V(V), _src(src) {}

private:
int _V, _src;
};*/

template <class T, typename Identifier, class Comparator>
class EditableHeap {
public:
    //priority_queue can't change/remove already inserted values, so time to write my own,
    //editable heap
    EditableHeap(const Comparator& comp) : _comparator(comp) {}

    //Push new, or change old, on the heap
    void push(const T& newValue, const Identifier& id) {
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

template<typename T>
class SingleShortestPath {
public:
    vector<pair<int, T>> path; //Will contain the previous node (in the optimal path) for all
                               //visited, and the travel cost

    SingleShortestPath(size_t size, size_t start) : _prioQueue(_comparator()),
        _start(start), path(size, make_pair(-1, 0)) {
        //First is current, 2nd is previous, 3rd is total cost;
        _prioQueue.push(make_tuple(start, 0, BIG, 0), start);
        path[start].first = start;
    }

    long long shortestPath(size_t goal, vector<Node> & G) {

        for (int i = 0; i < path.size(); ++i)
            path[i] = { -1, BIG };

        path[_start].first = _start;

        //Calculate the shortest path from start to goal (using already found paths)

        //First is current, 2nd is previous, 3rd is total cost;
        tuple<int, T, long long, size_t> curr;
        int currI, i, neighbor;

        bool found(false);

        long long retVal{ BIG };

        //Simpel Dijkstras
        while (!_prioQueue.empty()) {

            //Get the the current best
            curr = _prioQueue.top();
            currI = _prioQueue.topID();
            _prioQueue.pop();

            //Stor the previous and travell cost
            path[currI] = make_pair(get<0>(curr), get<3>(curr));
            G[currI].dist = get<1>(curr);
            if (currI == goal) {
                //If we are the our goal, return
                //(We have to check for goal after pushing edges, as we reuse the pq)

                if (retVal > get<2>(curr))
                    retVal = get<2>(curr);

                return get<2>(curr);
            }
            else {
                //For all neighbors
                //for (auto e : G[currI].edges) {
                for (int i{ 0 }; i < G[currI].edges.size(); ++i) {
                    neighbor = G[currI].edges[i].v;
                    T newMinFlow{ min(get<2>(curr), G[currI].edges[i].c - G[currI].edges[i].flow) };
                    //cout << newCost << " " << path[neighbor].second << "\n";
                    if (path[neighbor].second > newMinFlow && G[currI].edges[i].flow < G[currI].edges[i].c) { //Don't bother storing already visited
                                                                                                              //cout << "push\n";
                        _prioQueue.push(
                            make_tuple(currI, get<1>(curr) + G[currI].edges[i].cost, newMinFlow, i),
                            neighbor);
                    }
                }
            }
        }

        return retVal;
    }

private:
    struct _comparator {
        //"Have to" transfer the comperator as a type (can be done as function pointer but cba
        bool operator()(const tuple<int, T, long long, size_t> & lhs, const tuple<int, T, long long, size_t> & rhs)
            const {
            return get<1>(lhs) < get<1>(rhs) || (get<1>(lhs) == get<1>(rhs) && get<2>(lhs) > get<2>(rhs));
        }
    };

    //First is current, 2nd is previous, 3rd is total cost;
    EditableHeap<tuple<int, T, long long, size_t>, int, _comparator> _prioQueue;
    size_t _start;
};


//Reduce Cost()
/*void reduceCost(vector<Node> & nodes) {
//For each(i, j) in Ex do
size_t _V{ nodes.size() };
for (int i = 0; i < _V; ++i) {
size_t size = nodes[i].edges.size();
for (int j = 0; j < size; ++j) {
if (!nodes[i].edges[j].isRev) {
nodes[i].edges[j].cost += nodes[i].dist - nodes[nodes[i].edges[j].v].dist;
nodes[nodes[i].edges[j].v].edges[nodes[i].edges[j].rev].cost = 0;
}
}
}
}*/


//Successive Shortest Path with potentials
pair<long long, long long> minCostMaxFlow(int s, int t, size_t V, vector<Node> & nodes) {
    //Transform network G by adding source and sink

    //Initial flow x is zero
    long long flow{ 0 };
    long long cost{ 0 };

    //Use Bellman - Ford's algorithm to establish potentials
    //BellmanFord<long long> bf(V, s);
    //bf.solve(nodes);


    //Reduce Cost()
    //reduceCost(nodes);

    //while (Gx contains a path from s to t) do
    while (true) {
        //Find any shortest path P from s to t
        SingleShortestPath<long long> ssp(nodes.size(), s);
        long long a{ ssp.shortestPath(t,nodes) };

        if (a == BIG)
            break;

        //Reduce Cost()
        //reduceCost(nodes);

        //Augment current flow x along P
        int curr{ t }, prev{ ssp.path[t].first };
        long long i{ ssp.path[t].second };
        while (curr != s) {
            nodes[prev].edges[i].flow += a;
            nodes[curr].edges[nodes[prev].edges[i].rev].flow -= a;
            cost += a * nodes[prev].edges[i].orgCost;
            curr = prev;
            i = ssp.path[prev].second;
            prev = ssp.path[prev].first;
        }

        //update Gx
        flow += a;
    }
    return { flow, cost };
}


int main() {
    ios::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);

    int n, m, s, i, j, t, t1, t2, t3, t4;
    //while (true) {
    //input blablabla
    fastScan(n);
    fastScan(m);
    fastScan(s);
    fastScan(t);


    vector<Node> nodes(n);

    ++m;
    while (--m) {
        //input blablabla
        fastScan(t1);
        fastScan(t2);
        fastScan(t3);
        fastScan(t4);
        nodes[t1].edges.emplace_back(t1, t2, t3, nodes[t2].reverse.size(), 0, t4);
        nodes[t2].edges.emplace_back(t2, t1, t3, nodes[t1].reverse.size(), t3, -t4);
        nodes[t1].reverse.push_back(nodes[t2].edges.size() - 1);
        nodes[t2].reverse.push_back(nodes[t1].edges.size() - 1);
    }


    pair<long long, long long> ans{ minCostMaxFlow(s, t, n, nodes) };
    cout << ans.first << " " << ans.second << "\n";

    return 0;
}


/*
4 4 0 3
0 1 4 10
1 2 2 10
0 2 4 30
2 3 4 10


*/