#include <bits/stdc++.h>

using namespace std;

const int LMAX = 30010, NMAX = 18, MOD1 = 666013, MOD2 = 666019, M = 101, inf = 0x3f3f3f3f;

int N;
int L1[NMAX][LMAX], L2[NMAX][LMAX], pw1[LMAX], pw2[LMAX], len[NMAX];
int C[NMAX][NMAX], DP[1 << NMAX][NMAX];
pair<int, int> from[1 << NMAX][NMAX];
char S[NMAX][LMAX];

pair<int, int> ComputeHash(int i, int left, int right) {
    int h1 = L1[i][right] - 1ll * pw1[right - left + 1] * L1[i][left - 1] % MOD1;
    if (h1 < 0) h1 += MOD1;
    int h2 = L2[i][right] - 1ll * pw2[right - left + 1] * L2[i][left - 1] % MOD2;
    if (h2 < 0) h2 += MOD2;
    return {h1, h2};
}

bool Check(int i, int j, int pos) {
    if (L1[i][pos] == -1 || L1[j][pos] == -1)
        return 0;

    return ComputeHash(i, len[i] - pos + 1, len[i]) == ComputeHash(j, 1, pos);
}

int main() {
	ios_base::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
	assert(freopen("adn.in", "r", stdin) != NULL);
    assert(freopen("adn.out", "w", stdout) != NULL);
    assert(freopen("debug.err", "w", stderr) != NULL);
    #endif

    int i, j, k;

    memset(L1, -1, sizeof(L1));
    memset(L2, -1, sizeof(L2));

    int maxlen = 0;

    cin >> N;
    for (i = 0; i < N; ++i) {
        cin >> (S[i] + 1);

        L1[i][0] = L2[i][0] = 0;
        len[i] = strlen(S[i] + 1);
        maxlen = max(maxlen, len[i]);
        for (j = 1; j <= len[i]; ++j) {
            L1[i][j] = (1ll * L1[i][j - 1] * M + S[i][j]) % MOD1;
            L2[i][j] = (1ll * L2[i][j - 1] * M + S[i][j]) % MOD2;
        }
    }

    pw1[0] = pw2[0] = 1;
    for (i = 1; i <= maxlen; ++i) {
        pw1[i] = 1ll * pw1[i - 1] * M % MOD1;
        pw2[i] = 1ll * pw2[i - 1] * M % MOD2;
    }

    for (i = 0; i < N; ) {
        for (j = 0; j < N; ++j) {
            if (i == j) continue;
            for (k = 1; k + len[i] - 1 <= len[j]; ++k) {
                if (ComputeHash(i, 1, len[i]) == ComputeHash(j, k, k + len[i] - 1)) {
                    memcpy(S[i], S[N - 1], sizeof(S[i]));
                    memcpy(L1[i], L1[N - 1], sizeof(L1[i]));
                    memcpy(L2[i], L2[N - 1], sizeof(L2[i]));
                    len[i] = len[N - 1];
                    --N;
                    goto Continue;
                }
            }
        }

        ++i;
        Continue:;
    }

    for (i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j) {
            if (i == j)
                continue;

            for (k = 1; k <= min(len[i], len[j]); ++k)
                if (Check(i, j, k))
                    C[i][j] = k;

            C[i][j] = len[j] - C[i][j];
        }
    }

    int min_global = inf;
    vector<int> answer;
    memset(DP, inf, sizeof(DP));

    for (i = 0; i < N; ++i)
        DP[1 << i][i] = len[i];

    for (i = 0; i < (1 << N); ++i) {
        for (j = 0; j < N; ++j) {
            if (i & (1 << j)) {
                for (k = 0; k < N; ++k) {
                    if (j != k && (i & (1 << k))) {
                        if (DP[i][j] > DP[i ^ (1 << j)][k] + C[k][j]) {
                            DP[i][j] = DP[i ^ (1 << j)][k] + C[k][j];
                            from[i][j] = {i ^ (1 << j), k};
                        }
                    }
                }
            }
        }
    }

    int mask = (1 << N) - 1, node = 0;
    for (i = 1; i < N; ++i)
        if (DP[mask][node] > DP[mask][i])
            node = i;

    if (DP[mask][node] < min_global) {
        min_global = DP[mask][node];
        answer.clear();

        while (mask) {
            answer.push_back(node);
            tie(mask, node) = from[mask][node];
        }
    }

    reverse(answer.begin(), answer.end());
    cout << (S[answer[0]] + 1);
    for (i = 1; i < int(answer.size()); ++i)
        cout << (S[answer[i]] - C[answer[i - 1]][answer[i]] + len[answer[i]] + 1);
    cout << '\n';

	return 0;
}
