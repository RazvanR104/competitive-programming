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

ifstream in("prefix2.in");
ofstream out("prefix2.out");

typedef long long int64;

const int NMAX = 100010;

int N, gap, limit;
int sa[NMAX], pos[NMAX], tmp[NMAX], lcp[NMAX];
int64 res[NMAX];
char S[NMAX];

struct compare {
    bool operator()(const int &i, const int &j) const {
        if (pos[i] != pos[j])
            return pos[i] < pos[j];
        return (i + gap < limit && j + gap < limit) ? (pos[i + gap] < pos[j + gap]) : (i > j);
    }
};

void build() {
    int i;
    for (i = 0; i < limit; ++i)
        sa[i] = i, pos[i] = S[i];
    for (gap = 1; ; gap *= 2) {
        sort(sa, sa + limit, compare());
        for (i = 0; i < limit - 1; ++i) tmp[i + 1] = tmp[i] + compare()(sa[i], sa[i + 1]);
        for (i = 0; i < limit; ++i) pos[sa[i]] = tmp[i];
        if (tmp[limit - 1] == limit - 1) break;
    }
}

void build_LCP() {
    for (int i = 0, k = 0; i < limit; ++i) {
        if (pos[i] == limit - 1) continue;
        for (int j = sa[pos[i] + 1]; S[i + k] == S[j + k]; ) ++k;
        lcp[pos[i]] = k;
        if (k) --k;
    }
}

int main() {
    int i, j;

    in.getline(S, NMAX);
    N = strlen(S);

    for (limit = 1; limit <= N; ++limit) {
        build();
        build_LCP();
        int sum = 0;
        for (j = 0; j < limit - 1; ++j) {
            sum += lcp[j];
        }

        res[limit] = 1LL * limit * (limit + 1) / 2 - sum;
    }

    for (i = 1; i <= N; ++i) out << res[i] << '\n';
    in.close(), out.close();
    return 0;
}
