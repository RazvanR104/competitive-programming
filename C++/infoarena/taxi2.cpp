#include <bits/stdc++.h>

#define pb push_back
#define mp make_pair
#define st first
#define nd second

using namespace std;

const int NMAX = 1010, MOD = 1e9 + 7;

int N, M;
int level[NMAX], stree[NMAX], fact[NMAX], ifact[NMAX], P[NMAX][2 * NMAX];
int DP[2 * NMAX];
bool seen[NMAX];
vector<pair<int, int>> G[NMAX];

int FastPow(int base, int expo) {
    int res = 1;
    while (expo) {
        if (expo & 1)
            res = (1LL * res * base) % MOD;
        base = (1LL * base * base) % MOD;
        expo >>= 1;
    }
    return res;
}

void DF(int node, int from, int curr) {
    level[node] = curr;
    stree[node] = 1;

    for (const auto &it : G[node]) {
        if (it.first == from)
            continue;
        DF(it.first, node, curr + 1);
        stree[node] += stree[it.first];
    }
}

int Comb(int N, int K) {
    return ((1LL * fact[N] * ifact[K] % MOD) * ifact[N - K]) % MOD;
}

int main() {
	ios_base::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
	assert(freopen("taxi2.in", "r", stdin) != NULL);
    assert(freopen("taxi2.out", "w", stdout) != NULL);
    assert(freopen("debug.err", "w", stderr) != NULL);
    #endif

    int i, j, x, y, c;

    cin >> N >> M;

    fact[0] = 1;
    for (i = 1; i <= N; ++i)
        fact[i] = (1LL * fact[i - 1] * i) % MOD;
    ifact[N] = FastPow(fact[N], MOD - 2);
    for (i = N - 1; i >= 0; --i)
        ifact[i] = (1LL * (i + 1) * ifact[i + 1]) % MOD;

    for (i = 1; i < N; ++i) {
        cin >> x >> y >> c;
        G[x].pb(mp(y, c));
        G[y].pb(mp(x, c));
    }

    DF(1, -1, 1);

    int human, taxi;
    for (human = 0; human <= M; ++human) {
        for (taxi = 0; taxi <= M; ++taxi) {
            int add = min(human, M - taxi) + min(taxi, M - human);
            add = (1LL * add * Comb(M, human)) % MOD;
            add = (1LL * add * Comb(M, taxi)) % MOD;
            DP[human + taxi] += add;
            if (DP[human + taxi] >= MOD)
                DP[human + taxi] -= MOD;
        }
    }

    for (i = 1; i <= N; ++i) {
        P[i][0] = 1;
        for (j = 1; j <= 2 * M; ++j) {
            P[i][j] = (1LL * P[i][j - 1] * i) % MOD;
        }
    }

    int answer = 0;
    for (i = 1; i <= N; ++i) {
        for (const auto &it : G[i]) {
            int lnode = it.st, unode = i;
            if (level[lnode] < level[unode])
                swap(lnode, unode);
            if (seen[lnode]) continue;
            seen[lnode] = 1;
            int lower = stree[lnode];
            int upper = N - lower;
            int cost = it.nd;

            for (j = 1; j <= 2 * M; ++j) {
                int add = cost;
                add = (1LL * add * P[lower][j]) % MOD;
                add = (1LL * add * P[upper][2 * M - j]) % MOD;
                add = (1LL * add * DP[j]) % MOD;
                answer += add;
                if (answer >= MOD)
                    answer -= MOD;
            }
        }
    }

    cout << answer << '\n';
	return 0;
}
