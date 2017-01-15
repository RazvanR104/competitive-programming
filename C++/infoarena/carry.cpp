#include <bits/stdc++.h>

using namespace std;

const int MOD = 30211, NMAX = 100010, KMAX = 110;

int N, K;
int DP1[KMAX][2], DP2[KMAX][2];
char num[NMAX];

int main() {
	ios_base::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
	assert(freopen("carry.in", "r", stdin) != NULL);
    assert(freopen("carry.out", "w", stdout) != NULL);
    assert(freopen("debug.err", "w", stderr) != NULL);
    #endif

    cin >> N >> K;
    int i, j;

    cin >> (num + 1);

    for (i = 1; i <= N; ++i)
        num[i] -= '0';
    reverse(num + 1, num + N + 1);

    DP1[0][0] = 10 - num[1];
    DP1[1][1] = num[1];
    for (i = 2; i < N; ++i) {
        for (j = 0; j <= K; ++j) {
            DP2[j][0] = (DP1[j][0] * (10 - num[i]) + DP1[j][1] * (9 - num[i])) % MOD;
            if (j)
                DP2[j][1] = (DP1[j - 1][0] * num[i] + DP1[j - 1][1] * (num[i] + 1)) % MOD;
        }
        memcpy(DP1, DP2, sizeof(DP1));
        //memset(DP2, 0, sizeof(DP2));
    }

    DP2[K][0] = (DP1[K][0] * (max(9 - num[N], 0)) + DP1[K][1] * (max(8 - num[N], 0))) % MOD;
    DP2[K][1] = (DP1[K - 1][0] * num[N] + DP1[K - 1][1] * (num[N] + 1)) % MOD;

    cout << (DP2[K][0] + DP2[K][1]) % MOD << '\n';
	return 0;
}
