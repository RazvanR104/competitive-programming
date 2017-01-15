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

ifstream in("evantai.in");
ofstream out("evantai.out");

const int NMAX = 710, MOD = 30103, MAX = 2010;

int N;
int A[NMAX], BIT[NMAX][MAX], AUX[NMAX][NMAX];

inline int LSB(const int value) {
    return (value & -value);
}

inline void update(const int pos, const int sum, const int value) {
    int i, j;
    for (i = pos; i <= N; i += LSB(i))
        for (j = sum; j <= 2000; j += LSB(j)) {
            BIT[i][j] += value;
            if (BIT[i][j] >= MOD) BIT[i][j] -= MOD;
        }
}

inline int query(const int pos, const int sum) {
    int i, j, ret = 0;
    for (i = pos; i >= 1; i -= LSB(i))
        for (j = sum; j >= 1; j -= LSB(j)) {
            ret += BIT[i][j];
            if (ret >= MOD) ret -= MOD;
        }
    return ret;
}

int main() {
    int i, j, res = 0;

    in >> N;
    for(i = 1; i <= N; ++i) in >> A[i];

    for (i = N - 1; i; --i) {
        for (j = i + 1; j <= N; ++j) {
            AUX[i][j] = 1 + query(j - 1, A[i] + A[j] - 1);
            res += AUX[i][j];
            if (res >= MOD) res -= MOD;
        }
        for (j = i + 1; j <= N; ++j) update(j, A[i] + A[j], AUX[i][j]);
    }

    out << res << '\n';
    in.close(), out.close();
    return 0;
}
