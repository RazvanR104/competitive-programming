#include <bits/stdc++.h>

using namespace std;

const int LMAX = 510, inf = 0x3f3f3f3f;

char str[LMAX];
int DP[LMAX][LMAX];

int main() {
	ios_base::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
	assert(freopen("stiva.in", "r", stdin) != NULL);
    assert(freopen("stiva.out", "w", stdout) != NULL);
    assert(freopen("debug.err", "w", stderr) != NULL);
    #endif

    cin >> (str + 1);

    int i, j, k, len = strlen(str + 1);

    for (i = 1; i <= len; ++i)
        DP[i][i] = 3;

    for (i = 1; i < len; ++i) {
        for (j = 1; j + i <= len; ++j) {
            DP[j][j + i] = DP[j][j + i - 1] + 3;

            for (k = j + i - 1; k >= j; --k)
                if (str[j + i] == str[k])
                    DP[j][j + i] = min(DP[j][j + i], DP[j][k] + DP[k + 1][j + i - 1] + 1);
        }
    }

    cout << DP[1][len] << '\n';

	return 0;
}
