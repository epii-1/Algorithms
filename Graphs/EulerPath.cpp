//Leif Eriksson
//leier318
#include <vector>
#include <iterator>
#include <list>

using namespace std;

template <typename T = int>
class EulerianPath {
private:
	struct _Node {
		vector<T> edges;
		T i{ 0 }, to{ 0 }, from{ 0 };
	};

public:
	vector<_Node> nodes;

	EulerianPath() {}

	void resize(size_t n) {
		fill(nodes.begin(), min(nodes.end(), nodes.begin() + n), _Node());
		nodes.resize(n);
	}

	bool eulerianPath(list<T> & l) {
		T s{ 0 }, i;

		//Find a logical startnode
		//(Should add a check to only do this is oddIn,
		//Else it should only make sure first node got from > 0)
		for (i = 0; i < nodes.size(); ++i) {
			if (nodes[i].from > nodes[i].to) {
				s = i;
				break;
			}
			//if(nodes[i].from > 0) s = i; //Read comment down bellow
		}

		//Interesting. Is this really correct? What if we have a full cycle without node 0?

		//Walk from start (or node 0)
		_eulerianPathDeep(s, l, -1, -1);
		l.push_front(s);

		//Recheck
		if (!_recheck(l))
			return false;

		//Find unvisited nodes
		for (i = 0; i < nodes.size(); ++i)
			if (nodes[i].i < nodes[i].from)
				return false;

		return true;
	}

private:

	bool _eulerianPathDeep(T i, list<T> & l, const T e, const T e2) {
		_Node* curr{ &nodes[i] };
		//DF walk untill we get stuck
		while (true) {
			_Node* next{ &(nodes[curr->edges[curr->i]]) };
			i = curr->edges[curr->i];

			++curr->i;
			if (i == e) //We found a cycle, can return it
				return true;

			l.push_back(i); //Add to path

			if (i == e2) //We found the start, we can return it
				return false;

			if (next->i == next->from) //This is bad
				return false; //Next is already full

			curr = next;
		}
	}

	//Recheck everything along to path to se if some node still have unused edges
	bool _recheck(list<T> & l) {
		auto it{ l.begin() };
		for (; it != l.end(); ++it) {
			while (nodes[*it].i < nodes[*it].from) {
				list<T> l2;
				if (_eulerianPathDeep(*it, l2, *it, *l.begin())) {
					//Add the newfound cycle
					l2.push_front(*it);
					it = l.insert(it, l2.begin(), l2.end());
				}
				else //Bad Path
					return false;
			}
		}
		return true;
	}


};