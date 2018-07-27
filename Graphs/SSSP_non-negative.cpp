//Leif Eriksson 
#include <vector>
#include <map>
#include "Data Structures\VectorEditableHeap.cpp"


template<typename C = unsigned long long, typename T = size_t>
class SingleShortestPath {
public:
	std::vector<std::map<T, C>> G; //The graph
	std::vector<std::pair<T, C>> path; //Will contain the previous node (in the optimal path) for all 
									   //visited, and the travel cost

	SingleShortestPath(T size, T start) : _prioQueue(size, _comparator()), G(size),
		_start(start), path(size, { -1, 0 }) {
		//First is current, 2nd is previous, 3rd is total cost;
		_prioQueue.push({ start, 0 }, start);
		path[start].first = start;
	}

	bool shortestPath(T goal) {
		//Calculate the shortest path from start to goal (using already found paths)

		if (path[goal].first != -1) {
			//Already found it, just return
			return true;
		}

		//First is current, 2nd is previous, 3rd is total cost;
		std::pair<T, C> curr;
		T currI, i, neighbor;

		bool found(false);

		//Simpel Dijkstras
		while (!_prioQueue.empty()) {

			//Get the the current best
			curr = _prioQueue.top();
			currI = _prioQueue.topID();
			_prioQueue.pop();

			//Stor the previous and travell cost
			path[currI] = curr;

			//For all neighbors
			for (auto e : G[currI]) {
				neighbor = e.first;
				if (path[neighbor].first == -1) { //Don't bother storing already visited
					_prioQueue.push({ currI, curr.second + e.second },
						neighbor);
				}
			}

			if (currI == goal) {
				//If we are the our goal, return
				//(We have to check for goal after pushing edges, as we reuse the pq)
				found = true;
				break;
			}
		}

		return found;
	}

private:
	struct _comparator {
		//"Have to" transfer the comperator as a type (can be done as function pointer but cba
		bool operator()(const std::pair<T, C> & lhs, const std::pair<T, C> & rhs)	const {
			return lhs.second < rhs.second;
		}
	};

	//First is current, 2nd is previous, 3rd is total cost;
	VectorEditableHeap<std::pair<T, C>, _comparator> _prioQueue;
	T _start;
};