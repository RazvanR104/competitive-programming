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

ifstream in("flori4.in");
ofstream out("flori4.out");

const int NMAX = 10010, MOD = 9001;

int N;
int DP[NMAX];

int main() {
    int i, j, sum;

    in >> N;
    if (N == 1) {
        out << "1\n";
        return 0;
    }

    DP[1] = DP[2] = 1;
    sum = 1;

    for (i = 3; i <= N; ++i) {
        DP[i] = (sum + 1) % MOD;
        sum += DP[i - 1];
        sum %= MOD;
    }

    sum += DP[N];
    sum %= MOD;

    out << sum << '\n';
    in.close(), out.close();
    return 0;
}
