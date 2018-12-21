//Leif Eriksson
#include <vector>

//Pseudo-code taken from wikipedia
//https://en.wikipedia.org/wiki/Floyd%E2%80%93Warshall_algorithm

template<typename C, typename T = int>
class AllShotestPathFloydWarshall {
private:
	const C _max;
	//vector<vector<int>> _next;
	std::vector<std::vector<bool>> _bad;
	const T _V;
public:
	//vector<vector<pair<T, C>>> adjacencyList;
	std::vector<std::vector<C>> dist;
	//let dist be a V x V array of minimum distances initialized to inf
	//let next be a V x V array of vertex indices initialized to null
	AllShotestPathFloydWarshall(T V) : _max{ std::numeric_limits<C>::max() },
		dist(V, std::vector<C>(V, _max)),
		/*_next(V, vector<int>(V, -1)),*/ _bad(V, std::vector<bool>(V, false)),
		_V(V) {}

	//procedure FloydWarshallWithPathReconstruction()
	void solve() {
		T i, j, k, u{ 0 }, v;

		for (i = 0; i < _V; ++i)
			dist[i][i] = 0;

		//for each edge(u, v)
		/*for (; u < size; ++u) {
			size2 = adjacencyList[u].size();
			for (i = 0; i < size2; ++i) {
				v = adjacencyList[u][i].first;
				if (_dist[u][v] > adjacencyList[u][i].second) {
					_dist[u][v] = adjacencyList[u][i].second;  // the weight of the edge (u,v)
															   //_next[u][v] = v;
				}
			}
		}*/

		// standard Floyd-Warshall implementation
		for (k = 0; k < _V; ++k)
			for (i = 0; i < _V; ++i)
				if (dist[i][k] != _max)
					for (j = 0; j < _V; ++j)
						if (dist[k][j] != _max
							&& dist[i][j] > dist[i][k] + dist[k][j]) {
							dist[i][j] = dist[i][k] + dist[k][j];
							//_next[i][j] = _next[i][k];
						}

		//If node u can reach a bad node and the bad node can reach node v
		//Then u->v is a bad path
		for (j = 0; j < _V; ++j)
			if (dist[j][j] < 0) {
				_bad[j][j] = true;
				for (i = 0; i < _V; ++i)
					if (dist[i][j] != _max)
						for (k = 0; k < _V; ++k)
							if (dist[j][k] != _max)
								_bad[i][k] = true;
			}
	}

	std::pair<char, C> getDist(T u, T v) const {

		if (_bad[u][v])
			return { -1, 0 };

		if (dist[u][v] == _max)
			return { 1, 0 };

		return { 0, dist[u][v] };
	}

	//procedure Path(u, v)
	//if next[u][v] = null then
	//  return[]
	//  path = [u]
	//  while u != v
	//      u <- next[u][v]
	//      path.append(u)
	//      return path
};