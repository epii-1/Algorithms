
template <class T, typename Identifier, class Comparator>
class EditableHeap {
public:
    //priority_queue can't change/remove already inserted values, so time to write my own, 
    //editable heap
    EditableHeap(const Comparator& comp) : _comparator(comp) {}
    EditableHeap() : _comparator(std::less<T>()) {}

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
        else return push(newValue, it);
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