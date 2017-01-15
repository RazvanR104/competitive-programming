#include <bits/stdc++.h>

#define pb push_back

using namespace std;

const int NMAX = 210;

int NS, NI, NM, NR, NC;
int nM[NMAX], nS[NMAX], nR[NMAX], nI[NMAX], nC[NMAX];
char F[10 * NMAX][10 * NMAX], Cap[10 * NMAX][10 * NMAX];
int father[10 * NMAX];
bool vis[10 * NMAX];
vector<int> M[NMAX], RS[NMAX], RI[NMAX], C[NMAX], G[10 * NMAX];

bool BFS(int source, int sink) {
    queue<int> Q;
    Q.push(source);
    memset(father, 0, sizeof(father));
    memset(vis, 0, sizeof(vis));
    vis[source] = 1;

    while (!Q.empty()) {
        int now = Q.front();
        Q.pop();

        if (now == sink) {
            while (sink) {
                ++F[father[sink]][sink];
                --F[sink][father[sink]];
                sink = father[sink];
            }
            return 1;
        }

        for (const auto &it : G[now]) {
            if (vis[it])
                continue;
            if (Cap[now][it] - F[now][it] > 0) {
                Q.push(it);
                vis[it] = 1;
                father[it] = now;
            }
        }
    }

    return 0;
}

int main() {
	ios_base::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
	assert(freopen("politia.in", "r", stdin) != NULL);
    assert(freopen("politia.out", "w", stdout) != NULL);
    assert(freopen("debug.err", "w", stderr) != NULL);
    #endif

    int i;

    int source = 1, sink = 2;
    cin >> NS >> NI >> NM >> NR >> NC;

    for (i = 1; i <= NM; ++i) {
        nM[i] = sink;
        sink += 2;
    }
    for (i = 1; i <= NS; ++i) {
        nS[i] = sink;
        sink += 2;
    }
    for (i = 1; i <= NR; ++i) {
        nR[i] = sink;
        sink += 2;
    }
    for (i = 1; i <= NI; ++i) {
        nI[i] = sink;
        sink += 2;
    }
    for (i = 1; i <= NC; ++i) {
        nC[i] = sink;
        sink += 2;
    }

    for (i = 1; i <= NS; ++i) {
        int lim, value;
        cin >> lim;
        while (lim--) {
            cin >> value;
            M[i].pb(value);
        }

        cin >> lim;
        while (lim--) {
            cin >> value;
            RS[i].pb(value);
        }
    }

    for (i = 1; i <= NI; ++i) {
        int lim, value;
        cin >> lim;
        while (lim--) {
            cin >> value;
            RI[i].pb(value);
        }

        cin >> lim;
        while (lim--) {
            cin >> value;
            C[i].pb(value);
        }
    }

    for (i = 1; i <= NM; ++i) {
        G[source].pb(nM[i]);
        G[nM[i]].pb(source);
        Cap[source][nM[i]] = 1;
    }

    for (i = 1; i <= NS; ++i)
        for (const auto &it : M[i]) {
            G[nM[it] + 1].pb(nS[i]);
            G[nS[i]].pb(nM[it] + 1);
            Cap[nM[it] + 1][nS[i]] = 1;
        }

    for (i = 1; i <= NS; ++i)
        for (const auto &it : RS[i]) {
            G[nS[i] + 1].pb(nR[it]);
            G[nR[it]].pb(nS[i] + 1);
            Cap[nS[i] + 1][nR[it]] = 1;
        }

    for (i = 1; i <= NI; ++i)
        for (const auto &it : RI[i]) {
            G[nR[it] + 1].pb(nI[i]);
            G[nI[i]].pb(nR[it] + 1);
            Cap[nR[it] + 1][nI[i]] = 1;
        }

    for (i = 1; i <= NI; ++i)
        for (const auto &it : C[i]) {
            G[nI[i] + 1].pb(nC[it]);
            G[nC[it]].pb(nI[i] + 1);
            Cap[nI[i] + 1][nC[it]] = 1;
        }

    for (i = 1; i <= NC; ++i) {
        G[nC[i] + 1].pb(sink);
        G[sink].pb(nC[i] + 1);
        Cap[nC[i] + 1][sink] = 1;
    }

    for (i = 2; i <= sink - 2; i += 2) {
        G[i].pb(i + 1);
        G[i + 1].pb(i);
        Cap[i][i + 1] = 1;
    }

    int flow = 0;
    while (BFS(source, sink))
        ++flow;

    cout << flow << '\n';

	return 0;
}
