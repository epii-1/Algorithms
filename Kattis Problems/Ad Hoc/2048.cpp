//https://liu.kattis.com/sessions/tgp7wb/problems/2048
#include <iostream>

using namespace std;

struct tile {
    int i;
    bool m{ false };
};


int main() {

    ios::sync_with_stdio(NULL);
    const int s = 4;
    tile m[s][s];
    int move;
    bool moved = true;

    cin >> m[0][0].i >> m[0][1].i >> m[0][2].i >> m[0][3].i;
    cin >> m[1][0].i >> m[1][1].i >> m[1][2].i >> m[1][3].i;
    cin >> m[2][0].i >> m[2][1].i >> m[2][2].i >> m[2][3].i;
    cin >> m[3][0].i >> m[3][1].i >> m[3][2].i >> m[3][3].i;
    cin >> move;

    while (moved) {
        moved = false;
        switch (move) {
        case 0:
            for (int i = 0; i < s; ++i) {
                for (int j = 0; j < s - 1; ++j)
                    if (m[i][j].i == 0 && m[i][j + 1].i != 0) {
                        m[i][j].i = m[i][j + 1].i;
                        m[i][j + 1].i = 0;
                        m[i][j].m = m[i][j + 1].m;
                        m[i][j + 1].m = false;
                        moved = true;
                    }
                    else if (m[i][j].i == m[i][j + 1].i && !m[i][j].m && !m[i][j + 1].m) {
                        m[i][j].i += m[i][j + 1].i;
                        m[i][j + 1].i = 0;
                        m[i][j].m = true;
                        m[i][j + 1].m = false;
                        moved = true;
                    }
            }
            break;
        case 1:
            for (int i = 0; i < s - 1; ++i) {
                for (int j = 0; j < s; ++j)
                    if (m[i][j].i == 0 && m[i + 1][j].i != 0) {
                        m[i][j].i = m[i + 1][j].i;
                        m[i + 1][j].i = 0;
                        m[i][j].m = m[i + 1][j].m;
                        m[i + 1][j].m = false;
                        moved = true;
                    }
                    else if (m[i][j].i == m[i + 1][j].i && !m[i][j].m && !m[i + 1][j].m) {
                        m[i][j].i += m[i + 1][j].i;
                        m[i + 1][j].i = 0;
                        m[i][j].m = true;
                        m[i + 1][j].m = false;
                        moved = true;
                    }
            }
            break;
        case 2:
            for (int i = 0; i < s; ++i) {
                for (int j = s - 1; j > 0; --j)
                    if (m[i][j].i == 0 && m[i][j - 1].i != 0) {
                        m[i][j].i = m[i][j - 1].i;
                        m[i][j - 1].i = 0;
                        m[i][j].m = m[i][j - 1].m;
                        m[i][j - 1].m = false;
                        moved = true;
                    }
                    else if (m[i][j].i == m[i][j - 1].i && !m[i][j].m && !m[i][j - 1].m) {
                        m[i][j].i += m[i][j - 1].i;
                        m[i][j - 1].i = 0;
                        m[i][j].m = true;
                        m[i][j - 1].m = false;
                        moved = true;
                    }
            }
            break;
        case 3:
            for (int i = s - 1; i > 0; --i) {
                for (int j = 0; j < s; ++j)
                    if (m[i][j].i == 0 && m[i - 1][j].i != 0) {
                        m[i][j].i = m[i - 1][j].i;
                        m[i - 1][j].i = 0;
                        m[i][j].m = m[i - 1][j].m;
                        m[i - 1][j].m = false;
                        moved = true;
                    }
                    else if (m[i][j].i == m[i - 1][j].i && !m[i][j].m && !m[i - 1][j].m) {
                        m[i][j].i += m[i - 1][j].i;
                        m[i - 1][j].i = 0;
                        m[i][j].m = true;
                        m[i - 1][j].m = false;
                        moved = true;
                    }
            }
            break;
        default:
            throw 0;
        }
    }

    for (int i = 0; i < s; ++i) {
        for (int j = 0; j < s; ++j)
            cout << m[i][j].i << " ";
        cout << "\n";
    }

    cout << endl;

    //system("Pause");
    return 0;
}
