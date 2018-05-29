//https://liu.kattis.com/sessions/tgp7wb/problems/peg
#include <iostream>
#include <string>

using namespace std;

int main() {

    const int size{ 7 };
    const int e = 2;
    char m[size + e * 2][size + e * 2];

    int s;

    for (int i = 0; i < 7; ++i) {
        string stri;
        getline(cin, stri);
        for (int j = 0; j < 7; ++j) {
            char t = stri[j];
            if (t == ' ')
                m[i + e][j + e] = 0;
            if (t == 'o')
                m[i + e][j + e] = 1;
            if (t == '.')
                m[i + e][j + e] = -1;
        }
    }

    for (int i = 0; i < 7; ++i)
        for (int j = 0; j < 7; ++j) {
            if (m[i + e][j + e] == -1) {
                if (m[i + e][j + e + 1] == 1 && m[i + e][j + e + 2] == 1) ++s;
                if (m[i + e][j + e - 1] == 1 && m[i + e][j + e - 2] == 1) ++s;
                if (m[i + e + 1][j + e] == 1 && m[i + e + 2][j + e] == 1) ++s;
                if (m[i + e - 1][j + e] == 1 && m[i + e - 2][j + e] == 1) ++s;
            }
        }

    cout << s << endl;

    return 0;
}
