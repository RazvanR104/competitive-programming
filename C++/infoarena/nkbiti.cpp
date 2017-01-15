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

ifstream in("nkbiti.in");
ofstream out("nkbiti.out");

const int MOD = 666777, KMAX = 45;

int N, K;
int DP[KMAX][KMAX], res[KMAX][KMAX], aux[KMAX][KMAX];

void Expo(int A[][KMAX], int B[][KMAX], int res[][KMAX]) {
    int i, j, k;
    for (i = 0; i <= K; ++i)
        for (j = 0; j <= K; ++j)
            for (k = 0; k <= K; ++k)
                res[i][j] = (res[i][j] + 1LL * A[i][k] * B[k][j]) % MOD;
}

void FastExpo(int expo) {
    while (expo) {
        if (expo & 1) {
            memset(aux, 0, sizeof(aux));
            Expo(res, DP, aux);
            memcpy(res, aux, sizeof(res));
        }
        memset(aux, 0, sizeof(aux));
        Expo(DP, DP, aux);
        memcpy(DP, aux, sizeof(DP));
        expo >>= 1;
    }
}

int main() {
    int i;

    in >> N >> K;

    for (i = 0; i <= K; ++i)
        res[i][i] = 1;

    for (i = 0; i <= K; ++i)
        DP[i][0] = 1;

    for (i = 1; i <= K; ++i)
        DP[i - 1][i] = 1;

    FastExpo(N + 1);
    out << res[0][0] << '\n';

    in.close(), out.close();
    return 0;
}
