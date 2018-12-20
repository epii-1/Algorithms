//Leif Eriksson

#include <vector>

//All hail wikipedia :)
//https://en.wikipedia.org/wiki/Longest_increasing_subsequence
template<typename T=int>
void lis(const T& n, std::vector<T> & list) {
    //list is X
	std::vector<T> predecessor(n); //P
	std::vector<T> m(n + 1); //M : index of biggest for size i

    T l{ 0 }, i{ 0 }, low, high, mid, newL;
    for (; i < n; ++i) {
        // Binary search for the largest positive i <= L
        // such that X[M[j]] < X[i]
        low = 1;
        high = l;
        while (low <= high) {
            mid = (low + high + 1) >> 1;
            if (list[m[mid]] < list[i])
                low = mid + 1;
            else
                high = mid - 1;
        }

        // After searching, lo is 1 greater than the
        // length of the longest prefix of X[i]
        newL = low;

        // The predecessor of X[i] is the last index of 
        // the subsequence of length newL-1
        predecessor[i] = m[newL - 1];
        m[newL] = i;

        // If we found a subsequence longer than any we've
        // found yet, update L
        if (newL > l)
            l = newL;

    }

    // Reconstruct the longest increasing subsequence
    //vector<int> result(l);
    list.resize(l);
    T k( m[l] );
    for (--l; l > -1; --l){
        list[l] = k;
        k = predecessor[k];
    }

}