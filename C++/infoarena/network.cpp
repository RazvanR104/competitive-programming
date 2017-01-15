#include <bits/stdc++.h>

using namespace std;

const double eps = 1e-10;
const int NMAX = 5010, EMAX = 50010, EQMAX = 70 * 2 + 10;

int N, E;
int X[EMAX], Y[EMAX];
int where[NMAX], degree[NMAX];
double DP[NMAX][2], A[EQMAX][EQMAX];
double P0[EMAX], P1[EMAX], ans[EQMAX];
bool vis[NMAX], already[NMAX];
vector<int> Gi[NMAX], Gr[NMAX], order, component[NMAX];
vector<pair<int, int>> Find[NMAX];

void DFSP(int node) {
    vis[node] = 1;
    for (const int &it: Gi[node])
        if (vis[it] == 0)
            DFSP(it);
    order.push_back(node);
}

void DFSM(int node, int scc) {
    component[scc].push_back(node);
    where[node] = scc;
    for (const int &it: Gr[node])
        if (where[it] == -1)
            DFSM(it, scc);
}

int getpos(int where, int value) {
    return lower_bound(component[where].begin(), component[where].end(), value) - component[where].begin();
}

void Gauss(int N, int M) {
    int ln = 0, col = 0;
    int i, j, k;

    while (ln < N && col < M) {
        for (i = ln; i < N; ++i)
            if (A[i][col] < -eps || A[i][col] > eps)
                break;

        if (i == N) {
            ++col;
            continue;
        }

        if (i != ln)
            for (j = 1; j <= M; ++j)
                swap(A[ln][j], A[i][j]);

        for (i = col + 1; i <= M; ++i)
            A[ln][i] /= A[ln][col];
        A[ln][col] = 1;

        for (i = ln + 1; i < N; ++i)
            if (A[i][col] < -eps || A[i][col] > eps) {
                for (j = col + 1; j <= M; ++j)
                    A[i][j] -= A[i][col] * A[ln][j];
                A[i][col] = 0;
            }

        ++ln, ++col;
    }

    memset(ans, 0, sizeof ans);
    for (i = N - 1; i >= 0; --i) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] < -eps || A[i][j] > eps) {
                ans[j] = A[i][M];

                for (k = j + 1; k < M; ++k)
                    ans[j] -= A[i][k] * ans[k];

                break;
            }
        }
    }
}

int main() {
    assert(freopen("network.in", "r", stdin));
    assert(freopen("network.out", "w", stdout));

    int i;

    //cin >> N >> E;
    scanf("%d %d", &N, &E);
    for (i = 1; i <= E; ++i) {
        //cin >> X[i] >> Y[i] >> P0[i] >> P1[i];
        scanf("%d %d %lf %lf", &X[i], &Y[i], &P0[i], &P1[i]);
        Gi[X[i]].push_back(Y[i]);
        Gr[Y[i]].push_back(X[i]);
        Find[X[i]].push_back({Y[i], i});
    }

    for (i = 0; i < N; ++i)
        if (vis[i] == 0)
            DFSP(i);

    memset(where, -1, sizeof where);
    int curr_scc = 0;
    for ( ; order.size(); order.pop_back())
        if (where[order.back()] == -1)
            DFSM(order.back(), curr_scc++);

    for (i = 0; i < curr_scc; ++i)
        sort(component[i].begin(), component[i].end());

    int now = where[N - 1];
    int size = component[now].size();

    int pos = getpos(now, N - 1);
    A[pos * 2][pos * 2] = A[pos * 2][2 * size] = A[pos * 2 + 1][pos * 2 + 1] = A[pos * 2 + 1][2 * size] = 1;
    for (i = 0; i < size; ++i) {
        if (component[now][i] == N - 1)
            continue;

        pos = i;
        A[pos * 2][pos * 2] = A[pos * 2 + 1][pos * 2 + 1] += -1;

        for (const auto &it: Find[component[now][i]]) {
            int _pos = getpos(now, it.first);
            int _size = Find[component[now][i]].size();

            A[pos * 2][_pos * 2] += P0[it.second] / _size;
            A[pos * 2][_pos * 2 + 1] += (-1 + P0[it.second]) / _size;
            A[pos * 2][2 * size] += (-1 + P0[it.second]) / _size;

            A[pos * 2 + 1][_pos * 2] += (-1 + P1[it.second]) / _size;
            A[pos * 2 + 1][_pos * 2 + 1] += P1[it.second] / _size;
            A[pos * 2 + 1][2 * size] += (-1 + P1[it.second]) / _size;
        }
    }

    Gauss(2 * size, 2 * size);
    for (i = 0; i < size; ++i) {
        DP[component[now][i]][0] = ans[i * 2];
        DP[component[now][i]][1] = ans[i * 2 + 1];
        already[component[now][i]] = 1;
    }

    for (now = curr_scc - 2; now >= 0; --now) {
        size = component[now].size();

        memset(A, 0, sizeof A);
        for (i = 0; i < size; ++i) {
            pos = i;
            int _size = Find[component[now][i]].size();
            A[pos * 2][pos * 2] += -1;
            A[pos * 2 + 1][pos * 2 + 1] += -1;

            for (const auto &it: Find[component[now][i]]) {
                int _pos = getpos(now, it.first);

                if (already[it.first]) {
                    A[pos * 2][2 * size] -= P0[it.second] * DP[it.first][0] / _size;
                    A[pos * 2][2 * size] -= (-1 + P0[it.second]) * DP[it.first][1] / _size;
                    A[pos * 2][2 * size] += (-1 + P0[it.second]) / _size;

                    A[pos * 2 + 1][2 * size] -= (-1 + P1[it.second]) * DP[it.first][0] / _size;
                    A[pos * 2 + 1][2 * size] -= P1[it.second] * DP[it.first][1] / _size;
                    A[pos * 2 + 1][2 * size] += (-1 + P1[it.second]) / _size;

                    continue;
                }

                A[pos * 2][_pos * 2] += P0[it.second] / _size;
                A[pos * 2][_pos * 2 + 1] += (-1 + P0[it.second]) / _size;
                A[pos * 2][2 * size] += (-1 + P0[it.second]) / _size;

                A[pos * 2 + 1][_pos * 2] += (-1 + P1[it.second]) / _size;
                A[pos * 2 + 1][_pos * 2 + 1] += P1[it.second] / _size;
                A[pos * 2 + 1][2 * size] += (-1 + P1[it.second]) / _size;
            }
        }

        Gauss(2 * size, 2 * size);
        for (i = 0; i < size; ++i) {
            DP[component[now][i]][0] = ans[i * 2];
            DP[component[now][i]][1] = ans[i * 2 + 1];
            already[component[now][i]] = 1;
        }
    }

    cout << fixed << setprecision(7);
    cout << DP[0][0] << '\n' << DP[0][1] << '\n';
    return 0;
}
