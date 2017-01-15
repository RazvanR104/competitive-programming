#include <bits/stdc++.h>

using namespace std;

const int MAX = 60, NMAX = 70000;
const int dl[] = {0, 0, 1, 1};
const int dc[] = {0, 1, 1, 0};

int N, M;
int V[NMAX];
int P[MAX][MAX][MAX], DP[NMAX], from[NMAX];
vector<int> answer, curr;

int main() {
    assert(freopen("suma4.in", "r", stdin));
    assert(freopen("suma4.out", "w", stdout));

    int i, j, k, l;
    cin >> N;
    for (i = 1; i <= N; ++i)
        cin >> V[i];

    M = 1;
    while (M * (M + 1) * (2 * M + 1) / 6 < N)
        ++M;

    cout << M << ' ';

    int pos = 1;
    for (i = 1; i <= M; ++i)
        for (j = 1; j <= i; ++j)
            for (k = 1; k <= i; ++k)
                P[i][j][k] = pos++;

    for (i = 1; i <= N; ++i)
        cin >> V[i];

    memset(DP, 0x3f, sizeof DP);
    DP[1] = V[1];
    for (i = 1; i < M; ++i) {
        for (j = 1; j <= i; ++j) {
            for (k = 1; k <= i; ++k) {
                for (l = 0; l < 4; ++l) {
                    int nln = j + dl[l];
                    int ncol = k + dc[l];
                    if (P[i + 1][nln][ncol] == 0)
                        continue;
                    if (DP[P[i + 1][nln][ncol]] > DP[P[i][j][k]] + V[P[i + 1][nln][ncol]]) {
                        DP[P[i + 1][nln][ncol]] = DP[P[i][j][k]] + V[P[i + 1][nln][ncol]];
                        from[P[i + 1][nln][ncol]] = P[i][j][k];
                    } else if (DP[P[i + 1][nln][ncol]] == DP[P[i][j][k]] + V[P[i + 1][nln][ncol]] &&
                               from[P[i + 1][nln][ncol]] > P[i][j][k])
                        from[P[i + 1][nln][ncol]] = P[i][j][k];
                }
            }
        }
    }

    int answer1 = 1e9;
    for (j = 1; j <= M; ++j)
        for (k = 1; k <= M; ++k)
            answer1 = min(answer1, DP[P[M][j][k]]);
    cout << answer1 << '\n';

    for (j = 1; j <= M; ++j)
        for (k = 1; k <= M; ++k) {
            if (DP[P[M][j][k]] == answer1) {
                int go = P[M][j][k];
                curr.clear();
                curr.push_back(go);
                while (from[go]) {
                    curr.push_back(from[go]);
                    go = from[go];
                }
                reverse(curr.begin(), curr.end());
                if (answer.size() == 0 || curr < answer)
                    answer = curr;
            }
        }

    for (const int &it: answer)
        cout << it << ' ';
    cout << '\n';
    return 0;
}
