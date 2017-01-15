#include <bits/stdc++.h>

using namespace std;

const int NMAX = 201, MOD = 98999;

int S1[NMAX][NMAX], S2[NMAX][NMAX];

int main() {
	ios_base::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
	assert(freopen("stirling.in", "r", stdin) != NULL);
    assert(freopen("stirling.out", "w", stdout) != NULL);
    assert(freopen("debug.err", "w", stderr) != NULL);
    #endif

    int i, j;

    S1[0][0] = S2[0][0] = S1[1][1] = S2[1][1] = 1;
    for (i = 2; i < NMAX; ++i)
        for (j = 1; j <= i; ++j) {
            S1[i][j] = (S1[i - 1][j - 1] - 1ll * (i - 1) * S1[i - 1][j] % MOD) % MOD;
            S2[i][j] = (S2[i - 1][j - 1] + 1ll * j * S2[i - 1][j] % MOD) % MOD;
        }

    int T;
    for (cin >> T; T; --T) {
        int type, n, m;
        cin >> type >> n >> m;

        if (type == 1)
            cout << S1[n][m] << '\n';
        else
            cout << S2[n][m] << '\n';
    }

	return 0;
}
