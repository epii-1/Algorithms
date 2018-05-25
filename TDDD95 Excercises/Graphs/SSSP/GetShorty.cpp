//https://liu.kattis.com/problems/getshorty
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
#include <iomanip>

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

    if (c == '.') {
        c = getchar();
        for (long double p = 0.1; (c>47 && c<58); c = getchar_unlocked(), p *= 0.1)
            number += (c - 48)*p;
    }

    // if scanned input has a negative sign, negate the
    // value of the input number
    if (negative)
        number *= -1;
}

template <class T, typename Identifier, class Comparator>
class EditableHeap {
public:
    struct _Node {
        //Class/Node for keeping track of existance and position in heap
        _Node() { throw 1; } //The compiler demands it, but it's never used :)
        _Node(const T& val, const Identifier& id) : value(val), id(id) {}
        size_t index;
        T value;
        Identifier id;
    };

    map<Identifier, _Node> ehMap;

    //priority_queue can't change/remove already inserted values, so time to write my own, 
    //editable heap
    EditableHeap(const Comparator& comp) : _comparator(comp) {}
    EditableHeap() : _comparator(std::less<T>()) {}

    //Push new, or change old, on the heap
    bool push(const T& newValue, const Identifier& id) {
        //Insert fails (pair.second is the bool) if key already exists
        //In anycase it allways return the iterator to the key-value-pair
        auto pair(ehMap.insert(make_pair(id, _Node(newValue, id)))); //This should (Maybe) be a 
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


    //Push new, or change old, on the heap
    bool push(const T& newValue, typename std::map<Identifier, _Node>::iterator & it) {
        //Insert fails (pair.second is the bool) if key already exists
        //In anycase it allways return the iterator to the key-value-pair
        //auto pair(map.insert(make_pair(id, _Node(newValue, id)))); //This should (Maybe) be a 
        //try_emplace but we lack c++17 support 
        //auto it(pair.first);
        if (_comparator(newValue, it->second.value)) {
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
        auto it(ehMap.find(id));
        if (it != ehMap.end()) {
            --_size;
            size_t index(it->second.index);
            _heap[_size]->index = index; //Move tail to index
            _heap[index] = _heap[_size];
            ehMap.erase(it);//Erase from map

                            //Rebalance both directions (dont know if better or worse then childs/parent)
            _balanceDown(index);
            _balanceUp(index);
        }
    }

    //Remove top from heap
    void pop() {
        if (_size > 0) {
            --_size;
            ehMap.erase(_heap[0]->id); //Erase from map
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

    Comparator _comparator;
    size_t _size{ 0 };
    vector<_Node*> _heap;
};

//Small struct for storing nodes and their (outgoing) edges
struct GraphNode {
    size_t id;
    vector<pair<int, double>> edges;
};

template<typename T>
class SingleShortestPath {
public:
    vector<GraphNode> G; //The graph
    vector<T> path; //Will contain the previous node (in the optimal path) for all 
                    //visited, and the travel cost

    SingleShortestPath(size_t size, size_t start) : _prioQueue(_comparator()), G(size),
        _start(start), path(size, -1) {
        //First is current, 2nd is previous, 3rd is total cost;
        _prioQueue.push(1, start);
        path[start] = 1;
    }

    bool shortestPath(size_t goal) {
        //Calculate the shortest path from start to goal (using already found paths)

        //if (path[goal].first != -1) {
        //Already found it, just return
        //    return true;
        //}

        //First is current, 2nd is previous, 3rd is total cost;
        T curr;
        int currI, i, neighbor;

        bool found(false);
        //Simpel Dijkstras
        while (!_prioQueue.empty()) {

            //Get the the current best
            curr = _prioQueue.top(),
                currI = _prioQueue.topID();
            _prioQueue.pop();

            //Stor the previous and travell cost
            path[currI] = curr;

            if (currI == goal) {
                //If we are the our goal, return
                //(We have to check for goal after puching edges, as we reuse the pq)
                found = true;
                break;
            }

            //For all neighbors
            for (auto e : G[currI].edges) {
                neighbor = e.first;
                if (path[neighbor] == -1) { //Don't bother storing already visited
                    _prioQueue.push(curr * e.second,
                        neighbor);
                }
            }
        }

        return found;
    }

private:

    struct _comparator {
        //"Have to" transfer the comperator as a type (can be done as function pointer but cba
        bool operator()(const T & lhs, const T & rhs)
            const {
            return lhs > rhs;
        }
    };

    //First is current, 2nd is previous, 3rd is total cost;
    EditableHeap<T, int, _comparator> _prioQueue;
    size_t _start;
};


int main() {
    ios::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);

    int n, m, t1, t2, i;
    double f;

    while (true) {
        fastScan(n);
        fastScan(m);

        if (n == 0 && m == 0)
            break;

        SingleShortestPath<double> ssp(n, 0);

        for (i = 0; i < m; ++i) {
            fastScan(t1);
            fastScan(t2);
            fastScan(f);

            ssp.G[t1].edges.push_back({ t2, f });
            ssp.G[t2].edges.push_back({ t1, f });
        }

        ssp.shortestPath(n - 1);
        cout << std::fixed << std::setprecision(4) << ssp.path[n - 1] << "\n";

    }

    return 0;
}