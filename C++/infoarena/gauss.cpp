#include <bits/stdc++.h>

using namespace std;

const int MMAX = 310;
const double eps = 10e-10;

int N, M;
double A[MMAX][MMAX];
double X[MMAX];

int main() {
    assert(freopen("gauss.in", "r", stdin));
    assert(freopen("gauss.out", "w", stdout));

    int i, j, k;

    cin >> N >> M;

    for (i = 1; i <= N; ++i)
        for (j = 1; j <= M + 1; ++j)
            cin >> A[i][j];

    int ln = 1, col = 1;
    while (ln <= N && col <= M) {
        for (k = ln; k <= N; ++k)
            if (A[k][col] < -eps || A[k][col] > eps)
                break;

        if (k == N + 1) {
            ++col;
            continue;
        }

        for (i = 1; i <= M + 1; ++i)
            swap(A[ln][i], A[k][i]);

        for (i = col + 1; i <= M + 1; ++i)
            A[ln][i] /= A[ln][col];
        A[ln][col] = 1;

        for (i = ln + 1; i <= N; ++i) {
            if (A[i][col] < -eps || A[i][col] > eps) {
                for (j = col + 1; j <= M + 1; ++j) {
                    A[i][j] -= A[i][col] * A[ln][j];
                }
                A[i][col] = 0;
            }
        }

        ++ln, ++col;
    }

    for (i = N; i >= 1; --i) {
        for (j = 1; j <= M + 1; ++j) {
            if (A[i][j] < -eps || A[i][j] > eps) {
                if (j == M + 1) {
                    cout << "Imposibil\n";
                    return 0;
                }

                X[j] = A[i][M + 1];
                for (k = j + 1; k <= M; ++k)
                    X[j] -= A[i][k] * X[k];

                break;
            }
        }
    }

    cout << fixed << setprecision(10);
    for (i = 1; i <= M; ++i)
        cout << X[i] << ' ';
    cout << '\n';

    return 0;
}
