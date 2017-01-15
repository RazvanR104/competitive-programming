#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1010;
const int dl[] = {-1, 0, 1, 0};
const int dc[] = {0, -1, 0, 1};

int N, K1, K2, L1, C1, L2, C2;

int M[NMAX][NMAX];
int D[NMAX][NMAX][2][2];

int main() {
    assert(freopen("vis.in", "r", stdin));
    assert(freopen("vis.out", "w", stdout));

    int i, j;

    assert(scanf("%d %d %d %d %d %d %d", &N, &K1, &K2, &L1, &C1, &L2, &C2) == 7);

    for (i = 1; i <= N; ++i)
        for (j = 1; j <= N; ++j)
            assert(scanf("%d", &M[i][j]) == 1);

    D[1][1][0][0] = 1;
    queue<tuple<int, int, int, int>> Q;
    Q.push(make_tuple(1, 1, 0, 0));

    while (!Q.empty()) {
        int ln, col, st1, st2;
        tie(ln, col, st1, st2) = Q.front();
        Q.pop();

        for (i = 0; i < 4; ++i) {
            int nln = ln + dl[i];
            int ncol = col + dc[i];
            int nst1, nst2;

            if (nln < 1 || nln > N || ncol < 1 || ncol > N)
                continue;

            if (st1 == 0 && st2 == 0) {
                if (nln == L1 && ncol == C1) {
                    nst1 = 1;
                    nst2 = 0;
                } else if (nln == L2 && ncol == C2) {
                    nst1 = 0;
                    nst2 = 1;
                } else if (M[nln][ncol] == 0)
                    nst1 = nst2 = 0;
                else continue;
            } else if (st1 == 1 && st2 == 0) {
                if (nln == L2 && ncol == C2)
                    nst1 = nst2 = 1;
                else if (M[nln][ncol] == 0 || M[nln][ncol] <= K1) {
                    nst1 = 1;
                    nst2 = 0;
                } else continue;
            } else if (st1 == 0 && st2 == 1) {
                if (nln == L1 && ncol == C1)
                    nst1 = nst2 = 1;
                else if (M[nln][ncol] == 0 || M[nln][ncol] >= K2) {
                    nst1 = 0;
                    nst2 = 1;
                } else continue;
            } else {
                if (M[nln][ncol] == 0 || M[nln][ncol] >= K2 || M[nln][ncol] <= K1)
                    nst1 = nst2 = 1;
                else continue;
            }

            if (D[nln][ncol][nst1][nst2])
                continue;

            D[nln][ncol][nst1][nst2] = D[ln][col][st1][st2] + 1;
            Q.push(make_tuple(nln, ncol, nst1, nst2));
        }
    }

    int answer = 1e9;
    for (i = 0; i < 2; ++i)
        for (j = 0; j < 2; ++j)
            if (D[N][N][i][j])
                answer = min(answer, D[N][N][i][j]);

    cout << answer << '\n';
    return 0;
}
