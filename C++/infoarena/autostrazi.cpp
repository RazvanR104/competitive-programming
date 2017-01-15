#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>

#define pb push_back

using namespace std;

const int NMAX = 110, KMAX = 25;

int N, S, K;
int A[KMAX], DP[NMAX][NMAX], temp[NMAX], MOD = 30011;
vector<int> G[NMAX];

void DFS(int node, int from) {
    if (G[node].size() == 1) {
        DP[node][0] = 1;
        return;
    }

    DP[node][0] = 1;
    for (int itt = 0; itt < int(G[node].size()); ++itt) {
        int it = G[node][itt];
        if (it == from)
            continue;
        DFS(it, node);
        memset(temp, 0, sizeof(temp));
        int i, j, k;
        for (i = 0; i <= S; ++i) {
            for (j = 0; j + i <= S; ++j) {
                for (k = 1; k <= K; ++k) {
                    if (i + j + A[k] > S)
                        continue;
                    temp[max(i, j + A[k])] = (temp[max(i, j + A[k])] + DP[node][i] * DP[it][j]) % MOD;
                }
                temp[max(i, j)] = (temp[max(i, j)] + DP[node][i] * DP[it][j]) % MOD;
            }
        }
        memcpy(DP[node], temp, sizeof(DP[node]));
    }
}

int main() {
	ios_base::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
    freopen("autostrazi.in", "r", stdin);
    freopen("autostrazi.out", "w", stdout);
	freopen("debug.err", "w", stderr);
    #endif

    int i, j;
    cin >> N >> S >> K;

    for (i = 1; i <= K; ++i)
        cin >> A[i];

    for (i = 1; i < N; ++i) {
        int x, y;
        cin >> x >> y;
        G[x].pb(y);
        G[y].pb(x);
    }

    int root = 1;
    while (G[root].size() <= 1)
        ++root;
    DFS(root, -1);

    int answer = 0;
    for (i = 0; i <= S; ++i)
        answer = (answer + DP[root][i]) % MOD;

    cout << answer << '\n';

	return 0;
}
