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

ifstream in("perioada01.in");
ofstream out("perioada01.out");

const int NMAX = 1000010;

int N, P;
int pos[NMAX];

int main() {
    int i, j, k, sz, nr1;
    bool done = false;

    in >> N >> P;
    for (i = 1; i <= P; ++i) in >> pos[i];
    pos[P + 1] = pos[1] + N;

    for (i = P; i > 1; --i) {
        if (N % i || P % i) continue;
        sz = N / i, nr1 = P / i;

        done = true;
        for (j = 1; j * nr1 < P; ++j) {
            if (pos[j * nr1 + 1] - j * sz != pos[1]) {
                done = false;
                break;
            }
            for (k = j * nr1 + 2; k <= (j + 1) * nr1 + 1; ++k)
                if (pos[k] - pos[k - 1] != pos[k - j * nr1] - pos[k - j * nr1 - 1]) {
                    done = false;
                    break;
                }
            if (!done) break;
        }

        if (done) break;
    }

    if (!done) out << "-1\n";
    else out << sz;
    in.close(), out.close();
    return 0;
}
