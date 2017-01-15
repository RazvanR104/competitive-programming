#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1510;
const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};

int N, M;
int T[NMAX][NMAX], answer[2 * NMAX];
pair<int, int> where[NMAX * NMAX];
bitset<NMAX * NMAX> locked;

int main() {
    assert(freopen("bemo.in", "r", stdin));
    assert(freopen("bemo.out", "w", stdout));

    int i, j;

    scanf("%d %d", &N, &M);
    for (i = 1; i <= N; ++i)
        for (j = 1; j <= M; ++j) {
            scanf("%d", &T[i][j]);
            where[T[i][j]] = {i, j};
        }

    for (i = 1; i <= N * M; ++i) {
        if (locked[i])
            continue;
        int x, y;
        tie(x, y) = where[i];
        answer[x + y - 1] = i;

        queue<pair<int, int>> Q;

        locked[T[x - 1][y + 1]] = 1;
        Q.push({x - 1, y + 1});
        while (!Q.empty()) {
            int x, y;
            tie(x, y) = Q.front();
            Q.pop();

            for (j = 0; j < 2; ++j) {
                int nx = x + dx[j];
                int ny = y + dy[j];
                if (nx < 1 || ny < 1 || nx > N || ny > M || locked[T[nx][ny]])
                    continue;
                locked[T[nx][ny]] = 1;
                Q.push({nx, ny});
            }
        }

        locked[T[x + 1][y - 1]] = 1;
        Q.push({x + 1, y - 1});
        while (!Q.empty()) {
            int x, y;
            tie(x, y) = Q.front();
            Q.pop();

            for (j = 2; j < 4; ++j) {
                int nx = x + dx[j];
                int ny = y + dy[j];
                if (nx < 1 || ny < 1 || nx > N || ny > M || locked[T[nx][ny]])
                    continue;
                locked[T[nx][ny]] = 1;
                Q.push({nx, ny});
            }
        }
    }

    for (i = 1; i <= N + M - 1; ++i)
        cout << answer[i] << ' ';
    cout << '\n';

    return 0;
}
