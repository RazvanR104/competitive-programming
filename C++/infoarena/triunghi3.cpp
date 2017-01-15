#include <iostream>
#include <iomanip>
#include <fstream>

#include <algorithm>
#include <bitset>
#include <deque>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <utility>
#include <vector>

#if __cplusplus > 199711L
#include <unordered_map>
#include <unordered_set>
#endif

#include <cstdio>
#include <ctime>
#include <cmath>
#include <cstring>
#include <cstdlib>

using namespace std;

typedef unsigned int uint;

ifstream in("triunghi3.in");
ofstream out("triunghi3.out");

const uint NMAX = 1010, oo = 0xffffffff;

uint N;
uint T[NMAX][NMAX], DP[NMAX][NMAX], SUML[NMAX][NMAX], SUMR[NMAX][NMAX];

int main() {
    uint i, j, _j;

    in >> N;
    for (i = 1; i <= N; ++i)
        for (j = 1; j <= i; ++j)
            in >> T[i][j];

    for (i = 1; i <= N; ++i)
        for (j = N; j >= i; --j)
            SUML[i][N - j + 1] = SUML[i][N - j] + T[j][i];

    for (j = 1; j <= N; ++j)
        for (i = N, _j = N - j + 1; i >= 1 && _j >= 1; --i, --_j)
            SUMR[j][N - i + 1] = SUMR[j][N - i] + T[i][_j];

    memset(DP, oo, sizeof(DP));
    DP[0][0] = 0;

    for (i = 0; i <= N; ++i) {
        for (j = 0; j <= N && i + j < N; ++j) {
            if (i == j && i == 0) continue;
            if (i == 0 && j)
                DP[0][j] = DP[0][j - 1] + (SUMR[j][N - j + 1] + SUMR[j + 1][N - j] - T[N][N - j + 1]) * (N - j) + 2 * SUMR[j][N - j + 1] - T[N][N - j + 1] - T[j][1];
            else if (i && j == 0)
                DP[i][0] = DP[i - 1][0] + (SUML[i][N - i + 1] + SUML[i + 1][N - i] - T[N][i]) * (N - i) + 2 * SUML[i][N - i + 1] - T[N][i] - T[i][i];
            else
                DP[i][j] = min(DP[i - 1][j] + (SUML[i][N - i - j + 1] + SUML[i + 1][N - i - j] - T[N][i]) * (N - i - j) + 2 * SUML[i][N - i - j + 1] - T[N][i] - T[i + j][i],
                               DP[i][j - 1] + (SUMR[j][N - i - j + 1] + SUMR[j + 1][N - i - j] - T[N][N - j + 1]) * (N - i - j) + 2 * SUMR[j][N - i - j + 1] - T[N][N - j + 1] - T[i + j][i + 1]);
        }
    }

    uint res = oo;
    for (i = 0; i < N; ++i)
        res = min(res, DP[i][N - i - 1]);

    out << res << '\n';
    in.close(), out.close();
    return 0;
}
