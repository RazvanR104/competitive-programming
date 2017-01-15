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

typedef unsigned int uint;

ifstream in("potriveala.in");
ofstream out("potriveala.out");

const int LMAX = 250010, MULT1 = 97, MULT2 = 101;

uint MH1[LMAX], MH2[LMAX], NH1[LMAX], NH2[LMAX], pw1[LMAX], pw2[LMAX];
char N[LMAX], M[LMAX];

int main() {
    in.getline(N + 1, LMAX);
    in.getline(M + 1, LMAX);

    int Nlen = strlen(N + 1), Mlen = strlen(M + 1), i, j, res = 0;
    pw1[0] = pw2[0] = 1;
    for (i = 1; i <= max(Nlen, Mlen); ++i) {
        pw1[i] = pw1[i - 1] * MULT1;
        pw2[i] = pw2[i - 1] * MULT2;

        MH1[i] = MH1[i - 1] * MULT1 + M[i] - 'A';
        MH2[i] = MH2[i - 1] * MULT2 + M[i] - 'A';

        NH1[i] = NH1[i - 1] * MULT1 + N[i] - 'A';
        NH2[i] = NH2[i - 1] * MULT2 + N[i] - 'A';

    }

    int start, finish, mid, pos;
    for (i = 1; i <= Nlen; ++i) {
        start = 1, finish = min(Mlen, i), pos = -1;

        for (mid = (start + finish) >> 1; start <= finish; mid = (start + finish) >> 1) {
            int hash1, hash2;

            hash1 = MH1[Mlen] - pw1[mid] * MH1[Mlen - mid];
            hash2 = NH1[i] - pw1[mid] * NH1[i - mid];

            if (hash1 != hash2) {
                finish = mid - 1;
                continue;
            }

            hash1 = MH2[Mlen] - pw2[mid] * MH2[Mlen - mid];
            hash2 = NH2[i] - pw2[mid] * NH2[i - mid];

            if (hash1 != hash2) finish = mid - 1;
            else {
                pos = mid;
                start = mid + 1;
            }
        }

        if (pos == -1) continue;

        int part_res = pos;

        j = i + 1;
        while(j + Mlen - 1 <= Nlen &&
              MH1[Mlen] == NH1[j + Mlen - 1] - pw1[Mlen] * NH1[j - 1] &&
              MH2[Mlen] == NH2[j + Mlen - 1] - pw2[Mlen] * NH2[j - 1]) {
              j += Mlen;
              part_res += Mlen;
        }

        start = 1, finish = min(Mlen, Nlen - j + 1), pos = -1;
        for (mid = (start + finish) >> 1; start <= finish; mid = (start + finish) >> 1) {
            int hash1, hash2;

            hash1 = MH1[mid];
            hash2 = NH1[j + mid - 1] - pw1[mid] * NH1[j - 1];

            if (hash1 != hash2) {
                finish = mid - 1;
                continue;
            }

            hash1 = MH2[mid];
            hash2 = NH2[j + mid - 1] - pw2[mid] * NH2[j - 1];

            if (hash1 != hash2) finish = mid - 1;
            else {
                pos = mid;
                start = mid + 1;
            }
        }

        if (pos != -1) part_res += pos;
        res = max(res, part_res);
    }

    out << res << '\n';
    in.close(), out.close();
    return 0;
}
