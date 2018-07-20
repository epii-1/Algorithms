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