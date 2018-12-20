//Leif Eriksson
#include <vector>
#include <cstring>

template<typename T, typename S = int>
class FenwickTree {
    /*            n  --> No. of elements present in input array.
    BITree[0..n] --> Array that represents Binary Indexed Tree.
    arr[0..n-1]  --> Input array for whic prefix sum is evaluated. */
public:

    FenwickTree(S n) : _n{ n }, _v(n + 1) {}

    // Constructs and returns a Binary Indexed Tree for given
    // array of size n.
    FenwickTree(const std::vector<T> &v) : _n{ v.size() }, _v(v.size() + 1) {
        // Store the actual values in BITree[] using update()
        for (S i(0); i < _n; ++i)
            update(i, v[i]);
    }

    // Constructs and returns a Binary Indexed Tree for given
    // size and value.
    FenwickTree(S n, T value) : _n{ n }, _v(n + 1) {
        S i{ 1 }, j;
        T t;
        _v[1] = value;
        while (i + i <= n) {
            _v[i] = i*value;
            memcpy((&_v[1] + i), &_v[1], i * sizeof(value));
            i <<= 1;
        }
        if (i <= n) {
            _v[i] = i*value;
            memcpy((&_v[1] + i), &_v[1], (n - i) * sizeof(value));
        }
    }

    // Returns sum of arr[0..index]. This function assumes
    // that the array is preprocessed and partial sums of
    // array elements are stored in BITree[].
    T sum(S index) const {
        T sum{ 0 }; // Iniialize result

        ++index; // index in BITree[] is 1 more than the index in arr[]

                 // Traverse ancestors of BITree[index]
        while (index>0) {
            // Add current element of BITree to sum
            sum += _v[index];

            // Move index to parent node in getSum View
            index -= index & (-index);
        }
        return sum;
    }

    //Including
    T sum(S index, S index2) const {
        return sum(index2) - sum(index - 1);
    }

    // Updates a node in Binary Index Tree (BITree) at given index
    // in BITree.  The given value 'val' is added to BITree[i] and 
    // all of its ancestors in tree.
    void update(S index, T val) {
        // index in BITree[] is 1 more than the index in arr[]
        ++index;

        // Traverse all ancestors and add 'val'
        while (index <= _n) {
            // Add 'val' to current node of BI Tree
            _v[index] += val;

            // Update index to that of parent in update View
            index += index & (-index);
        }
    }

private:
    const S _n;
    std::vector<T> _v;
};