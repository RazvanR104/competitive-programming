#include <bits/stdc++.h>

using namespace std;

const int NMAX = 310;

int N, M, K;
int mat[NMAX][NMAX];
int cnt[NMAX * NMAX];
vector<int> elem;

int main() {
    assert(freopen("submatrix.in", "r", stdin));
    assert(freopen("submatrix.out", "w", stdout));

    int i, j;

    scanf("%d %d %d", &N, &M, &K);
    for (i = 1; i <= N; ++i)
        for (j = 1; j <= M; ++j) {
            scanf("%d", &mat[i][j]);
            elem.push_back(mat[i][j]);
        }

    sort(elem.begin(), elem.end());
    for (i = 1; i <= N; ++i)
        for (j = 1; j <= M; ++j)
            mat[i][j] = lower_bound(elem.begin(), elem.end(), mat[i][j]) - elem.begin() + 1;

    int answer = 1;
    for (i = 1; i <= N; ++i) {
        memset(cnt, 0, sizeof cnt);
        int lnd = i, cold = 1, uniq = 1;
        int lns = i, cols = 1;
        ++cnt[mat[lnd][cold]];

        for ( ; lnd <= N && cold <= M; ++lnd, ++cold) {
            ++cnt[mat[lnd][cold]];
            if (cnt[mat[lnd][cold]] == 1)
                ++uniq;

            for (j = cold - 1; j >= cols; --j) {
                ++cnt[mat[lnd][j]];
                if (cnt[mat[lnd][j]] == 1)
                    ++uniq;
            }

            for (j = lnd - 1; j >= lns; --j) {
                ++cnt[mat[j][cold]];
                if (cnt[mat[j][cold]] == 1)
                    ++uniq;
            }

            while (uniq > K) {
                --cnt[mat[lns][cols]];
                if (cnt[mat[lns][cols]] == 0)
                    --uniq;
                for (j = cols + 1; j <= cold; ++j) {
                    --cnt[mat[lns][j]];
                    if (cnt[mat[lns][j]] == 0)
                        --uniq;
                }

                for (j = lns + 1; j <= lnd; ++j) {
                    --cnt[mat[j][cols]];
                    if (cnt[mat[j][cols]] == 0)
                        --uniq;
                }
                ++lns, ++cols;
            }
            answer = max(answer, lnd - lns + 1);
        }
    }

    for (i = 1; i <= M; ++i) {
        memset(cnt, 0, sizeof cnt);
        int lnd = 1, cold = i, uniq = 1;
        int lns = 1, cols = i;
        ++cnt[mat[lnd][cold]];

        for ( ; lnd <= N && cold <= M; ++lnd, ++cold) {
            ++cnt[mat[lnd][cold]];
            if (cnt[mat[lnd][cold]] == 1)
                ++uniq;

            for (j = cold - 1; j >= cols; --j) {
                ++cnt[mat[lnd][j]];
                if (cnt[mat[lnd][j]] == 1)
                    ++uniq;
            }

            for (j = lnd - 1; j >= lns; --j) {
                ++cnt[mat[j][cold]];
                if (cnt[mat[j][cold]] == 1)
                    ++uniq;
            }

            while (uniq > K) {
                --cnt[mat[lns][cols]];
                if (cnt[mat[lns][cols]] == 0)
                    --uniq;

                for (j = cols + 1; j <= cold; ++j) {
                    --cnt[mat[lns][j]];
                    if (cnt[mat[lns][j]] == 0)
                        --uniq;
                }

                for (j = lns + 1; j <= lnd; ++j) {
                    --cnt[mat[j][cols]];
                    if (cnt[mat[j][cols]] == 0)
                        --uniq;
                }
                ++lns, ++cols;
            }
            answer = max(answer, lnd - lns + 1);
        }
    }

    cout << answer << '\n';
    return 0;
}
