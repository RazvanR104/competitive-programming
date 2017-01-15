#include <bits/stdc++.h>

#define pb push_back
#define sz(x) (int(x.size()))

using namespace std;

const int NMAX = 500010, inf = 0x3f3f3f3f;

int N;
int F[2 * NMAX], pos[NMAX], Time[2 * NMAX];
vector<int> P[NMAX];

void Update(int pos, int value, int curr) {
    pos += N;
    for ( ; pos <= 2 * N; pos += pos & -pos) {
        if (Time[pos] != curr) {
            Time[pos] = curr;
            F[pos] = inf;
        }
        F[pos] = min(F[pos], value);
    }
}

int Query(int pos, int curr) {
    pos += N;
    int res = inf;
    for ( ; pos >= 1; pos -= pos & -pos) {
        if (Time[pos] != curr) {
            Time[pos] = curr;
            F[pos] = inf;
        }
        res = min(res, F[pos]);
    }
    return res;
}

int main() {
	ios_base::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
    freopen("mate.in", "r", stdin);
    freopen("mate.out", "w", stdout);
	freopen("debug.err", "w", stderr);
    #endif

    int i, j, value;
    scanf("%d", &N);
    for (i = 1; i <= N; ++i) {
        scanf("%d", &value);
        P[value].pb(i);
        pos[i] = sz(P[value]) - 1;
    }

    int ans = 2;
    for (i = 1; i <= N; ++i) {
        if (sz(P[i]) == 0)
            continue;
        Update(2 - P[i][0] - 1, P[i][0], i);
        for (j = 1; j < sz(P[i]); ++j) {
            int where = Query(2 * (j + 1) - P[i][j], i);
            if (where == inf) {
                Update(2 * (j + 1) - P[i][j] - 1, P[i][j], i);
                continue;
            }
            int zeroes = P[i][j] - where + 1 - (j - pos[where] + 1);
            int possible = P[i][j] - where + 1 + j - pos[where] + 1 - zeroes;
            if (possible > N)
                possible = N;
            ans = max(ans, possible);
            Update(2 * (j + 1) - P[i][j] - 1, P[i][j], i);
        }
    }

    cout << ans << '\n';
	return 0;
}
