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

ifstream in("palindrom3.in");
ofstream out("palindrom3.out");

const int NMAX = 1000010, DIGITS = 10, MODMAX = 20, oo = 0x3f3f3f3f;

int K;
int MIN[DIGITS][DIGITS], T[DIGITS], P10[NMAX], DP[NMAX][MODMAX];
char P[NMAX], res[NMAX], lit[NMAX][MODMAX], from[NMAX][MODMAX];

int main() {
    int i, len, j, k;

    for (i = 0; i < DIGITS; ++i) in >> T[i];
    in.getline(P + 1, NMAX);
    in.getline(P + 1, NMAX);
    in >> K;

    len = strlen(P + 1);
    P10[0] = 1;
    for (i = 1; i <= len; ++i) P10[i] = P10[i - 1] * 10 % K;

    memset(MIN, oo, sizeof(MIN));
    int cost, dig;
    for (i = 0; i < 10; ++i) {
        cost = 0;
        dig = i;

        while (cost < MIN[i][dig]) {
            MIN[i][dig] = cost++;
            dig = T[dig];
        }
    }

    for (i = len / 2; i; --i)
        for (j = 9; j >= ((i == 1) ? (1) : (0)); --j)
            if (MIN[P[i] - '0'][j] != oo && MIN[P[len - i + 1] - '0'][j] != oo) {
                res[i] = res[len - i + 1] = j + '0';
                break;
            }

    out << res + 1 << '\n';

    memset(DP, oo, sizeof(DP));
    DP[len / 2 + 1][0] = 0;

    for (i = len / 2; i; --i) {
        for (k = 9; k >= ((i == 1) ? (1) : (0)); --k) {
            if (MIN[P[i] - '0'][k] == oo || MIN[P[len - i + 1] - '0'][k] == oo) continue;
            for (j = 0; j < K; ++j) {
                int new_rest = (j + (P10[len - i] + P10[i - 1]) * k) % K;
                int cost = DP[i + 1][j] + MIN[P[i] - '0'][k] + MIN[P[len - i + 1] - '0'][k];
                if (DP[i][new_rest] > cost) {
                    DP[i][new_rest] = cost;
                    from[i][new_rest] = j;
                    lit[i][new_rest] = k + '0';
                }
            }
        }
    }

    int rest = 0;
    for (i = 1; i <= len / 2; ++i) {
        res[i] = res[len - i + 1] = lit[i][rest];
        rest = from[i][rest];
    }

    res[len + 1] = 0;
    out << res + 1;
    out << '\n';

    in.close(), out.close();
    return 0;
}
