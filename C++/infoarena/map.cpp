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
typedef unsigned int uint;

ifstream in("map.in");
ofstream out("map.out");

const int NMAX = 2010, MULT1 = 29, MULT2 = 31;

int N, M;
char MAP[NMAX][NMAX];
uint H1[NMAX], H2[NMAX], pw1[NMAX], pw2[NMAX];

int main() {
    int i, j;

    in >> N >> M;
    in.get();

    for (i = 1; i <= N; ++i) in.getline(MAP[i] + 1, NMAX);

    pw1[0] = pw2[0] = 1;
    for (i = 1; i <= M; ++i) {
        pw1[i] = pw1[i - 1], pw2[i] = pw2[i - 1];
        for (j = 1; j <= N; ++j) {
            pw1[i] *= MULT1;
            pw2[i] *= MULT2;
        }
    }

    for (i = 1; i <= M; ++i) {
        H1[i] = H1[i - 1], H2[i] = H2[i - 1];
        for (j = 1; j <= N; ++j) {
            H1[i] = H1[i] * MULT1 + MAP[j][i] - 'a';
            H2[i] = H2[i] * MULT2 + MAP[j][i] - 'a';
        }
    }

    int res = M;

    for (i = 2; i <= M / 2 + M % 2; ++i) {
        uint hash1, hash2;
        hash1 = H1[M] - pw1[M - i + 1] * H1[i - 1];
        hash2 = H1[M - i + 1];

        if (hash1 != hash2) continue;

        hash1 = H2[M] - pw2[M - i + 1] * H2[i - 1];
        hash2 = H2[M - i + 1];

        if (hash1 != hash2) continue;

        res = min(res, M - i + 1);
    }

    out << res << '\n';

    in.close(), out.close();
    return 0;
}
