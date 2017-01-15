#include <bits/stdc++.h>

using namespace std;

const int NMAX = 260;
const int dl[] = {0, 1, -1, 0};
const int dc[] = {1, 0, 0, -1};

int T, N, M, K;
int U[NMAX][NMAX];
int disjoint[NMAX * NMAX], height[NMAX * NMAX], sum[NMAX * NMAX];
vector<pair<int, int>> C[NMAX * NMAX];
stack<pair<int *, int>> S;

inline int encode(int ln, int col) {
    return (ln - 1) * M + col;
}

void Unite(int root1, int root2, int log = 0) {
    if (root1 == root2)
        return;

    if (height[root1] < height[root2]) {
        if (log) {
            S.push({disjoint + root1, disjoint[root1]});
            S.push({sum + root2, sum[root2]});
        }
        disjoint[root1] = root2;
        sum[root2] += sum[root1];
    }
    else {
        if (log) {
            S.push({disjoint + root2, disjoint[root2]});
            S.push({sum + root1, sum[root1]});
        }
        disjoint[root2] = root1;
        sum[root1] += sum[root2];
        if (height[root1] == height[root2]) {
            if (log)
                S.push({height + root1, height[root1]});
            ++height[root1];
        }
    }
}

int Find(int node, int log = 0) {
    int _node = node;
    while (_node != disjoint[_node])
        _node = disjoint[_node];
    while (node != disjoint[node]) {
        int next = disjoint[node];
        if (log)
            S.push({disjoint + node, disjoint[node]});
        disjoint[node] = _node;
        node = next;
    }
    return _node;
}

void Restore() {
    while (!S.empty()) {
        int *where, value;
        tie(where, value) = S.top();
        S.pop();
        *where = value;
    }
}

int main() {
    assert(freopen("unlock.in", "r", stdin));
    assert(freopen("unlock.out", "w", stdout));

    int i, j, k;

    for (scanf("%d", &T); T; --T) {
        scanf("%d %d %d", &N, &M, &K);

        int cnt = 0;
        for (i = 1; i <= N; ++i)
            for (j = 1; j <= M; ++j) {
                scanf("%d", &U[i][j]);
                if (U[i][j] == 0)
                    ++cnt;
                else
                    C[U[i][j]].push_back({i, j});
                int pos = encode(i, j);
                height[pos] = 0;
                disjoint[pos] = pos;
                sum[pos] = (U[i][j] > 0) ? 0 : 1;
            }

        for (i = 1; i <= N; ++i) {
            for (j = 1; j <= M; ++j) {
                if (U[i][j])
                    continue;
                int pos = encode(i, j);
                for (k = 0; k < 4; ++k) {
                    int nl = i + dl[k];
                    int nc = j + dc[k];
                    if (nl < 1 || nl > N || nc < 1 || nc > M || U[nl][nc])
                        continue;
                    int curr = encode(nl, nc);
                    Unite(Find(pos), Find(curr));
                }
            }
        }

        bool ok = 0;
        int ref_pos = 0;
        for (i = 1; i <= N; ++i)
            for (j = 1; j <= M; ++j) {
                if (U[i][j] == 0)
                    ref_pos = encode(i, j);
                if (U[i][j] == 0 && sum[Find(encode(i, j))] == cnt) {
                    ok = 1;
                    break;
                }
            }

        int answer = 0;
        for (i = 1; i <= K; ++i) {
            if (C[i].size() == 0) {
                answer += ok;
                continue;
            }
            if (ok) {
                C[i].clear();
                ++answer;
                continue;
            }

            for (const auto &it: C[i]) {
                int pos = encode(it.first, it.second);
                for (k = 0; k < 4; ++k) {
                    int nl = it.first + dl[k];
                    int nc = it.second + dc[k];
                    if (nl < 1 || nl > N || nc < 1 || nc > M || (U[nl][nc] != i && U[nl][nc] != 0))
                        continue;
                    Unite(Find(encode(nl, nc), 1), Find(pos, 1), 1);
                }
            }
            if (sum[Find(ref_pos, 1)] == cnt)
                ++answer;

            Restore();

            C[i].clear();
        }

        cout << answer << '\n';
    }

    return 0;
}
