#include <bits/stdc++.h>

using namespace std;

const int NMAX = 800;
const int dl[] = {-1, 0, 1, 0};
const int dc[] = {0, -1, 0, 1};

int N, M;
int A[NMAX][NMAX];
bool used[NMAX][NMAX], inside[NMAX][NMAX];

int main() {
    assert(freopen("volum.in", "r", stdin));
    assert(freopen("volum.out", "w", stdout));

    int i, j;

    scanf("%d %d", &N, &M);
    for (i = 1; i <= N; ++i)
        for (j = 1; j <= M; ++j)
            scanf("%d", &A[i][j]);

    priority_queue<tuple<int, int, int>> Q;
    for (i = 1; i <= N; ++i) {
        Q.push(make_tuple(-A[i][1], i, 1));
        Q.push(make_tuple(-A[i][M], i, M));
        inside[i][1] = inside[i][M] = 1;
    }

    for (i = 2; i <= M - 1; ++i) {
        Q.push(make_tuple(-A[1][i], 1, i));
        Q.push(make_tuple(-A[N][i], N, i));
        inside[1][i] = inside[N][i] = 1;
    }

    queue<pair<int, int>> BF;
    int64_t answer = 0;
    while (!Q.empty()) {
        int value, ln, col;
        tie(value, ln, col) = Q.top();
        Q.pop();

        used[ln][col] = 1;
        BF.push({ln, col});
        while (!BF.empty()) {
            int x, y;
            tie(x, y) = BF.front();
            BF.pop();

            answer += A[ln][col] - A[x][y];
            A[x][y] = A[ln][col];

            for (i = 0; i < 4; ++i) {
                int nln = x + dl[i];
                int ncol = y + dc[i];
                if (nln < 1 || nln > N || ncol < 1 || ncol > M || used[nln][ncol])
                    continue;
                if (A[nln][ncol] <= A[ln][col]) {
                    used[nln][ncol] = 1;
                    BF.push({nln, ncol});
                } else {
                    if (inside[nln][ncol] == 0) {
                        Q.push(make_tuple(-A[nln][ncol], nln, ncol));
                        inside[nln][ncol] = 1;
                    }
                }
            }
        }
    }

    cout << answer << '\n';
    return 0;
}
