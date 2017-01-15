#include <bits/stdc++.h>

using namespace std;

const int NMAX = 100010, SMAX = 20;
typedef int64_t i64;

int N, M, pos, psz;
int P[NMAX], special[SMAX], where[NMAX];
i64 DP[2][NMAX], DPL[NMAX][2][2], c[2][NMAX];
bool seen[NMAX], notok[SMAX][SMAX];
vector<int> G[NMAX], L[NMAX], path[NMAX];

void Path(int node, int pos, int lol) {
    path[pos].push_back(node);
    seen[node] = 1;
    int _node = node;

    while (1) {
        int next = -1;
        for (const int &it : L[node])
            if (seen[it] == 0) {
                next = it;
                break;
            }

        if (next == -1)
            break;

        seen[next] = 1;
        path[pos].push_back(next);
        node = next;
    }

    c[0][pos] = lol + 1;
    for (const int &it : G[_node])
        if (G[it].size() > 2)
            c[0][pos] = where[it];

    c[1][pos] = lol + 1;
    for (const int &it : G[path[pos].back()])
        if (G[it].size() > 2 && it != c[0][pos])
            c[1][pos] = where[it];
}

int main() {
	ios_base::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
	assert(freopen("metrou2.in", "r", stdin) != NULL);
    assert(freopen("metrou2.out", "w", stdout) != NULL);
    assert(freopen("debug.err", "w", stderr) != NULL);
    #endif

    cin >> N >> M;

    int i, j, x, y, k;
    for (i = 1; i <= N; ++i)
        cin >> P[i];

    for (i = 1; i <= M; ++i) {
        cin >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x);
    }

    int grad2 = 1;

    for (i = 1; i <= N; ++i)
        if (G[i].size() != 2) {
            grad2 = 0;
            break;
        }

    for (i = 1; i <= N; ++i) {
        if (G[i].size() >= 3) {
            special[++pos] = i;
            where[i] = pos;
        }
    }

    for (i = 1; i <= N; ++i) {
        if (G[i].size() >= 3)
            continue;
        for (const auto &it : G[i]) {
            if (G[it].size() >= 3)
                continue;
            L[i].push_back(it);
        }
    }

    if (grad2) {
        Path(1, 1, 0);
        DP[0][1] = P[path[1][0]];
        for (j = 1; j < int(path[1].size()); ++j) {
            DP[0][j + 1] = max(DP[0][j], DP[0][j - 1] + P[path[1][j]]);
            DP[1][j + 1] = max(DP[1][j], DP[1][j - 1] + P[path[1][j]]);
        }

        cout << max(DP[0][path[1].size() - 1], max(DP[1][path[1].size()], DP[1][path[1].size() - 1])) << '\n';
        return 0;
    }

    for (i = 1; i <= N; ++i)
        if (L[i].size() <= 1 && G[i].size() <= 2 && seen[i] == 0)
            Path(i, ++psz, pos);

    for (i = 1; i <= psz; ++i) {
        DP[0][1] = P[path[i][0]];
        for (j = 1; j < int(path[i].size()); ++j) {
            DP[0][j + 1] = max(DP[0][j], DP[0][j - 1] + P[path[i][j]]);
            DP[1][j + 1] = max(DP[1][j], DP[1][j - 1] + P[path[i][j]]);
        }

        DPL[i][0][0] = DP[0][path[i].size()];
        DPL[i][0][1] = DP[0][path[i].size() - 1];
        DPL[i][1][0] = DP[1][path[i].size()];
        DPL[i][1][1] = DP[1][path[i].size() - 1];
    }

    for (i = 1; i <= pos; ++i) {
        for (const int &it : G[special[i]]) {
            if (where[it] == 0)
                continue;
            notok[i][where[it]] = notok[where[it]][i] = 1;
        }
    }

    i64 answer = 0;

    for (i = 0; i < (1 << pos); ++i) {
        i64 now = 0;
        for (j = 0; j < pos; ++j)
            for (k = 0; k < pos; ++k)
                if ((i & (1 << j)) && (i & (1 << k)) && notok[j + 1][k + 1])
                    goto Continue;

        for (j = 0; j < pos; ++j) {
            if ((i & (1 << j)))
                now += P[special[j + 1]];
        }

        for (j = 1; j <= psz; ++j) {
            int c0 = c[0][j] - 1, c1 = c[1][j] - 1;
            if (path[j].size() == 1) {
                if (c0 == c1) {
                    if (((i >> c0) & 1))
                        continue;
                    now += P[path[j][0]];
                } else {
                    if (((i >> c0) & 1) == 0 && ((i >> c1) & 1) == 0)
                        now += P[path[j][0]];
                }
                continue;
            }
            now += DPL[j][(i >> c0) & 1][(i >> c1) & 1];
        }

        if (answer < now)
            answer = now;

        Continue: continue;
    }

    cout << answer << '\n';
	return 0;
}
