#include <bits/stdc++.h>

using namespace std;

const int NMAX = 2010, MOD = 100003;

int p, N;
int DP[NMAX][NMAX];

int main() {
    freopen("fractii2.in", "r", stdin);
    freopen("fractii2.out", "w", stdout);

    int i, j, k;

    cin >> p >> N;
    if (p == 1) {
        for (i = 1; i < N; ++i)
            cout << i << ' ';
        cout << N - 1 << '\n';
        return 0;
    }

    DP[2][2] = 1;
    for (i = 3; i <= N; ++i) {
        for (j = 1; j <= i; ++j) {
            DP[i][j] = DP[i][j - 1];
            if (j % 2)
                continue;
            DP[i][j] += DP[i - j / 2][i - j / 2];
            if (DP[i][j] >= MOD)
                DP[i][j] -= MOD;
            DP[i][j] -= DP[i - j / 2][j / 2 - 1];
            if (DP[i][j] < 0)
                DP[i][j] += MOD;
        }
    }

    cout << DP[N][N] << '\n';
    return 0;
}
