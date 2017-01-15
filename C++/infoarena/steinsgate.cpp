#include <bits/stdc++.h>

using namespace std;

const int NMAX = 210;

int N, M, K;
bool adj[NMAX][NMAX], res[NMAX][NMAX];
int value[NMAX];

void Multiply(bool dest[NMAX][NMAX], bool source[NMAX][NMAX]) {
    bool temp[NMAX][NMAX];
    int i, j, k;

    memset(temp, 0, NMAX * NMAX * sizeof(bool));
    for (i = 1; i <= N; ++i)
        for (j = 1; j <= N; ++j)
            for (k = 1; k <= N; ++k)
                temp[i][k] = max(temp[i][k], bool(dest[i][j] * source[j][k]));

    memcpy(dest, temp, NMAX * NMAX * sizeof(bool));
}

void FastExpo(bool base[NMAX][NMAX], int expo, bool res[NMAX][NMAX]) {
    for (int i = 1; i <= N; ++i)
        res[i][i] = 1;

    while (expo) {
        if (expo & 1)
            Multiply(res, base);
        expo >>= 1;
        Multiply(base, base);
    }
}

int answer[NMAX];

int main() {
	ios_base::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
	assert(freopen("steinsgate.in", "r", stdin) != NULL);
    assert(freopen("steinsgate.out", "w", stdout) != NULL);
    assert(freopen("debug.err", "w", stderr) != NULL);
    #endif

    int i, j, x, y;

    cin >> N >> M >> K;
    for (i = 1; i <= M; ++i) {
        cin >> x >> y;
        adj[x][y] = 1;
    }

    for (i = 1; i <= N; ++i)
        cin >> value[i];

    FastExpo(adj, K, res);

    for (i = 1; i <= N; ++i)
        for (j = 1; j <= N; ++j)
            if (res[i][j])
                answer[j] = max(answer[j], value[i]);

    for (i = 1; i <= N; ++i)
        cout << answer[i] << ' ';
    cout << '\n';

	return 0;
}
