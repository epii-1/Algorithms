//https://liu.kattis.com/sessions/tgp7wb/problems/cold
#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(NULL);

    int m;

    cin >> m;

    int s = 0;

    for (int i = 0; i < m; ++i) {
        int t;
        cin >> t;
        if (t < 0)
            ++s;
    }

    cout << s << endl;
    return 0;
}
