#include <limits>
#include "2D\Point.cpp"

using namespace std;

template <typename T = long double, typename S = long long>
void merge(vector<Point<T>>& a, vector<Point<T>>& aux, S lo, S mid, S hi) {
    S i, j, k;
    for (k = lo; k <= hi; ++k)
        aux[k] = a[k];

    i = lo; j = mid + 1; k = lo;
    while (i <= mid && j <= hi)
        a[k++] = compY(aux[i], aux[j]) ? aux[i++] : aux[j++];

    // Copy the rest of the left side of the array into the target array
    while (i <= mid)
        a[k++] = aux[i++];
}

template <typename T = long double, typename S = long long>
pair<T, pair<Point<T>, Point<T>>> leastDist(vector<Point>& pointsByX, vector<Point<T>>& pointsByY, vector<Point<T>>& aux, S lo, Sg hi) {
    if (hi <= lo)
        return { numeric_limits<T>::infinity(),{} };

    S mid{ lo + (hi - lo) / 2 };
    pair<T, pair<Point<T>, Point<T>>> delta{ leastDist(pointsByX, pointsByY, aux, lo, mid) };
    pair<T, pair<Point<T>, Point<T>>> dist{ leastDist(pointsByX, pointsByY, aux, mid + 1, hi) };
    if (dist.first < delta.first)
        delta = dist;

    merge<T, S>(pointsByY, aux, lo, mid, hi);

    S M{ 0 }, i, j;
    T dx;
    for (i = lo; i <= hi; ++i) {
        dx = pointsByY[i].x - pointsByX[mid].x;
        if (dx*dx < delta.first)
            aux[M++] = pointsByY[i];
    }
    T distance, t;
    for (i = 0; i + 1 < M; ++i) {
        for (j = i + 1, dx = aux[i + 1].y - aux[i].y; j < M; ++j) {
            dx = aux[j].y - aux[i].y;
            if (dx*dx >= delta.first)
                break;
            distance = aux[i].sDist(aux[j]);
            if (distance < delta.first) {
                delta.first = distance;
                delta.second.first.x = aux[i].x;
                delta.second.first.y = aux[i].y;
                delta.second.second.x = aux[j].x;
                delta.second.second.y = aux[j].y;
            }
        }
    }
    return delta;
}