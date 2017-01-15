#include <bits/stdc++.h>

using namespace std;

const int NMAX = 210;
const int dl[] = {-1, 0, 1, 0, -1, -1, 1, 1};
const int dc[] = {0, -1, 0, 1, 1, -1, -1, 1};

int N, M, p, x, y, K, E;
int mat[NMAX][NMAX];
bool locked[NMAX];
vector<tuple<int, int, int>> G[NMAX][NMAX];
vector<pair<int, int>> answer;

void Cycle(int x, int y) {
    int nx, ny, pos;
    for (const auto &it: G[x][y]) {
        tie(nx, ny, pos) = it;
        if (locked[pos])
            continue;
        locked[pos] = 1;
        Cycle(nx, ny);
    }
    answer.push_back({x, y});
}

int main() {
    freopen("cartite.in", "r", stdin);
    freopen("cartite.out", "w", stdout);

    int i, j;

    cin >> p >> N >> M >> x >> y >> K;

    int px, py, r;
    for (i = 1; i <= K; ++i) {
        cin >> px >> py >> r;
        mat[px][py] = -1;
        if (r >= 1) {
            for (j = 0; j < 4; ++j)
                mat[px + dl[j]][py + dc[j]] = -1;

            if (r == 2) {
                for (j = 4; j < 8; ++j)
                    mat[px + dl[j]][py + dc[j]] = -1;

                if (py - 2 >= 1) mat[px][py - 2] = -1;
                if (px - 2 >= 1) mat[px - 2][py] = -1;
                if (py + 2 <= M) mat[px][py + 2] = -1;
                if (px + 2 <= N) mat[px + 2][py] = -1;
            }
        }
    }

    cin >> E;
    int x1, y1, x2, y2;
    for (i = 1; i <= E; ++i) {
        cin >> x1 >> y1 >> x2 >> y2;
        G[x1][y1].push_back(make_tuple(x2, y2, i));
        G[x2][y2].push_back(make_tuple(x1, y1, i));
        if (mat[x1][y1] == 0) mat[x1][y1] = -2;
        if (mat[x2][y2] == 0) mat[x2][y2] = -2;
    }

    if (p == 1) {
        if (mat[x][y] == -2) {
            cout << x << ' ' << y << ' ' << 0 << '\n';
            return 0;
        }

        mat[x][y] = 1;
        queue<pair<int, int>> Q;
        Q.push({x, y});

        while (!Q.empty()) {
            tie(x, y) = Q.front();
            Q.pop();

            int nx, ny;
            for (i = 0; i < 4; ++i) {
                nx = x + dl[i];
                ny = y + dc[i];
                if (nx < 1 || nx > N || ny < 1 || ny > M || mat[nx][ny] == -1)
                    continue;

                if (mat[nx][ny] == -2) {
                    cout << nx << ' ' << ny << ' ' << mat[x][y] << '\n';
                    return 0;
                }

                if (mat[nx][ny] != 0)
                    continue;

                mat[nx][ny] = mat[x][y] + 1;
                Q.push({nx, ny});
            }
        }
    }

    Cycle(x1, y1);
    for (const auto &it: answer)
        cout << it.first << ' ' << it.second << '\n';

    return 0;
}
