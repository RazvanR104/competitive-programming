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

ifstream in("perioada2.in");
ofstream out("perioada2.out");

const int NMAX = 10000010;
const int MOD[] = { 0, 666013, 666431, 667421 }, MULT[] = { 0, 1039, 1049, 1051 };

int N;
int hash1, hash2, hash3;
char str[NMAX];

void euclid(int64 &x, int64 &y, int a, int b) {
    if (b == 0) x = 1, y = 0;
    else {
        euclid(x, y, b, a % b);
        int64 aux = x;
        x = y;
        y = aux - y * (a / b);
    }
}

int fast_expo(int base, int expo, int MOD) {
    int ret = 1;
    while(expo) {
        if (expo & 1) ret = 1LL * ret * base % MOD;
        base = 1LL * base * base % MOD;
        expo >>= 1;
    }
    return ret;
}

int make_hash(int phash, int length, int MULT, int MOD) {
    int ret_hash, second;

    ret_hash = fast_expo(MULT, N, MOD) - 1;
    if (ret_hash < 0) ret_hash += MOD;

    second = fast_expo(MULT, length, MOD) - 1;
    if (second < 0) second += MOD;

    int64 inv = 0, ins;
    euclid(inv, ins, second, MOD);
    if (inv < 0) inv = inv % MOD + MOD;

    ret_hash = 1LL * ret_hash * phash % MOD;
    ret_hash = ret_hash * inv % MOD;

    return ret_hash;
}

int main() {
    int i, j, nrp = 0;

    in >> N;
    in.getline(str + 1, NMAX);
    in.getline(str + 1, NMAX);

    for (i = 1; i <= N; ++i) {
        hash1 = (hash1 * MULT[1] + str[i]) % MOD[1];
        hash2 = (hash2 * MULT[2] + str[i]) % MOD[2];
        hash3 = (hash3 * MULT[3] + str[i]) % MOD[3];
    }

    int curr_hash1 = 0, curr_hash2 = 0, curr_hash3 = 0;
    for (i = 1; i < N; ++i) {
        curr_hash1 = (curr_hash1 * MULT[1] + str[i]) % MOD[1];
        curr_hash2 = (curr_hash2 * MULT[2] + str[i]) % MOD[2];
        curr_hash3 = (curr_hash3 * MULT[3] + str[i]) % MOD[3];
        if (N % i) continue;

        if (hash1 != make_hash(curr_hash1, i, MULT[1], MOD[1])) continue;
        if (hash2 != make_hash(curr_hash2, i, MULT[2], MOD[2])) continue;
        if (hash3 != make_hash(curr_hash3, i, MULT[3], MOD[3])) continue;

        for (j = 1; j * i < N; ++j)
            if (N % (i * j) == 0) ++nrp;
        break;
    }

    out << nrp << '\n';
    in.close(), out.close();
    return 0;
}
