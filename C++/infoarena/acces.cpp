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

typedef long long int64;

ifstream in("acces.in");
ofstream out("acces.out");

const int NMAX = 1010;

int N, M, Q;
int A[NMAX][NMAX], DP[NMAX][NMAX];

int main() {
    int i, j, _i, _j;

    in >> N >> M;
    for (i = 1; i <= N; ++i)
        for (j = 1; j <= M; ++j)
            in >> A[i][j];

    for (i = 1; i <= N; ++i)
        for (j = 1; j <= M; ++j) {
            if (A[i][j] == 1) continue;

            if (A[i - 1][j - 1] == 1 && A[i - 1][j] == 0 && A[i][j - 1] == 0) {
                _i = i - 1;
                _j = j - 1;

                while (A[_i][_j - 1] == 1) --_j;
                while (A[_i - 1][_j] == 1) --_i;

                DP[i][j] = 1 + DP[i - 1][j] + DP[i][j - 1] - DP[_i - 1][_j - 1];
            }
            else if (A[i - 1][j] == 0 && A[i][j - 1] == 1) DP[i][j] = 1 + DP[i - 1][j];
            else if (A[i - 1][j] == 1 && A[i][j - 1] == 0) DP[i][j] = 1 + DP[i][j - 1];
            else DP[i][j] = 1 + DP[i - 1][j] + DP[i][j - 1] - DP[i - 1][j - 1];
        }

    for (in >> Q; Q; --Q) {
        in >> i >> j;
        out << DP[i][j] << '\n';
    }

    in.close(), out.close();
    return 0;
}
