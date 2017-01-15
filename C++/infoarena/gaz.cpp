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

ifstream in("gaz.in");
ofstream out("gaz.out");

const int NMAX = 2010, oo = 0x3f3f3f3f;

int L, P, D, C, N;
int64 G[NMAX], DP[NMAX];

int main() {
    int64 i, j, sum = 0, _sum, night;

    in >> L >> P >> D >> C >> N;
    for (i = 1; i <= N; ++i) {
        in >> G[i];
        sum += G[i];
    }

    memset(DP, oo, sizeof(DP));
    DP[0] = 0;

    for (i = 1; i <= N; ++i) {
        _sum = G[i];
        night = 0;
        for (j = i - 1; j >= 0; --j) {
            DP[i] = min(DP[i], DP[j] + night * C + P);
            night = max(0LL, _sum - L);
            _sum += G[j];
        }
    }

    out << DP[N] + sum * D << '\n';
    in.close(), out.close();
    return 0;
}
