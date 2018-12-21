//Robado de shygypsy.com/tools/mcmf4.cpp

/**
*   ///////////////////////
*   // MIN COST MAX FLOW //
*   ///////////////////////
*
*   Authors: Frank Chu, Igor Naverniouk
**/

//Edited and updated by Leif Eriksson

/*********************
* Min cost max flow * (Edmonds-Karp relabelling + fast heap Dijkstra)
*********************
* Takes a directed graph where each edge has a capacity ('cap') and a
* cost per unit of flow ('cost') and returns a maximum flow network
* of minimal cost ('fcost') from s to t. USE mcmf3.cpp FOR DENSE GRAPHS!
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
*      - Worst case: O(m*log(m)*flow  <?  n*m*log(m)*fcost)
* FIELD TESTING:
*      - Valladolid 10594: Data Flow
* REFERENCE:
*      Edmonds, J., Karp, R.  "Theoretical Improvements in Algorithmic
*          Efficieincy for Network Flow Problems".
*      This is a slight improvement of Frank Chu's implementation.
**/

#include <iostream>
#include <climits>
#include <cstring>
using namespace std;

#define NN 1024

// adjacency matrix (fill this up)
int cap[NN][NN];

// cost per unit of flow matrix (fill this up)
int cost[NN][NN];

// flow network and adjacency list
int fnet[NN][NN], adj[NN][NN], deg[NN];

// Dijkstra's predecessor, depth and priority queue
int par[NN], d[NN], q[NN], inq[NN], qs;

// Labelling function
int pi[NN];

#define CLR(a, x) memset( a, x, sizeof( a ) )
#define Inf (INT_MAX/2)
#define BUBL { \
t = q[i]; q[i] = q[j]; q[j] = t; \
t = inq[q[i]]; inq[q[i]] = inq[q[j]]; inq[q[j]] = t; }

// Dijkstra's using non-negative edge weights (cost + potential)
#define Pot(u,v) (d[u] + pi[u] - pi[v])
bool dijkstra(int n, int s, int t)
{
    CLR(d, 0x3F);
    CLR(par, -1);
    CLR(inq, -1);
    //for( int i = 0; i < n; i++ ) d[i] = Inf, par[i] = -1;
    d[s] = qs = 0;
    inq[q[qs++] = s] = 0;
    par[s] = n;

    while (qs)
    {
        // get the minimum from q and bubble down
        int u = q[0]; inq[u] = -1;
        q[0] = q[--qs];
        if (qs) inq[q[0]] = 0;
        for (int i = 0, j = 2 * i + 1, t; j < qs; i = j, j = 2 * i + 1)
        {
            if (j + 1 < qs && d[q[j + 1]] < d[q[j]]) j++;
            if (d[q[j]] >= d[q[i]]) break;
            BUBL;
        }

        // relax edge (u,i) or (i,u) for all i;
        for (int k = 0, v = adj[u][k]; k < deg[u]; v = adj[u][++k])
        {
            // try undoing edge v->u
            if (fnet[v][u] && d[v] > Pot(u, v) - cost[v][u])
                d[v] = Pot(u, v) - cost[v][par[v] = u];

            // try using edge u->v
            if (fnet[u][v] < cap[u][v] && d[v] > Pot(u, v) + cost[u][v])
                d[v] = Pot(u, v) + cost[par[v] = u][v];

            if (par[v] == u)
            {
                // bubble up or decrease key
                if (inq[v] < 0) { inq[q[qs] = v] = qs; qs++; }
                for (int i = inq[v], j = (i - 1) / 2, t;
                    d[q[i]] < d[q[j]]; i = j, j = (i - 1) / 2)
                    BUBL;
            }
        }
    }

    for (int i = 0; i < n; i++) if (pi[i] < Inf) pi[i] += d[i];

    return par[t] >= 0;
}
#undef Pot

int mcmf4(int n, int s, int t, int &fcost)
{
    // build the adjacency list
    CLR(deg, 0);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (cap[i][j] || cap[j][i]) adj[i][deg[i]++] = j;

    CLR(fnet, 0);
    CLR(pi, 0);
    int flow = fcost = 0;

    // repeatedly, find a cheapest path from s to t
    while (dijkstra(n, s, t))
    {
        // get the bottleneck capacity
        int bot = INT_MAX;
        int tt;
        for (int v = t, u = par[v]; v != s; u = par[v = u]) {
            tt = fnet[v][u] ? fnet[v][u] : (cap[u][v] - fnet[u][v]);
            if (tt < bot)
                bot = tt;
        }

        // update the flow network
        for (int v = t, u = par[v]; v != s; u = par[v = u])
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
    //  while ( cin >> numV && numV ) {
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
    for (int i = 0; i<m; i++) {
        fs(a);
        fs(b);
        fs(cap[a][b]);
        fs(cost[a][b]);
    }

    int fcost;
    int flow = mcmf4(numV, s, t, fcost);
    printf("%d %d\n", flow, fcost);

    return 0;
}