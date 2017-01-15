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

ifstream in("stramosi.in");
ofstream out("stramosi.out");

const int NMAX = 250010, LOG2NMAX = 20;

int N, M;
int ancestor[LOG2NMAX][NMAX];

int main() {
    int i, j, anc;
    in >> N >> M;

    for (i = 1; i <= N; ++i) {
        in >> anc;
        ancestor[0][i] = anc;
    }

    for (i = 1; (1 << i) < N; ++i)
        for (j = 1; j <= N; ++j)
            ancestor[i][j] = ancestor[i - 1][ancestor[i - 1][j]];

    while(M--) {
        in >> i >> j;
        for (int bit = 0; j && (1 << bit) < N; ++bit)
            if (j & (1 << bit)) {
                i = ancestor[bit][i];
                j -= (1 << bit);
            }
        out << i << '\n';
    }

    in.close(), out.close();
    return 0;
}
