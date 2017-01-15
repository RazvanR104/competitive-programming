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

ifstream in("poly2.in");
ofstream out("poly2.out");

const int MOD = 30103;
int N;

void GCD(int64 &x, int64 &y, int a, int b) {
     if (!b) x = 1, y = 0;
     else {
         GCD(x, y, b, a % b);
         int64 aux = x;
         x = y;
         y = aux - y * (a / b);
     }
}

int main() {
    int i;
    int64 A = 1, B = 1, C = 1;

    in >> N;
    for (i = 2; i <= 2 * N; ++i) A = (A * i) % MOD;
    for (i = 2; i <= N; ++i) B = (B * i) % MOD;
    C = (B * i) % MOD;

    int64 inv = 0, ins;
    GCD(inv, ins, B, MOD);
    if (inv <= 0) inv = inv % MOD + MOD;
    A = (A * inv) % MOD;

    inv = 0;
    GCD(inv, ins, C, MOD);
    if (inv <= 0) inv = inv % MOD + MOD;
    A = (A * inv) % MOD;

    out << A << '\n';

    in.close(), out.close();
    return 0;
}
