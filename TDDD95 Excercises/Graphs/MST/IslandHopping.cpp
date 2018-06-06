//https://liu.kattis.com/problems/islandhopping
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
    for (; (c>47 && c<58); c = gc())
        number = number * 10 + c - 48;

    if (c == '.') {
        c = gc();
        for (T p(0.1); (c > 47 && c < 58); c = gc(), p *= 0.1)
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
    //priority_queue can't change/remove already inserted values, so time to write my own, 
    //editable heap
    EditableHeap(const Comparator& comp = std::less<T>()) : _comparator(comp) {}

    //Push new, or change old, on the heap
    bool push(const T& newValue, const Identifier& id, bool force = false) {
        //Insert fails (pair.second is the bool) if key already exists
        //In anycase it allways return the iterator to the key-value-pair
#if __cplusplus < 201703L
        auto pair(_map.insert({ id, _Node(newValue, id) }));
#else
        auto pair(_map.try_emplace(id, _Node(newValue, id)));
#endif                                               
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
        else return _push(newValue, it, force);
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
        return !_size;
    }

    T& top() const {
        return _heap[0]->value;
    }

    Identifier& topID() const {
        return _heap[0]->id;
    }

    struct _Node;

    //Push new, or change old, on the heap
    bool _push(const T& newValue, typename std::map<Identifier, _Node>::iterator & it, bool force) {
        //Insert fails (pair.second is the bool) if key already exists
        //In anycase it allways return the iterator to the key-value-pair
        if (_comparator(newValue, it->second.value)) {
            //Change old value
            it->second.value = newValue;

            //Rebalance
            size_t newHole(it->second.index);
            _balanceUp(newHole);
            return true;
        }
        else if (force && _comparator(it->second.value, newValue)) {
            //Change old value
            it->second.value = newValue;

            //Rebalance
            size_t newHole(it->second.index);
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



int main() {
    ios::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);

    int n, m, m2, i, c;
    float u, v, u2, v2, a;
    fastScan(n);
    ++n;
    vector<pair<float, float>> nodes;
    EditableHeap<float, int, std::less<float>> eh;

    auto it{ eh._map.begin() };

    while (--n) {
        fastScan(m);
        nodes.resize(m);
        a = 0;
        m2 = m;
        while (m) {
            fastScan(u);
            fastScan(v);
            nodes[--m] = { u, v };
        }
        u = nodes[0].first;
        v = nodes[0].second;
        for (i = 1; i < m2; ++i) {
            u2 = u - nodes[i].first;
            v2 = v - nodes[i].second;
            eh.push(u2*u2 + v2*v2, i);
        }
        while (!eh.empty()) {
            c = eh.topID();
            a += sqrt(eh.top());
            eh.pop();
            u = nodes[c].first;
            v = nodes[c].second;
            for (it = eh._map.begin(); it != eh._map.end(); ++it) {
                u2 = u - nodes[it->first].first;
                v2 = v - nodes[it->first].second;
                eh._push(u2*u2 + v2*v2, it, false);
            }
        }

        printf("%.4f\n", a);

    }

    return 0;
}