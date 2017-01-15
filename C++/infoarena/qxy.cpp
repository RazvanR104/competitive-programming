#include <bits/stdc++.h>

using namespace std;

const int NMAX = 10010, FMAX = 1010, QMAX = 100010;

int N, Q;
int V[NMAX], Fen[FMAX];

int Query(int pos) {
    ++pos;
    int res = 0;
    for ( ; pos > 0; pos -= pos & (-pos))
        res += Fen[pos];
    return res;
}

void Update(int pos, int value) {
    ++pos;
    for ( ; pos < FMAX; pos += pos & (-pos))
        Fen[pos] += value;
}

struct Qu {
    int vmin, vmax;
    int ans[3];
} Qry[QMAX];

vector<int> Event[NMAX];

int main() {
	ios_base::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
	assert(freopen("qxy.in", "r", stdin) != NULL);
    assert(freopen("qxy.out", "w", stdout) != NULL);
    assert(freopen("debug.err", "w", stderr) != NULL);
    #endif

    int i, x, y;

    scanf("%d", &N);
    for (i = 1; i <= N; ++i)
        scanf("%d", &V[i]);

    scanf("%d", &Q);
    for (i = 1; i <= Q; ++i) {
        //cin >> x >> y >> Qry[i].vmin >> Qry[i].vmax;
        scanf("%d %d %d %d", &x, &y, &Qry[i].vmin, &Qry[i].vmax);
        Event[x - 1].push_back(i);
        Event[y].push_back(i);
    }

    for (i = 0; i <= N; ++i) {
        if (i > 0)
            Update(V[i], 1);

        for (const int &it : Event[i])
            Qry[it].ans[++Qry[it].ans[0]] = Query(Qry[it].vmax) - Query(Qry[it].vmin - 1);
    }

    for (i = 1; i <= Q; ++i)
        cout << Qry[i].ans[2] - Qry[i].ans[1] << '\n';

	return 0;
}
