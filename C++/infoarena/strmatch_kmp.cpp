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

ifstream in("strmatch.in");
ofstream out("strmatch.out");

const int LMAX = 2000010, RMAX = 1024;

int nexxt[LMAX], res[RMAX], Alen;
char A[LMAX], B[LMAX];

void make_prefix() {
    int i, q = 0;

    for (i = 2; A[i]; ++i) {
        while(q && A[q + 1] != A[i])
            q = nexxt[q];
        if (A[q + 1] == A[i]) ++q;
        nexxt[i] = q;
    }

    Alen = i - 1;
}

int main() {
    int i, q = 0;

    in.getline(A + 1, LMAX);
    in.getline(B + 1, LMAX);

    make_prefix();

    for (i = 1; B[i]; ++i) {
        while(q && A[q + 1] != B[i])
            q = nexxt[q];
        if (A[q + 1] == B[i]) ++q;
        if (q == Alen) {
            ++res[0];
            if (res[0] <= 1000)
                res[res[0]] = i - Alen;
        }
    }

    out << res[0] << '\n';
    for (i = 1; i <= min(res[0], 1000); ++i)
        out << res[i] << ' ';
    out << '\n';

    in.close(), out.close();
    return 0;
}
