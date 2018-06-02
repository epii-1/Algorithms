/*
For every positive number nn we define the function streak(n)=kstreak(n)=k as the smallest positive integer kk such that n+kn+k is not divisible by k+1k+1.
E.g:
13 is divisible by 1
14 is divisible by 2
15 is divisible by 3
16 is divisible by 4
17 is NOT divisible by 5
So streak(13)=4streak(13)=4.
Similarly:
120 is divisible by 1
121 is NOT divisible by 2
So streak(120)=1streak(120)=1.

Define P(s,N)P(s,N) to be the number of integers nn, 1<n<N1<n<N, for which streak(n)=sstreak(n)=s.
So P(3,14)=1P(3,14)=1 and P(6,106)=14286P(6,106)=14286.

Find the sum, as ii ranges from 1 to 31, of P(i,4i)P(i,4i).

1617243
*/

#include <iostream>
#include <vector>
#include "BigIntegerLibrary.hh"


using namespace std;

BigInteger gcd(BigInteger a, BigInteger b);

int main() {
	BigInteger sum = -1;
	const int max = 32;
	char p[max+10];
	vector<int> pi;
	pi.push_back(2);
	for (int i = 3; i <= max+10; i += 2) 
		p[i] = 1;
	for (int i = 3; i*i <= max+10; i += 2) {
		if (p[i]) {
			for (int j = i*i; j <= max+10; j += i + i) {
				p[j] = 0;
			}
		}
	}
	for (int i = 3; i <= max+10; i += 2) {
		if (p[i]) {
			pi.push_back(i);
			cout << i << endl;
		}
	}


	BigInteger a2 = 1;

	for (int i = 1; i < max; i++) {
		a2 *= 4;
		BigInteger a = a2-1;
		BigInteger b = 1;
		for (int j = 0; pi[j] <= i; j++) {
			int c = pi[j];
			while (c * pi[j] <= i) {
				c *= pi[j];
			}
			b *= c;
		}
		BigInteger d = i + 1;
		if (b%d != 0) {
			d = d / gcd(b, d);
			sum += a / b - a / (b*d);
		}

	}
	cout << sum << endl;

	system("Pause");
	return 0;
}

BigInteger gcd(BigInteger a, BigInteger b) {
	if (a < b) {
		BigInteger c = a;
		a = b;
		b = c;
	}
	if (a % b == 0)
		return b;
	if (b == 1)
		return 1;
	if(a-(a/b)*b > b)
		return gcd(a - (a / b)*b, b);
	else
		return gcd(b, a - (a / b)*b);
}