//https://liu.kattis.com/problems/allpairspath
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
        c = getchar();
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

//Pseudo-code taken from wikipedia
//https://en.wikipedia.org/wiki/Floyd%E2%80%93Warshall_algorithm

template<typename T>
class AllShotestPathFloydWarshall {
public:
    vector<vector<pair<int, T>>> adjacencyList;
    //let dist be a V x V array of minimum distances initialized to inf
    //let next be a V x V array of vertex indices initialized to null
    AllShotestPathFloydWarshall(int V) : _max{ std::numeric_limits<T>::max() },
        _dist(V, vector<T>(V, _max)),
        /*_next(V, vector<int>(V, -1)),*/ _bad(V, vector<bool>(V, false)),
        _V(V), adjacencyList(V) {}

    //procedure FloydWarshallWithPathReconstruction()
    void solve() {
        int i, j, k, u{ 0 }, v, size(adjacencyList.size()), size2;

        for (i = 0; i < _V; ++i)
            _dist[i][i] = 0;

        //for each edge(u, v)
        for (; u < size; ++u) {
            size2 = adjacencyList[u].size();
            for (i = 0; i < size2; ++i) {
                v = adjacencyList[u][i].first;
                if (_dist[u][v] > adjacencyList[u][i].second) {
                    _dist[u][v] = adjacencyList[u][i].second;  // the weight of the edge (u,v)
                                                               //_next[u][v] = v;
                }
            }
        }

        // standard Floyd-Warshall implementation
        for (k = 0; k < _V; ++k)
            for (i = 0; i < _V; ++i)
                for (j = 0; j < _V; ++j)
                    if (_dist[i][k] != _max && _dist[k][j] != _max
                        && _dist[i][j] > _dist[i][k] + _dist[k][j]) {
                        _dist[i][j] = _dist[i][k] + _dist[k][j];
                        //_next[i][j] = _next[i][k];
                    }

        //stack<pair<int, int>> s;
        //Time to find negatives
        for (i = 0; i < _V; ++i)
            if (_dist[i][i] < 0)
                _bad[i][i] = true;

        //If node u can reach a bad node and the bad node can reach node v
        //Then u->v is a bad path
        for (i = 0; i < _V; ++i)
            for (j = 0; j < _V; ++j)
                if (_bad[j][j] && _dist[i][j] != _max)
                    for (k = 0; k < _V; ++k)
                        if (_dist[j][k] != _max)
                            _bad[i][k] = true;
    }

    pair<int, T> getDist(int u, int v) {

        if (_bad[u][v])
            return { -1, 0 };

        if (_dist[u][v] == std::numeric_limits<T>::max())
            return { 1, 0 };

        return { 0, _dist[u][v] };
    }

    //procedure Path(u, v)
    //if next[u][v] = null then
    //  return[]
    //  path = [u]
    //  while u != v
    //      u <- next[u][v]
    //      path.append(u)
    //      return path
private:
    const T _max;
    vector<vector<T>> _dist;
    //vector<vector<int>> _next;
    vector<vector<bool>> _bad;
    const int _V;
};

int main() {
    ios::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);

    int n, m, i, q, t1, t2;
    long long t3;
    while (true) {
        //input blablabla
        fastScan(n);
        fastScan(m);
        fastScan(q);

        if (n == 0 && m == 0 && q == 0)
            break;

        AllShotestPathFloydWarshall<long long> asp(n);

        ++m;
        while (--m) {
            //input blablabla
            fastScan(t1);
            fastScan(t2);
            fastScan(t3);
            asp.adjacencyList[t1].push_back({ t2,t3 });
        }

        asp.solve();

        ++q;
        while (--q) {
            fastScan(t1);
            fastScan(t2);

            pair<int, long long> solution(asp.getDist(t1, t2));
            if (solution.first == -1)
                printf("-Infinity\n");
            else {
                if (solution.first == 1)
                    printf("Impossible\n");
                else
                    printf("%lld\n", solution.second);
            }
        }
        printf("\n");
    }

    return 0;
}

/*


5 4 4
0 1 999
1 2 -2
2 1 1
0 3 2
0 1
2 2
0 3
0 4
*/