#include <bits/stdc++.h>

using namespace std;

const int M = 200, ALPHABET_SIZE = 30;

int r, m;
char rd1[M], rd2[M];
int go1[ALPHABET_SIZE], go2[ALPHABET_SIZE][ALPHABET_SIZE], DP[M][M];

int main() {
    assert(freopen("minerale.in", "r", stdin));
    assert(freopen("minerale.out", "w", stdout));

    int i, j, k;

    cin >> r >> m;
    cin.ignore(1);
    for (i = 1; i <= r; ++i) {
        cin >> rd1 >> rd2;
        if (rd2[0] >= 'a' && rd2[0] <= 'z')
            go1[rd2[0] - 'a'] |= (1 << (rd1[0] - 'A'));
        else
            go2[rd2[0] - 'A'][rd2[1] - 'A'] |= (1 << (rd1[0] - 'A'));
    }

    while (m--) {
        cin >> (rd1 + 1);
        int len = strlen(rd1 + 1);
        for (i = 1; i <= len; ++i)
            DP[i][i] = go1[rd1[i] - 'a'];

        for (i = 1; i < len; ++i) {
            for (j = 1; j + i <= len; ++j) {
                for (k = j; k < j + i; ++k) {
                    for (int bit1 = 0; bit1 < ALPHABET_SIZE; ++bit1) {
                        if ((DP[j][k] & (1 << bit1)) == 0)
                            continue;
                        for (int bit2 = 0; bit2 < ALPHABET_SIZE; ++bit2) {
                            if ((DP[k + 1][j + i] & (1 << bit2)) == 0)
                                continue;
                            DP[j][j + i] |= go2[bit1][bit2];
                        }
                    }
                }
            }
        }

        if (DP[1][len] == 0)
            cout << "0\n";
        else if (DP[1][len] & (1 << ('S' - 'A')))
            cout << "1\n";
        else
            cout << "2\n";

        memset(DP, 0, sizeof DP);

    }

    return 0;
}
