#include <bits/stdc++.h>

using namespace std;

const int VMAX = 8010, NMAX = 4010, inf = 0x3f3f3f3f;

int T, N, Vmax;
int V[NMAX], DP[VMAX], arog[VMAX];

int main() {
    assert(freopen("euro3.in", "r", stdin));
    assert(freopen("euro3.out", "w", stdout));

    int i, j;

    for (cin >> T; T; --T) {
        cin >> N >> Vmax;

        for (i = 1; i <= N; ++i)
            cin >> V[i];
        sort(V + 1, V + N + 1);

        memset(DP, -1, sizeof DP);
        memset(arog, inf, sizeof arog);

        DP[V[1]] = 1;
        arog[V[1]] = 0;

        for (i = 2; i <= N; ++i) {
            for (j = Vmax - V[i]; j >= 1; --j) {
                if (DP[j] == -1)
                    continue;
                if (V[i] - V[DP[j]] <= Vmax && DP[j + V[i]] < DP[j]) {
                    DP[j + V[i]] = DP[j];
                    arog[j + V[i]] = min(arog[j + V[i]], V[i] - V[DP[j]]);
                }
            }

            DP[V[i]] = i;
            arog[V[i]] = 0;
        }

        for (i = 1; i <= Vmax; ++i)
            cout << (arog[i] != inf ? arog[i] : -1) << ' ';
        cout << '\n';
    }

    return 0;
}
