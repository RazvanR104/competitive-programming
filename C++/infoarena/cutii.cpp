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

ifstream in("cutii.in");
ofstream out("cutii.out");

const int NMAX = 3510;

int N, T;
int BIT[NMAX][NMAX];
struct Box {
    int X, Y, Z;

    bool operator<(const Box &rhs) const {
        if (X < rhs.X) return true;
        return false;
    }
} B[NMAX];

inline int LSB(const int value) {
    return (value & -value);
}

inline void update(const int Y, const int Z, const int value) {
    int i, j;
    for (i = Y; i <= N; i += LSB(i))
        for (j = Z; j <= N; j += LSB(j))
            BIT[i][j] = max(BIT[i][j], value);
}

inline int query(const int Y, const int Z) {
    int i, j, ret = 0;
    for (i = Y; i >= 1; i -= LSB(i))
        for (j = Z; j >= 1; j -= LSB(j))
            ret = max(ret, BIT[i][j]);
    return ret;
}

inline void destroy() {
    int i, j, k;
    for (i = 1; i <= N; ++i)
        for (j = B[i].Y; j <= N; j += LSB(j))
            for (k = B[i].Z; k <= N; k += LSB(k))
                BIT[j][k] = 0;
}

int main() {
    int i;
    in >> N >> T;

    while(T--) {
        for (i = 1; i <= N; ++i) in >> B[i].X >> B[i].Y >> B[i].Z;
        sort(B + 1, B + N + 1);

        int res = 0;
        for (i = 1; i <= N; ++i) {
            int value = query(B[i].Y - 1, B[i].Z - 1);
            update(B[i].Y, B[i].Z, value + 1);
            res = max(res, value + 1);
        }

        out << res << '\n';
        destroy();
    }

    in.close(), out.close();
    return 0;
}
