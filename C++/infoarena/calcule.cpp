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

ifstream in("calcule.in");
ofstream out("calcule.out");

const int NMAX = 100010, KMAX = 50010, MOD = 20011;

int N, K, pos = -1;
int Part[NMAX], R[KMAX];

int BinSearch(int value) {
    int ret = -1, left = 0, right = pos, mid;

    for (mid = (left + right) / 2; left <= right; mid = (left + right) / 2) {
        if (value > Part[mid]) {
            ret = mid;
            right = mid - 1;
        } else left = mid + 1;
    }

    return ((ret == -1) ? (pos + 1) : (ret));
}

int main() {
    int i, sum = 0, value, _pos, res = 0;

    in >> N >> K;
    for (i = 1; i <= N; ++i) {
        in >> value;
        sum += value;
        sum %= K;
        ++R[sum];
        if (R[sum] >= MOD) R[sum] -= MOD;

        _pos = BinSearch(value);

        if (_pos > pos) Part[++pos] = value;
        else Part[_pos] = value;
    }

    out << pos + 1 << '\n';

    res = (R[0] * (R[0] + 1) / 2) % MOD;
    for (i = 1; i < K; ++i)
        res = (res + R[i] * (R[i] - 1) / 2) % MOD;

    out << res << '\n';
    in.close(), out.close();
    return 0;
}
