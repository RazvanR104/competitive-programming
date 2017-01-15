#include <bits/stdc++.h>

using namespace std;

const int NMAX = 25;
const int dl[] = {-2, 2, 0, 0, -1, 1, 0, 0};
const int dc[] = {0, 0, -2, 2, 0, 0, -1, 1};

int N, M, I;
int T[NMAX][NMAX], pos[NMAX][NMAX];
pair<int, int> coord[NMAX];
vector<tuple<int, int, int, int>> answer;

void Go(int depth) {
    if (depth == 1) {
        for (const auto &it: answer)
            cout << get<0>(it) << ' ' << get<1>(it) << ' ' << get<2>(it) << ' ' << get<3>(it) << '\n';
        exit(0);
    }

    for (int it = 1; it <= I; ++it) {
        int x, y;
        tie(x, y) = coord[it];
        if (pos[x][y] == 0)
            continue;
        for (int i = 0; i < 4; ++i) {
            int nx = x + dl[i];
            int ny = y + dc[i];

            if (nx < 1 || nx > N || ny < 1 || ny > M)
                continue;

            int cx = x + dl[i + 4];
            int cy = y + dc[i + 4];
            if (T[nx][ny] == 0 && T[cx][cy] == 1) {
                T[cx][cy] = 0;
                T[nx][ny] = 1;
                T[x][y] = 0;

                int pos1 = pos[x][y], pos2 = pos[cx][cy];
                pos[x][y] = 0;
                pos[cx][cy] = 0;
                pos[nx][ny] = pos1;
                coord[pos1] = {nx, ny};

                answer.push_back(make_tuple(x, y, nx, ny));
                Go(depth - 1);
                answer.pop_back();

                T[cx][cy] = 1;
                T[nx][ny] = 0;
                T[x][y] = 1;


                pos[x][y] = pos1;
                pos[cx][cy] = pos2;
                pos[nx][ny] = 0;
                coord[pos1] = {x, y};
                coord[pos2] = {cx, cy};
            }
        }
    }
}

int main() {
    assert(freopen("immortal.in", "r", stdin));
    assert(freopen("immortal.out", "w", stdout));

    int i, x, y;

    cin >> N >> M >> I;
    for (i = 1; i <= I; ++i) {
        cin >> x >> y;
        T[x][y] = 1;
        coord[i] = {x, y};
        pos[x][y] = i;
    }

    Go(I);

    return 0;
}
