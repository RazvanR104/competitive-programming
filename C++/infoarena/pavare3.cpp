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

#include <cassert>
#include <cstdio>
#include <ctime>
#include <cmath>
#include <cstring>
#include <cstdlib>

using namespace std;

typedef long long int64;

ifstream in("pavare3.in");
ofstream out("pavare3.out");

const int NMAX = 160;
const int INSERT[][3] = { { 1, 1, 2 }, { 1, 2, 2 }, { 1, 1, 2 }, { 1, 2, 2 } };

int N, M;
int MAT[NMAX][NMAX];

int main() {
    int i, j, k, l, Area = 0, add = 0, new_add = -1;
    bool Rotate = false;

    in >> N >> M;
    if (N > M) {
        swap(N, M);
        Rotate = true;
    }

    for (i = 1; i <= N; i += 4) {
        if (Area + 12 > N * M / 2) break;
        for (j = 1; j <= M; j += 3) {
            if (Area + 12 > N * M / 2) break;
                for (k = 0; k < 4; ++k) {
                    for (l = 0; l < 3; ++l) {
                        MAT[i + k][j + l] = INSERT[k][l] + add;
                        new_add = max(new_add, INSERT[k][l] + add);
                    }
                }
                Area += 12;
                add = new_add;
        }
    }

   /* for (i = 2; MAT[i][M - M % 3]; i += 2)
        for (j = 1; j <= M % 3; ++j)
            MAT[i - 1][M - M % 3 + j] = MAT[i][M - M % 3 + j] = ++add;

    for (k = 1; k <= M; ++k)
        if (MAT[i][k] == 0) break;

    for ( ; MAT[i][k - 1]; i += 2)
        for (j = k; j <= M; ++j)
            MAT[i - 1][j] = MAT[i][j] = ++add;

    if (MAT[i - 1][k - 1] == 0) --i;

    if (M % 2 == 0) {
        for ( ; i <= N; ++i)
            for (j = 1; j <= M; j += 2)
                MAT[i][j] = MAT[i][j + 1] = ++add;
    } else {
        for (++j; i <= N; i += 2)
            for (j = 1; j <= M; ++j)
                MAT[i - 1][j] = MAT[i][j] = ++add;
    }*/

    if (Rotate) swap(N, M);
    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= M; ++j)
            if (Rotate) out << MAT[j][i] << ' ';
            else out << MAT[i][j] << ' ';
        out << '\n';
    }
    in.close(), out.close();
    return 0;
}
