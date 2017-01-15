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

typedef pair<int, int> PII;
const int NMAX = 710, MOD = 30103;

int N;
int A[NMAX], BIT[NMAX][NMAX], next[NMAX][NMAX];
PII sorted[NMAX * NMAX];

struct compare {
    bool operator()(const PII &lhs, const PII &rhs) const {
        if (lhs.x <= rhs.x && lhs.y >= rhs.y) return true;
        return false;
    }
};

inline void update(int x, int y, int val) {
    while(x <= N) {
        int cy = y;
        while(cy <= N) {
            BIT[x][cy] += val;
            cy += (cy & -cy);
        }
        x += (x & -x);
    }
}

inline int query(int x, int y) {
    int ret = 0;

    while(x <= N) {
        int cy = y;
        while(cy <= N) {
            ret += BIT[x][cy];
            cy -= (cy & -cy);
        }
        x -= (x & -x);
    }

    return ret;
}

int main() {
    int i, j, value;

    in >> N;
    for (i = 1; i <= N; ++i) in >> A[i];

    for (i = N - 1; i; --i) {
        for (j = i + 1; j <= N; ++j) {
            update(i, j, 1);
            //value = query()
        }
    }

    in.close(), out.close();
    return 0;
}
