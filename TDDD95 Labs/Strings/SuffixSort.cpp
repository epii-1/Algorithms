//https://liu.kattis.com/problems/suffixsorting
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
#include <complex>
#include <bits/stdc++.h>

using namespace std;

//https://www.geeksforgeeks.org/fast-io-for-competitive-programming/
template<typename T>
bool fastScan(T &number) {
    register T c;

    number = 0;

    // extract current character from buffer
    c = getchar();
    while (!((c > 47 && c < 58) || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')))
        c = getchar_unlocked();

    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return false;

    // Keep on extracting characters if they are integers
    // i.e ASCII Value lies from '0'(48) to '9' (57)
    for (; (c > 47 && c < 58); c = getchar_unlocked())
        number = number * 10 + c - 48;
    return true;
}

class SuffixArray {
#define _SUFFIX_ARRAY_DEBUG 0
	//http://zork.net/~st/jottings/sais.html
public:

	std::vector<int> static createSA(const std::string& s) {
		std::vector<int> t(s.begin(), s.end());
		return makeSuffixArrayByInducedSorting(t, 128);
	}

private:
	std::vector<int> static makeSuffixArrayByInducedSorting(const std::vector<int>& s, int alphabetSize) {

		// Classify each character of the string as S_TYPE or L_TYPE
		std::vector<bool> type(buildTypeMap(s));

		// We'll be slotting suffixes into buckets according to what
		// character they start with, so let's precompute that info now.

		std::vector<int> head, tail;
		findBucketHeadsAndTails(findBucketSizes(s, alphabetSize), head, tail);

		// Use a simple bucket - sort to insert all the LMS suffixes into
		// approximately the right place the suffix array.
		std::vector<int> guessedSuffixArray(guessLMSSort(s, type, tail));

		// Slot all the other suffixes into guessedSuffixArray, by using
		// induced sorting.This may move the LMS suffixes around.

		induceSortL(s, guessedSuffixArray, type, head);
		induceSortS(s, guessedSuffixArray, type, tail);

		// Create a new string that summarises the relative order of LMS
		// suffixes in the guessed suffix array.
		std::vector<int> summaryString;
		int summaryAlphabetSize;
		std::vector<int> summarySuffixOffsets;
		summariseSuffixArray(s, guessedSuffixArray, summaryString,
			summaryAlphabetSize, summarySuffixOffsets, type);

		// Make a sorted suffix array of the summary string.
		// AKA summarySuffixArray
		guessedSuffixArray = makeSummarySuffixArray(
			summaryString,
			summaryAlphabetSize);
		// Using the suffix array of the summary string, determine exactly
		// where the LMS suffixes should go in our final array.
		// AKA result
		summaryString = accurateLMSSort(s, tail, type,
			guessedSuffixArray, summarySuffixOffsets);
		// ...and once again, slot all the other suffixes into place with
		// induced sorting.
		induceSortL(s, summaryString, type, head);
		induceSortS(s, summaryString, type, tail);

		return summaryString;
	}


	std::vector<bool> static buildTypeMap(const std::vector<int>& s) {
		// S_TYPE is true
		if (!s.size())
			return std::vector<bool>(0);

		std::vector<bool> type(s.size() + 1);

		int i(s.size());
		type[i] = true;

		for (i -= 2; i > -1; --i) {
			if (s[i] < s[i + 1])
				type[i] = true;
			else if (s[i] == s[i + 1])
				type[i] = type[i + 1];
		}
		return type;
	}

	std::vector<int> static findBucketSizes(const std::vector<int>& s, int alphabetSize) {
		std::vector<int> bucketSize(alphabetSize);
		for (int c : s)
			++bucketSize[c];
		return bucketSize;
	}

	void static findBucketHeadsAndTails(const std::vector<int>&& bucketSize, std::vector<int>& head, std::vector<int>& tail) {
		int offset(0);
		for (int size : bucketSize) {
			head.push_back(offset + 1);
			offset += size;
			tail.push_back(offset);
		}
	}

	bool static isLMSChar(int offset, const std::vector<bool>& type) {
		if (offset == 0)
			return false;
		if (type[offset] && !type[offset - 1])
			return true;

		return false;
	}

	bool static lmsSubstringsAreEqual(const std::vector<int>& s, int offsetA, int offsetB, const std::vector<bool>& type) {
		//No other substring is equal to the empty suffix.
		if (offsetA == s.size() || offsetB == s.size())
			return false;

		for (int i(0); true; ++i) {
			bool aIsLMS(isLMSChar(i + offsetA, type));
			bool bIsLMS(isLMSChar(i + offsetB, type));

			//If we've found the start of the next LMS substrings...
			if (i > 0 && aIsLMS && bIsLMS) {
				//...then we made it all the way through our original LMS
				//substrings without finding a difference, so we can go
				//home now.
				return true;
			}

			if (aIsLMS != bIsLMS) {
				//We found the end of one LMS substring before we reached
				//the end of the other.
				return false;
			}

			if (s[i + offsetA] != s[i + offsetB]) {
				//We found a character difference, we're done.
				return false;
			}
		}
	}

	std::vector<int> static guessLMSSort(const std::vector<int>& s, const std::vector<bool>& type, std::vector<int> bucketTails) {
		// Create a suffix array with room for a pointer to every suffix of
		// the string, including the empty suffix at the end.
		std::vector<int> guessedSuffixArray(type.size(), -1);

		// Bucket - sort all the LMS suffixes into their appropriate bucket.
		for (int i(0); i < s.size(); ++i) {
			if (!isLMSChar(i, type)) {
				// Not the start of an LMS suffix
				continue;
			}

			// Which bucket does this suffix go into ?
			int bucketIndex(s[i]);
			// Add the start position at the tail of the bucket...
			guessedSuffixArray[bucketTails[bucketIndex]] = i;
			// ...and move the tail pointer down.
			--bucketTails[bucketIndex];

			// Show the current state of the array
#if _SUFFIX_ARRAY_DEBUG
			showSuffixArray(guessedSuffixArray);
#endif
		}
		// The empty suffix is defined to be an LMS - substring, and we know
		// it goes at the front.
		guessedSuffixArray[0] = s.size();

#if _SUFFIX_ARRAY_DEBUG
		showSuffixArray(guessedSuffixArray);
#endif

		return guessedSuffixArray;
	}

	void static induceSortL(const std::vector<int>& s, std::vector<int>& guessedSuffixArray, const std::vector<bool>& type,
		std::vector<int> bucketHeads) {

		// For each cell in the suffix array....
		for (int i(0); i < guessedSuffixArray.size(); ++i) {
			// We're interested in the suffix that begins to the left of
			// the suffix this entry points at.
			int j(guessedSuffixArray[i] - 1);
			if (j < 0) {
				// There is no useful information in the typemap at this
				// location; skip it.
				continue;
			}
			if (type[j]) {
				// We're only interested in L-type suffixes right now.
				continue;
			}

			// Which bucket does this suffix go into ?
			int bucketIndex(s[j]);
			// Add the start position at the head of the bucket...
			guessedSuffixArray[bucketHeads[bucketIndex]] = j;
			// ...and move the head pointer up.
			++bucketHeads[bucketIndex];

#if _SUFFIX_ARRAY_DEBUG
			showSuffixArray(guessedSuffixArray);
#endif
		}
	}

	void static induceSortS(const std::vector<int>& s, std::vector<int>& guessedSuffixArray, const std::vector<bool>& type, std::vector<int> bucketTails) {

		for (int i(guessedSuffixArray.size() - 1); i > -1; --i) {
			int j(guessedSuffixArray[i] - 1);
			if (j < 0) {
				// There is no useful information in the typemap at this
				// location; skip it.
				continue;
			}
			if (!type[j]) {
				// We're only interested in S-type suffixes right now.
				continue;
			}

			// Which bucket does this suffix go into ?
			int bucketIndex(s[j]);
			// Add the start position at the tail of the bucket...
			guessedSuffixArray[bucketTails[bucketIndex]] = j;
			// ...and move the tail pointer down.
			--bucketTails[bucketIndex];

#if _SUFFIX_ARRAY_DEBUG
			showSuffixArray(guessedSuffixArray);
#endif
		}
	}

	void static summariseSuffixArray(const std::vector<int>& s, const std::vector<int>& guessedSuffixArray,
		std::vector<int>& summaryString, int& summaryAlphabetSize,
		std::vector<int>& summarySuffixOffsets, const std::vector<bool>& type) {
		// We will use this array to store the names of LMS substrings in
		// the positions they appear in the original string.
		std::vector<int> lmsNames(guessedSuffixArray.size(), -1);

		// Keep track of what names we've allocated.
		int currentName(0);

		// We know that the first LMS - substring we'll see will always be
		// the one representing the empty suffix, and it will always be at
		// position 0 of suffixOffset.
		lmsNames[guessedSuffixArray[0]] = currentName;
		// Where in the original string was the last LMS suffix we checked ?
		int lastLMSSuffixOffset(guessedSuffixArray[0]);

#if _SUFFIX_ARRAY_DEBUG
		showSuffixArray(lmsNames);
#endif

		// For each suffix in the suffix array...
		for (int i(1); i < guessedSuffixArray.size(); ++i) {
			// ...where does this suffix appear in the original string ?
			int suffixOffset(guessedSuffixArray[i]);

			// We only care about LMS suffixes.
			if (!isLMSChar(suffixOffset, type))
				continue;

			// If this LMS suffix starts with a different LMS substring
			// from the last suffix we looked at....
			if (!lmsSubstringsAreEqual(s, lastLMSSuffixOffset, suffixOffset, type)) {
				// ...then it gets a new name
				++currentName;
			}

			// Record the last LMS suffix we looked at.
			lastLMSSuffixOffset = suffixOffset;

			// Store the name of this LMS suffix in lmsNames, in the same
			// place this suffix occurs in the original string.
			lmsNames[suffixOffset] = currentName;
#if _SUFFIX_ARRAY_DEBUG
			showSuffixArray(lmsNames);
#endif
		}

		// Now lmsNames contains all the characters of the suffix string in
		// the correct order, but it also contains a lot of unused indexes
		// we don't care about and which we want to remove. We also take
		// this opportunity to build summarySuffixOffsets, which tells
		// us which LMS - suffix each item in the summary string represents.
		// This will be important later.
		for (int i(0); i < lmsNames.size(); ++i) {
			if (lmsNames[i] == -1)
				continue;
			summarySuffixOffsets.push_back(i);
			summaryString.push_back(lmsNames[i]);
		}

		// The alphabetically smallest character in the summary string
		// is numbered zero, so the total number of characters in our
		// alphabet is one larger than the largest numbered character.
		summaryAlphabetSize = currentName + 1;
	}

	std::vector<int> static makeSummarySuffixArray(const std::vector<int>& summaryString, int summaryAlphabetSize) {

		std::vector<int> summarySuffixArray;

		if (summaryAlphabetSize == summaryString.size()) {
			//Every character of this summary string appears once and only
			//once, so we can make the suffix array with a bucket sort.
			summarySuffixArray.resize(summaryString.size() + 1, -1);
			//Always include the empty suffix at the beginning.
			summarySuffixArray[0] = summaryString.size();

			for (int x(0); x < summaryString.size(); ++x) {
				int y = summaryString[x];
				summarySuffixArray[y + 1] = x;
			}
		}
		else {
			//This summary string is a little more complex, so we'll have
			//to use recursion.
			summarySuffixArray = makeSuffixArrayByInducedSorting(
				summaryString,
				summaryAlphabetSize);
		}

		return summarySuffixArray;
	}

	std::vector<int> static accurateLMSSort(const std::vector<int>& s, std::vector<int> bucketTails, const std::vector<bool>& type,
		const std::vector<int>& summarySuffixArray, const std::vector<int>& summarySuffixOffsets) {
		// A suffix for every character, plus the empty suffix.
		std::vector<int> suffixOffsets(s.size() + 1, -1);

		// As before, we'll be adding suffixes to the ends of their
		// respective buckets, so to keep them in the right order we'll
		// have to iterate through summarySuffixArray in reverse order.

		for (int i(summarySuffixArray.size() - 1); i > 1; --i) {
			int stringIndex(summarySuffixOffsets[summarySuffixArray[i]]);

			// Which bucket does this suffix go into ?
			int bucketIndex(s[stringIndex]);
			// Add the suffix at the tail of the bu cket...
			suffixOffsets[bucketTails[bucketIndex]] = stringIndex;
			// ...and move the tail pointer down.
			--bucketTails[bucketIndex];

#if _SUFFIX_ARRAY_DEBUG
			showSuffixArray(suffixOffsets);
#endif
		}
		// Always include the empty suffix at the beginning.
		suffixOffsets[0] = s.size();

#if _SUFFIX_ARRAY_DEBUG
		showSuffixArray(suffixOffsets);
#endif

		return suffixOffsets;
	}

#if _SUFFIX_ARRAY_DEBUG
	void static showSuffixArray(const std::vector<int>& arr) {
		std::copy(arr.begin(), arr.end(), std::ostream_iterator<int>(std::cout, " "));
		std::cout << "\n";
	}
#endif
};

int main() {
    ios::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);

    string s;
    char c(getchar_unlocked());
    int i, j, k;
    vector<size_t> v;
    while (c != EOF && c != '1') {
        s = "";
        while (c != '\n') {
            s += c;
            c = getchar_unlocked();
        }

        suffixsorting ss(s, &v);

        fastScan(j);
        for (k = 0; k < j; ++k) {
            fastScan(i);
            printf("%zu ", ss.getSuffix(i));
        }
        printf("\n");
        c = getchar_unlocked();
    }

    return 0;
}

/*
4 5 0 3
0 1 10
1 2 1
1 3 1
0 2 1
2 3 10
*/


class SuffixArray {
#ifndef _SUFFIX_ARRAY_DEBUG
#define _SUFFIX_ARRAY_DEBUG 0
#endif
#ifndef MINBUCKETSIZE
# define MINBUCKETSIZE 256
#endif
	//http://zork.net/~st/jottings/sais.html
public:

	std::vector<int> static createSA(const std::string& s) {
		std::vector<int> t(s.begin(), s.end());
		return sais_main(t, 0, 256);
	}

private:
	/* find the start or end of each bucket */
	static std::vector<int>
		getCounts(const std::vector<int>& T, int alphabetSize) {
		int i;
		std::vector<int> C(alphabetSize);
		for (i = 0; i < T.size(); ++i) ++C[T[i]];
	}

	static std::vector<int>
		getBuckets(const std::vector<int>& C, int alphabetSize, bool end) {
		std::vector<int> B(alphabetSize);
		int i(0), sum(0);
		if (end)
			for (; i < alphabetSize; ++i) {
				sum += C[i];
				B[i] = sum;
			}
		else
			for (; i < alphabetSize; ++i) {
				sum += C[i];
				B[i] = sum - C[i];
			}
		return B;
	}

	static void
		LMSsort2(const std::vector<int>& T, std::vector<int>& SA,
			const std::vector<int>& C, std::vector<int>& D,
			int alphabetSize) {
		sais_index_type *b, i, j, t, d;
		sais_index_type c0, c1;
		assert(C != B);

		/* compute SAl */
		getBuckets(C, B, k, 0); /* find starts of buckets */
		j = n - 1;
		b = SA + B[c1 = chr(j)];
		--j;
		t = (chr(j) < c1);
		j += n;
		*b++ = (t & 1) ? ~j : j;
		for (i = 0, d = 0; i < n; ++i) {
			if (0 < (j = SA[i])) {
				if (n <= j) { d += 1; j -= n; }
				assert(chr(j) >= chr(j + 1));
				if ((c0 = chr(j)) != c1) { B[c1] = b - SA; b = SA + B[c1 = c0]; }
				assert(i < (b - SA));
				--j;
				t = c0; t = (t << 1) | (chr(j) < c1);
				if (D[t] != d) { j += n; D[t] = d; }
				*b++ = (t & 1) ? ~j : j;
				SA[i] = 0;
			}
			else if (j < 0) {
				SA[i] = ~j;
			}
		}
		for (i = n - 1; 0 <= i; --i) {
			if (0 < SA[i]) {
				if (SA[i] < n) {
					SA[i] += n;
					for (j = i - 1; SA[j] < n; --j) {}
					SA[j] -= n;
					i = j;
				}
			}
		}

		/* compute SAs */
		getBuckets(C, B, k, 1); /* find ends of buckets */
		for (i = n - 1, d += 1, b = SA + B[c1 = 0]; 0 <= i; --i) {
			if (0 < (j = SA[i])) {
				if (n <= j) { d += 1; j -= n; }
				assert(chr(j) <= chr(j + 1));
				if ((c0 = chr(j)) != c1) { B[c1] = b - SA; b = SA + B[c1 = c0]; }
				assert((b - SA) <= i);
				--j;
				t = c0; t = (t << 1) | (chr(j) > c1);
				if (D[t] != d) { j += n; D[t] = d; }
				*--b = (t & 1) ? ~(j + 1) : j;
				SA[i] = 0;
			}
		}
	}

	/* find the suffix array SA of T[0..n-1] in {0..255}^n */
	std::vector<int> static sais_main(const std::vector<int>& T, int fs,
		int alphabetSize) {
		int n(T.size());
		std::vector<int> RA;
		int i, j, m, p, q, name, pidx(0), newfs;
		int c0, c1;
		unsigned int flags;

		flags = 3;

		if ((2 * alphabetSize <= n)) {
			flags |= ((alphabetSize * 2) <= (fs - alphabetSize)) ? 32 : 16;
		}

		/* stage 1: reduce the problem by at least 1/2
		sort all the LMS-substrings */
		std::vector<int> C(getCounts(T, alphabetSize));
		std::vector<int> B(getBuckets(C, alphabetSize, 1)); /* find ends of buckets */
		std::vector<int> SA(T.size());
		int b(0);
		i = n - 1; j = n; m = 0; c0 = T[n - 1];

		do { c1 = c0; } while ((0 <= --i) && ((c0 = T[i]) >= c1));

		for (; 0 <= i;) {
			do { c1 = c0; } while ((0 <= --i) && ((c0 = T[i]) <= c1));
			if (0 <= i) {
				SA[b] = j; b = --B[c1]; j = i; ++m;
				do { c1 = c0; } while ((0 <= --i) && ((c0 = T[i]) >= c1));
			}
		}

		if (1 < m) {
			if (flags & (16 | 32)) {
				std::vector<int> D(alphabetSize * 2);
				++B[T[j + 1]];
				for (i = 0, j = 0; i < alphabetSize; ++i) {
					j += C[i];
					if (B[i] != j)
						SA[B[i]] += n;
					D[i] = D[i + alphabetSize] = 0;
				}
				LMSsort2(T, SA, C, B, D, n, alphabetSize, cs);
				name = LMSpostproc2(SA, n, m);
				if (flags & 16) { SAIS_MYFREE(D, alphabetSize * 2, sais_index_type); }
			}
			else {
				LMSsort1(T, SA, C, B, n, alphabetSize, cs);
				name = LMSpostproc1(T, SA, n, m, cs);
			}
		}
		else if (m == 1) {
			*b = j + 1;
			name = 1;
		}
		else {
			name = 0;
		}

		/* stage 2: solve the reduced problem
		recurse if names are not yet unique */
		if (name < m) {
			if (flags & 4) { SAIS_MYFREE(C, alphabetSize, sais_index_type); }
			if (flags & 2) { SAIS_MYFREE(B, alphabetSize, sais_index_type); }
			newfs = (n + fs) - (m * 2);
			if ((flags & (1 | 4 | 8)) == 0) {
				if ((alphabetSize + name) <= newfs) { newfs -= alphabetSize; }
				else { flags |= 8; }
			}
			assert((n >> 1) <= (newfs + m));
			RA = SA + m + newfs;
			for (i = m + (n >> 1) - 1, j = m - 1; m <= i; --i) {
				if (SA[i] != 0) {
					RA[j--] = SA[i] - 1;
				}
			}
			if (sais_main(RA, SA, newfs, m, name, sizeof(sais_index_type), 0) != 0) {
				if (flags & 1) { SAIS_MYFREE(C, alphabetSize, sais_index_type); }
				return -2;
			}

			i = n - 1; j = m - 1; c0 = chr(n - 1);
			do { c1 = c0; } while ((0 <= --i) && ((c0 = chr(i)) >= c1));
			for (; 0 <= i;) {
				do { c1 = c0; } while ((0 <= --i) && ((c0 = chr(i)) <= c1));
				if (0 <= i) {
					RA[j--] = i + 1;
					do { c1 = c0; } while ((0 <= --i) && ((c0 = chr(i)) >= c1));
				}
			}
			for (i = 0; i < m; ++i) { SA[i] = RA[SA[i]]; }
			if (flags & 4) {
				if ((C = B = SAIS_MYMALLOC(alphabetSize, int)) == NULL) { return -2; }
			}
			if (flags & 2) {
				if ((B = SAIS_MYMALLOC(alphabetSize, int)) == NULL) {
					if (flags & 1) { SAIS_MYFREE(C, alphabetSize, sais_index_type); }
					return -2;
				}
			}
		}

		/* stage 3: induce the result for the original problem */
		if (flags & 8) { getCounts(T, C, n, alphabetSize, cs); }
		/* put all left-most S characters into their buckets */
		if (1 < m) {
			getBuckets(C, B, alphabetSize, 1); /* find ends of buckets */
			i = m - 1, j = n, p = SA[m - 1], c1 = chr(p);
			do {
				q = B[c0 = c1];
				while (q < j) { SA[--j] = 0; }
				do {
					SA[--j] = p;
					if (--i < 0) { break; }
					p = SA[i];
				} while ((c1 = chr(p)) == c0);
			} while (0 <= i);
			while (0 < j) { SA[--j] = 0; }
		}
		if (isbwt == 0) { induceSA(T, SA, C, B, n, alphabetSize, cs); }
		else { pidx = computeBWT(T, SA, C, B, n, alphabetSize, cs); }
		if (flags & (1 | 4)) { SAIS_MYFREE(C, alphabetSize, sais_index_type); }
		if (flags & 2) { SAIS_MYFREE(B, alphabetSize, sais_index_type); }

		return pidx;
	}
};
