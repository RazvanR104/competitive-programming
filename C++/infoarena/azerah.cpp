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

ifstream in("azerah.in");
ofstream out("azerah.out");

const int MOD = 1000000007, NMAX = 1000010;

int T, N;
int DP[2][NMAX];

int main() {
    int i, num;

    for (in >> T; T; --T) {
        in >> N;

        DP[0][0] = 1;
        DP[1][0] = 0;

        for (i = 1; i <= N; ++i) {
            in >> num;
            if (num % 2 == 0) {
                DP[0][i] = 2 * DP[0][i - 1];
                DP[1][i] = 2 * DP[1][i - 1];

                if (DP[0][i] >= MOD) DP[0][i] -= MOD;
                if (DP[1][i] >= MOD) DP[1][i] -= MOD;
            } else {
                DP[0][i] = DP[0][i - 1] + DP[1][i - 1];
                DP[1][i] = DP[0][i - 1] + DP[1][i - 1];

                if (DP[0][i] >= MOD) DP[0][i] -= MOD;
                if (DP[1][i] >= MOD) DP[1][i] -= MOD;
            }
        }

        out << DP[0][N] - 1 << '\n';
    }

    in.close(), out.close();
    return 0;
}
