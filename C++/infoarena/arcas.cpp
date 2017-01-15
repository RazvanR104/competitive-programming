#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e5;

int N, M;
int BIT[4 * NMAX + 10], answer[NMAX];

void Update(int pos, int value) {
    for ( ; pos <= 4 * NMAX; pos += pos & -pos)
        BIT[pos] += value;
}

int Query(int pos) {
    int ret = 0;
    for ( ; pos > 0; pos -= pos & -pos)
        ret += BIT[pos];
    return ret;
}

inline int Get(int x, int y) {
    if (x <= y)
        return 2 * NMAX - y + x + 1;
    return 2 * NMAX + x - y + 1;
}

vector<pair<int, int>> Add[2 * NMAX + 10], Qu[2 * NMAX + 10];

int main() {
    assert(freopen("arcas.in", "r", stdin));
    assert(freopen("arcas.out", "w", stdout));

    cin >> N >> M;

    int i, j;
    int x, y1, y2, y, r;

    for (i = 1; i <= N; ++i) {
        cin >> x >> y1 >> y2;
        Add[x].push_back({Get(x, y2), Get(x, y1)});
    }

    for (i = 1; i <= M; ++i) {
        cin >> x >> y >> r;
        Qu[x - 1].push_back({Get(x, y), -i});
        Qu[x + r].push_back({Get(x, y), i});
    }

    for (i = 1; i < 2 * NMAX + 10; ++i) {
        for (const auto &it: Add[i]) {
            Update(it.first, 1);
            Update(it.second + 1, -1);
        }

        for (const auto &it: Qu[i]) {
            if (it.second < 0)
                answer[-it.second] -= Query(it.first);
            else
                answer[it.second] += Query(it.first);
        }
    }

    for (i = 1; i <= M; ++i)
        cout << answer[i] << '\n';

    return 0;
}
