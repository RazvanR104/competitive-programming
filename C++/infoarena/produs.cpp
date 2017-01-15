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

ifstream in("produs.in");
ofstream out("produs.out");

const int NMAX = 510, CMAX = 210;

int N, K, C;
int aux[NMAX], digits[NMAX], from[NMAX][NMAX], path[CMAX], num[NMAX][NMAX];
double DP[2][NMAX];

void Multiply(int *A, int B, int *RES) {
    int i;
    int64 t = 0;

    for (i = 1; i <= A[0] || t; ++i, t /= 10)
        RES[i] = (t += 1LL * ((i <= A[0]) ? (A[i]) : (0)) * B) % 10;
    RES[0] = i - 1;
}

bool Compare(const int *A, const int *B) { //returns true if A > B
    if (A[0] > B[0]) return true;
    if (A[0] < B[0]) return false;

    for (int i = A[0]; i >= 1; --i) {
        if (A[i] > B[i]) return true;
        if (A[i] < B[i]) return false;
    }

    return false;
}

int main() {
    int i, j, k;

    in >> N >> K >> C;
    for (i = 1; i <= N; ++i) in >> digits[i];

    for (i = 1; i <= N; ++i)
        for (j = i; j <= N; ++j)
            num[i][j] = num[i][j - 1] * 10 + digits[j];

    for (i = 1; i <= C; ++i) {
        /*DP[0][i][0] = i;
        for (j = 1; j <= i; ++j) DP[0][i][j] = digits[j];
        reverse(DP[0][i] + 1, DP[0][i] + i + 1);*/
        DP[0][i] = log((double)num[1][i]);
    }

    for (k = 1; k <= K; ++k) {
        int source = (k - 1) % 2, destination = k % 2;

        for (i = k + 1; i <= N; ++i)
            for (j = 1; j <= C && i - j >= k; ++j) {
                if (digits[i - j + 1] == 0 || DP[source][i - j] == 0) continue;
                /*Multiply(DP[source][i - j], num[i - j + 1][i], aux);
                if (Compare(aux, DP[destination][i])) {
                    memcpy(DP[destination][i], aux, sizeof(int) * (DP[destination][i][0] + 1));
                    from[k][i] = i - j;
                }*/
                if (DP[source][i - j] + log((double)num[i - j + 1][i]) > DP[destination][i]) {
                    DP[destination][i] = DP[source][i - j] + log((double)num[i - j + 1][i]);
                    from[k][i] = i - j;
                }
            }
        memset(DP[source], 0, sizeof(DP[source]));
    }

    path[++path[0]] = from[K][N];
    for (i = K - 1; i >= 1; --i) {
        path[path[0] + 1] = from[i][path[path[0]]];
        ++path[0];
    }

    for (i = 1; i <= N; ++i) {
        out << digits[i];
        if (i == path[path[0]]) {
            out << '*';
            --path[0];
        }
    }

    out << '\n';
    in.close(), out.close();
    return 0;
}
