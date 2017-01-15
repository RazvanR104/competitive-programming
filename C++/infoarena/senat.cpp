#include <bits/stdc++.h>

using namespace std;

const int NMAX = 110, LMAX = 510;

int N, M;
int lt[NMAX], rt[NMAX];
char line[LMAX];
bool vis[NMAX];
vector<int> G[NMAX];

bool PairUp(int node) {
    if (vis[node])
        return 0;
    vis[node] = 1;

    for (const int &it: G[node]) {
        if (rt[it] == 0) {
            lt[node] = it;
            rt[it] = node;
            return 1;
        }
    }

    for (const int &it: G[node]) {
        if (PairUp(rt[it])) {
            lt[node] = it;
            rt[it] = node;
            return 1;
        }
    }
    return 0;
}

int main() {
    assert(freopen("senat.in", "r", stdin));
    assert(freopen("senat.out", "w", stdout));

    int i, j;

    cin >> N >> M;
    cin.ignore(1);
    for (i = 1; i <= M; ++i) {
        cin.getline(line, LMAX);

        int pos = 0;
        while (1) {
            int node = 0;
            while (!isdigit(line[pos]) && line[pos] != 0)
                ++pos;
            while (isdigit(line[pos]))
                node = node * 10 + line[pos++] - '0';

            if (node == 0)
                break;

            G[node].push_back(i);
        }
    }

    int changed;
    do {
        changed = 0;
        memset(vis, 0, sizeof vis);
        for (i = 1; i <= N; ++i)
            if (lt[i] == 0)
                changed |= PairUp(i);
    } while (changed);

    int maxmatch = 0;
    for (i = 1; i <= N; ++i)
        if (lt[i])
            ++maxmatch;

    if (maxmatch < M)
        cout << "0\n";
    else
        for (i = 1; i <= M; ++i)
            cout << rt[i] << '\n';

    return 0;
}
