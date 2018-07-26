//Leif Eriksson
#include <memory>
#include <cstring>
#include "Implementations\fastFill.cpp"

struct myBitset {
	myBitset(size_t s, bool val = false) : _trueSize{ s }, _s((s >> 3) + bool(s & 7)), _v{ new char[_s] }, _allocSize{ _s } {
		fastFill(_v, (char)(255 * val), _s);
	}

	~myBitset() {
		delete[] _v;
	}

    bool inline operator[] (size_t index) const {
        return _v[index >> 3] & _c[index & 7];
    }

    void inline set(size_t index, bool val) {
        if (val) {
            _v[index >> 3] |= _c[index & 7];
        }
        else {
            _v[index >> 3] &= _n[index & 7];
        }
    }

	void resize(size_t newSize, bool val) {
		if (newSize > _trueSize) {
			size_t _newSize((newSize >> 3) + bool(newSize & 7));
			if (_newSize > _allocSize) {
				char *t(new char[_newSize]);
				memcpy(t, _v, _newSize * sizeof(char));
				fastFill(t + _allocSize, (char)(255 * val), _newSize - _allocSize);
			}
			for (size_t i{ _trueSize }, i < newSize; ++i)
				set(i, val);
			_trueSize = newSize;
			_allocSize = _newSize;	
		} 
		else if (newSize < _trueSize) 
			_trueSize = newSize; //Frankly, we dont give a shit
	}

    void inline flip(size_t index) {
        set(index, !(_v[index >> 3] & _c[index & 7]));
    }

    size_t count() const {
        return count(0, _trueSize);
    }

    size_t count(const size_t from, const size_t to) const {
        const size_t _to((to >> 3) + bool(to & 7));
        size_t nr{ 0 }, i;
        for (size_t i{ from >> 3 }; i < _to; ++i) {
            nr += (((_v[i] & 1) + ((_v[i] & 2) >> 1)) + (((_v[i] & 4) >> 2) + ((_v[i] & 8) >> 3))) +
                ((((_v[i] & 16) >> 4) + ((_v[i] & 32) >> 5)) + (((_v[i] & 64) >> 6) + ((_v[i] & 128) >> 7)));
        }
        for (i = from - (from & 7); i < from; ++i)
            nr -= operator[](i);
        for (i = to; i < _to << 3; ++i)
            nr -= operator[](i);
        return nr;
    }

    const static vector<char> _c;
    const static vector<char> _n;
    size_t _trueSize;
    size_t _s;
	size_t _allocSize;
	char *_v;
};

const vector<char> myBitset::_c{ char(1), char(2), char(4), char(8),
char(16), char(32), char(64), char(128) };
const vector<char> myBitset::_n{ char(254), char(253), char(251), char(247),
char(239), char(223), char(191), char(127) };
