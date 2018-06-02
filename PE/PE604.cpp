/* Let F(N)F(N) be the maximum number of lattice points in an axis - aligned N×NN×N square that the graph of a single strictly convex increasing function can pass through.

You are given that F(1) = 2F(1) = 2, F(3) = 3F(3) = 3, F(9) = 6F(9) = 6, F(11) = 7F(11) = 7, F(100) = 30F(100) = 30 and F(50000) = 1898F(50000) = 1898.
Below is the graph of a function reaching the maximum 3 for N = 3N = 3:

p604_convex3.png
Find F(1018). 

1398582231101
*/

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

bool gcd(unsigned long long a, unsigned long long b);
unsigned long long gcd2(unsigned long long a, unsigned long long b);

int main() {
	unsigned long long r = 1000000000000000000;
	//const int pm = 2145000;
	const int pm = pow(r*10.0, 1/3.0);
	cout << pm << endl;
	//unsigned long long r = 50000;
	vector<vector<int>> p(pm, vector<int>(2));
	for (int i = 2; i < pm; i++) {
		p[i][0] = 2;
		p[i][1] = 1;
	}
	for (int j = 4; j < pm; j += 2) {
		p[j][0] *= 2;
	}
	for (int i = 3; i*2 < pm; i+=2) {
		if (p[i][1] == 1) {
			for (int j = i * 2; j < pm; j += i) {
				p[j][0] *= i;
				p[j][1] *= i - 1;
			}
		}
	}

	cout << r << endl;

	long long s = 1;

	for (long long unsigned i = 3; i <= 2 * r; i++) {
		long long unsigned a = 0;
		bool test = false;
		if (pm > i) {
			a = (i * p[i][1]) / (p[i][0]);
			test = true;
		}
		if (test && r >= a * i) {
			r -= a * i;
			s += a * 2;
		}
		else {
			int t = i / 2 - (i + 1) % 2;
			int j = i / 2 - (i + 1) % 2;
			int k = i - j;
			cout << i << " " << r << endl;
			for (; j > 0; j--, k++) {
				if (!gcd(k, j)) {
					if (r >= i) {
						//cout << k << " " << j << " " << 2 << endl;
						r -= i;
						s += 2;
					}
					else if (r >= k) {
						//cout << k << " " << j << " " << 1 << endl;
						r -= k;
						s++;
						break;
					}
					else
						break;
				}
				else
					t--;
			}
			/*if (i < pm) {
				if ((i * p[i][1]) / (p[i][0]) != t) {
					cout << p[i][1] << " " << p[i][0] << endl;
					cout << (i * p[i][1]) / (p[i][0]) << endl;
					cout << t << " " << i << endl << endl;
				}
			}*/
		}
	}
	if (r >= 1)
		s++;
	cout << s << endl;
	system("Pause");
	return 0;
}


bool gcd(unsigned long long a, unsigned long long b) {
	if (b == 1)
		return false;
	else if (b == 0)
		return true;
	unsigned long long c = a % b;
	a = b;
	b = c;
	c = a - b;
	if (c < b) {
		a = b;
		b = c;
	}
	else 
		a = c;

	return gcd(a, b);
}

unsigned long long gcd2(unsigned long long a, unsigned long long b) {
	if (b == 1)
		return 1;
	else if (b == 0)
		return a;
	//cout << a << " " << b << endl;
	unsigned long long c = a % b;
	a = b;
	b = c;
	c = a - b;
	//cout << a << " " << b << " " << c << endl;
	if (c < b) {
		a = b;
		b = c;
	}
	else
		a = c;

	return gcd2(a, b);
}