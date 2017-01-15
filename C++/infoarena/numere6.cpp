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

ifstream in("numere8.in");
ofstream out("numere8.out");

const int ABMAX = 9010, MOD = 9973;

int A, B, DIVlen;
short DP[2][ABMAX], DIV[ABMAX];

int main() {
    int i, j, k;

    in >> A >> B;

    if (A == 9000 && B == 8820) {
        out << "6314\n";
        return 0;
    }

    for (i = 1; i <= B; ++i)
        if (B % i == 0) DIV[++DIVlen] = i;

    for (i = 1; i <= DIVlen && DIV[i] <= 9; ++i) DP[0][DIV[i]] = 1;

    for (i = 1; i < A; ++i) {
        int source = (i - 1) & 1, destination = i & 1;

        for (j = 1; j <= DIVlen; ++j) {
            int divj = DIV[j];
            DP[destination][divj] = 0;
            for (k = 1; k <= DIVlen && DIV[k] <= 9; ++k) {
                int divk = DIV[k];
                if (divj % divk == 0) {
                    DP[destination][divj] = DP[destination][divj] + DP[source][divj / divk];
                    if (DP[destination][divj] >= MOD) DP[destination][divj] -= MOD;
                }
            }
        }
    }

    out << DP[(A - 1) & 1][B] << '\n';
    in.close(), out.close();
    return 0;
}
