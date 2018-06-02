/*
Let H(n) be the number of distinct integer sided equiangular convex hexagons with perimeter not exceeding n.
Hexagons are distinct if and only if they are not congruent.

You are given H(6) = 1, H(12) = 10, H(100) = 31248.
Find H(55106).

*/

#include <iostream>

using namespace std;

int main() {
	long long sum = 0;
	int n = 55106;
	int maxSquare = (n - 3) / 3;

	for (int i = 1; i <= maxSquare; i++) {
		int nrShapes = (i + 1) / 2;
		int t = i % 2;
		for (int j = i * 3 + 3; j <= n && nrShapes > 0; j++, nrShapes -= t, t = (t + 1) % 2)
			sum += ((n - j) / 2) * nrShapes + nrShapes;
	}

	cout << sum << endl;
	system("Pause");
	return 0;
}
