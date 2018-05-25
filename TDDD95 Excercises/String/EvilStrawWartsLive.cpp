//https://liu.kattis.com/problems/evilstraw
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
#include <iomanip>
#include <fstream>
//#include <bits/stdc++.h>

using namespace std;

//https://www.geeksforgeeks.org/fast-io-for-competitive-programming/
template<typename T>
void fastScan(T &number)
{
    //variable to indicate sign of input number
    bool negative = false;
    register T c;

    number = 0;

    // extract current character from buffer
    c = getchar();
    while (!(c == '-' || (c > 47 && c < 58)))
        c = getchar();

    if (c == '-')
    {
        // number is negative
        negative = true;

        // extract the next character from the buffer
        c = getchar();
    }

    // Keep on extracting characters if they are integers
    // i.e ASCII Value lies from '0'(48) to '9' (57)
    for (; (c>47 && c<58); c = getchar())
        number = number * 10 + c - 48;

    // if scanned input has a negative sign, negate the
    // value of the input number
    if (negative)
        number *= -1;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        string S;
        cin >> S;
        int count[26] = { 0 }, odd = 0;
        for (int i = 0; i < S.length(); i++)
            count[S[i] - 'a']++;
        for (int i = 0; i < 26; i++)
            if (count[i] % 2 == 1)
                odd++;
        if ((S.length() % 2 == 0 && odd > 0) || (S.length() % 2 == 1 && odd > 1))
            puts("Impossible");
        else {
            int step = 0;
            for (int i = 0, j = S.length() - 1; i < j; i++, j--) {
                int posL, posR;
                for (posR = j; posR > i; posR--)
                    if (S[i] == S[posR])
                        break;
                for (posL = i; posL < j; posL++)
                    if (S[j] == S[posL])
                        break;
                if (j - posR > posL - i) {
                    step += posL - i;
                    for (int k = posL - 1; k >= i; k--)
                        swap(S[k], S[k + 1]);
                }
                else {
                    step += j - posR;
                    for (int k = posR + 1; k <= j; k++)
                        swap(S[k], S[k - 1]);
                }
            }
            printf("%d\n", step);
        }
    }
    return 0;
}
