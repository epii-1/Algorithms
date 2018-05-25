//https://liu.kattis.com/sessions/tgp7wb/problems/coke
//Should be using dp instead
#include <iostream>
#include <vector>

using namespace std;

int main() {

    ios::sync_with_stdio(NULL);

    int n;
    cin >> n;
    const int c = 8;

    vector<int> a;
    vector<int> e;
    vector<int> f;
    vector<int> t;


    for (int i = 0; i < n; ++i) {
        int a1, e1, f1, t1;
        cin >> a1 >> e1 >> f1 >> t1;
        a.push_back(a1);
        e.push_back(e1);
        f.push_back(f1);
        t.push_back(t1);
    }

    for (int i = 0; i < n; ++i) {
        int s = 0;
        for (int j = 0; j < a[i]; ++j) {
            if (t[i] > 0) {
                --t[i];
                ++s;
            }
            else if (f[i] > 1 && i + 1 == a[i]) {
                f[i] -= 2;
                s += 2;
            }
            else if (f[i] > 2) {
                --f[i];
                s += 4;
            }
            else {
                s += 8;
            }
        }

        cout << "\n" << s << "\n";
    }

    cout << endl;


    return 0;
}
