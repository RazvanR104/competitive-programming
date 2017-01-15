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

ifstream in("virus.in");
ofstream out("virus.out");

const int LMAX = 100010, KMAX = 1010, MULT1 = 2, MULT2 = 3;

int N, L, K;
uint H1[LMAX], H2[LMAX], pw1[KMAX] = { 1 }, pw2[KMAX] = { 1 };
char str[LMAX], match[KMAX];

int main() {
    int i;

    in >> N >> L;
    in.getline(str + 1, LMAX);
    in.getline(str + 1, LMAX);

    for (i = 1; i < KMAX; ++i) pw1[i] = pw1[i - 1] * MULT1, pw2[i] = pw2[i - 1] * MULT2;
    for (i = 1; i <= N; ++i) {
        H1[i] = H1[i - 1] * MULT1 + str[i] - '0';
        H2[i] = H2[i - 1] * MULT2 + str[i] - '0';
    }

    while(L--) {
        in >> K;
        in.getline(match + 1, LMAX);
        in.getline(match + 1, LMAX);

        uint hash1 = 0, hash2 = 0;
        for (i = 1; i <= K; ++i) {
            hash1 = hash1 * MULT1 + match[i] - '0';
            hash2 = hash2 * MULT2 + match[i] - '0';
        }

        int res = 0;
        for (i = K; i <= N; ++i) {
            if (H1[i] - pw1[K] * H1[i - K] == hash1 &&
                H2[i] - pw2[K] * H2[i - K] == hash2)
                ++res;
        }

        out << res << '\n';
    }

    in.close(), out.close();
    return 0;
}
