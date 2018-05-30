//https://github.com/evandrix/codejam/blob/master/lib/algorithms/Graph/min-cost-max-flow-2.cpp
/**
*   ///////////////////////
*   // MIN COST MAX FLOW //
*   ///////////////////////
*
*   Authors: Frank Chu, Igor Naverniouk
**/

//Edited and updated by Leif Eriksson

/*********************
* Min cost max flow * (Edmonds-Karp relabelling + Dijkstra)
*********************
* Takes a directed graph where each edge has a capacity ('cap') and a
* cost per unit of flow ('cost') and returns a maximum flow network
* of minimal cost ('fcost') from s to t. USE THIS CODE FOR (MODERATELY)
* DENSE GRAPHS; FOR VERY SPARSE GRAPHS, USE mcmf4.cpp.
*
* PARAMETERS:
*      - cap (global): adjacency matrix where cap[u][v] is the capacity
*          of the edge u->v. cap[u][v] is 0 for non-existent edges.
*      - cost (global): a matrix where cost[u][v] is the cost per unit
*          of flow along the edge u->v. If cap[u][v] == 0, cost[u][v] is
*          ignored. ALL COSTS MUST BE NON-NEGATIVE!
*      - n: the number of vertices ([0, n-1] are considered as vertices).
*      - s: source vertex.
*      - t: sink.
* RETURNS:
*      - the flow
*      - the total cost through 'fcost'
*      - fnet contains the flow network. Careful: both fnet[u][v] and
*          fnet[v][u] could be positive. Take the difference.
* COMPLEXITY:
*      - Worst case: O(n^2*flow  <?  n^3*fcost)
* FIELD TESTING:
*      - Valladolid 10594: Data Flow
* REFERENCE:
*      Edmonds, J., Karp, R.  "Theoretical Improvements in Algorithmic
*          Efficieincy for Network Flow Problems".
*      This is a slight improvement of Frank Chu's implementation.
**/

#include <string.h>
#include <limits.h>
using namespace std;

// the maximum number of vertices + 1
#define NN 1024

// adjacency matrix (fill this up)
int cap[NN][NN];

// cost per unit of flow matrix (fill this up)
int cost[NN][NN];

// flow network and adjacency list
int fnet[NN][NN], adj[NN][NN], deg[NN];

// Dijkstra's successor and depth
int par[NN], d[NN];        // par[source] = source;

                           // Labelling function
int pi[NN];

#define CLR(a, x) memset( a, x, sizeof( a ) )
#define Inf (INT_MAX/2)

// Dijkstra's using non-negative edge weights (cost + potential)
#define Pot(u,v) (d[u] + pi[u] - pi[v])
bool dijkstra(int n, int s, int tt) {
    int i, v, u, bestD;
    for (i = 0; i < n; ++i) d[i] = Inf, par[i] = -1;
    d[s] = 0;
    par[s] = -n - 1;

    while (1) {
        // find u with smallest d[u]
        u = -1, bestD = Inf;
        for (int i = 0; i < n; ++i) if (par[i] < 0 && d[i] < bestD)
            bestD = d[u = i];
        if (bestD == Inf) break;

        // relax edge (u,i) or (i,u) for all i;
        par[u] = -par[u] - 1;
        for (i = 0; i < deg[u]; ++i) {
            // try undoing edge v->u      
            v = adj[u][i];
            if (par[v] >= 0) continue;
            if (fnet[v][u] && d[v] > Pot(u, v) - cost[v][u])
                d[v] = Pot(u, v) - cost[v][u], par[v] = -u - 1;

            // try edge u->v
            if (fnet[u][v] < cap[u][v] && d[v] > Pot(u, v) + cost[u][v])
                d[v] = Pot(u, v) + cost[u][v], par[v] = -u - 1;
        }
    }

    for (i = 0; i < n; ++i) if (pi[i] < Inf) pi[i] += d[i];

    return par[tt] >= 0;
}
#undef Pot

int mcmf3(int n, int s, int t, int &fcost) {
    // build the adjacency list
    CLR(deg, 0);
    int i, j, v, u, tt, bot;
    for (i = 0; i < n; ++i)
        for (j = 0; j < n; ++j)
            if (cap[i][j] || cap[j][i]) adj[i][deg[i]++] = j;

    CLR(fnet, 0);
    CLR(pi, 0);
    int flow = fcost = 0;

    // repeatedly, find a cheapest path from s to t
    while (dijkstra(n, s, t)) {
        // get the bottleneck capacity
        bot = INT_MAX;
        for (v = t, u = par[v]; v != s; u = par[v = u]) {
            tt = fnet[v][u] ? fnet[v][u] : (cap[u][v] - fnet[u][v]);
            if (tt < bot)
                bot = tt;
        }

        // update the flow network
        for (v = t, u = par[v]; v != s; u = par[v = u])
            if (fnet[v][u]) { fnet[v][u] -= bot; fcost -= bot * cost[v][u]; }
            else { fnet[u][v] += bot; fcost += bot * cost[u][v]; }

            flow += bot;
    }

    return flow;
}

//----------------- EXAMPLE USAGE -----------------
#include <iostream>
#include <stdio.h>
using namespace std;

#define _UNLOCKED 1
#if _UNLOCKED
#define gc() getchar_unlocked()
#else
#define gc() getchar()
#endif

template<typename T>
void fs(T &number) {
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
        T pot(0.1);
        for (; (c>47 && c<58); c = gc(), pot *= 0.1)
            number += (c - 48)*pot;
    }

    // if scanned input has a negative sign, negate the
    // value of the input number
    if (negative)
        number *= -1;
}

int main() {
    ios::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);

    int numV;

    fs(numV);
    memset(cap, 0, sizeof(cap));

    int m, a, b, c, cp;
    int s, t;
    fs(m);
    fs(s);
    fs(t);

    // fill up cap with existing capacities.
    // if the edge u->v has capacity 6, set cap[u][v] = 6.
    // for each cap[u][v] > 0, set cost[u][v] to  the
    // cost per unit of flow along the edge i->v
    for (int i = 0; i<m; ++i) {
        fs(a);
        fs(b);
        fs(cap[a][b]);
        fs(cost[a][b]);
    }

    int fcost;
    int flow = mcmf3(numV, s, t, fcost);
    printf("%d %d\n", flow, fcost);

    return 0;
}