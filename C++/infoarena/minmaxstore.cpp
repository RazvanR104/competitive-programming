#include <bits/stdc++.h>

using namespace std;

const int NMAX = 100010, MMAX = 200010;

int T, N, M;
int go[NMAX], V[MMAX][2];

int Solve() {
    int i, j, cnt = 1;
    for (i = M; i >= 1; --i) {
        if (go[V[i][0]] == 1 && go[V[i][1]] == 0) {
            go[V[i][1]] = 1;
            ++cnt;
        } else if (go[V[i][0]] == 0 && go[V[i][1]] == 1) {
            go[V[i][1]] = 0;
            --cnt;
        }
    }

    return cnt == N;
}

int main() {
    assert(freopen("minmaxstore.in", "r", stdin));
    assert(freopen("minmaxstore.out", "w", stdout));

    int i, j, x, y;

    for (scanf("%d", &T); T; --T) {
        scanf("%d %d", &N, &M);
        for (i = 1; i <= M; ++i)
            scanf("%d %d", &V[i][0], &V[i][1]);
        scanf("%d %d", &x, &y);

        memset(go, 0, sizeof go);
        go[x] = 1;
        int ok1 = Solve();

        for (i = 1; i <= M; ++i)
            swap(V[i][0], V[i][1]);

        memset(go, 0, sizeof go);
        go[y] = 1;
        int ok2 = Solve();

        if (ok1 && ok2)
            cout << "Popeala\n";
        else if (ok1)
            cout << "Popel\n";
        else if (ok2)
            cout << "Popita\n";
        else cout << "Comisarul\n";
    }

    return 0;
}
