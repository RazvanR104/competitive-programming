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

ifstream in("parpal.in");
ofstream out("parpal.out");

const int NMAX = 1000010, MULT1 = 29, MULT2 = 31;

int T;
uint H1[NMAX], H2[NMAX], pw1[NMAX], pw2[NMAX], RH1[NMAX], RH2[NMAX];
char N[NMAX];

bool verify(const int &start, const int &finish) {
    uint hash1, hash2;

    hash1 = H1[finish] - pw1[finish - start + 1] * H1[start - 1];
    hash2 = RH1[start] - pw1[finish - start + 1] * RH1[finish + 1];

    if (hash1 != hash2) return false;

    hash1 = H2[finish] - pw2[finish - start + 1] * H2[start - 1];
    hash2 = RH2[start] - pw2[finish - start + 1] * RH2[finish + 1];

    if (hash1 != hash2) return false;

    return true;
}

int main() {
    freopen("parpal.in", "r", stdin);

    int i, j;

    pw1[0] = pw2[0] = 1;
    for (i = 1; i < NMAX; ++i) {
        pw1[i] = pw1[i - 1] * MULT1;
        pw2[i] = pw2[i - 1] * MULT2;
    }

    for (scanf("%d\n", &T); T; --T) {
        gets(N + 1);
        int len = strlen(N + 1);

        for (i = 1, j = len; i <= len; ++i, --j) {
            H1[i] = H1[i - 1] * MULT1 + N[i] - 'a';
            H2[i] = H2[i - 1] * MULT2 + N[i] - 'a';

            RH1[j] = RH1[j + 1] * MULT1 + N[j] - 'a';
            RH2[j] = RH2[j + 1] * MULT2 + N[j] - 'a';
        }

        int pos = 1;

        while(pos <= len) {
            for (i = pos + 1; i <= len; i += 2)
                if (verify(pos, i)) {
                    pos = i + 1;
                    break;
                }
            if (i > len) break;
        }

        if (pos == len + 1) out << "DA\n";
        else out << "NU\n";
    }

    in.close(), out.close();
    return 0;
}
