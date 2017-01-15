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

ifstream in("kfib.in");
ofstream out("kfib.out");

const int MOD = 666013;

int K;
int A[2][2], B[2][2], RES[2][2];

inline void multiply(int A[][2], int B[][2], int RES[][2]) {
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
            for (int k = 0; k < 2; ++k)
                RES[i][j] = (RES[i][j] + 1LL * A[i][k] * B[k][j] % MOD) % MOD;
}

int main() {
    in >> K;

    A[0][0] = 0, A[0][1] = 1, A[1][0] = 1, A[1][1] = 1;
    RES[0][0] = RES[1][1] = 1;
    --K;
    for (int bit = 0; (1 << bit) <= K; ++bit) {
        if (K & (1 << bit)) {
            memset(B, 0, sizeof(B));
            multiply(RES, A, B);
            memcpy(RES, B, sizeof(RES));
        }

        memset(B, 0, sizeof(B));
        multiply(A, A, B);
        memcpy(A, B, sizeof(A));
    }

    out << RES[1][1] << '\n';

    in.close(), out.close();
    return 0;
}
