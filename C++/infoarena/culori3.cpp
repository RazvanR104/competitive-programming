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

ifstream in("culori3.in");
ofstream out("culori3.out");

int N;

struct HugeNumber {
    char num[1200];
    int length;

    HugeNumber() { length = 0; }

    void operator+=(const HugeNumber &rhs) {
        size_t i, t = 0;
        for(i = 1; i <= length || i <= rhs.length || t; ++i, t /= 10)
            num[i] = (t += ((i <= length) ? (num[i]) : (0)) + ((i <= rhs.length) ? (rhs.num[i]) : (0))) % 10;
        length = i - 1;
    }
} DP1[5], DP2[5], res;

int pos;
char show[1200];

int main() {
    int i;

    in >> N;
    for (i = 0; i < 5; ++i)
        DP1[i].length = DP1[i].num[1] = 1;

    for (i = 1; i < N; ++i) {
        if (i % 2) {
        DP2[0] += DP1[1];
        DP2[1] += DP1[0];
        DP2[1] += DP1[2];
        DP2[2] += DP1[1];
        DP2[2] += DP1[3];
        DP2[3] += DP1[2];
        DP2[3] += DP1[4];
        DP2[4] += DP1[3];
        } else {
        DP1[0] += DP2[1];
        DP1[1] += DP2[0];
        DP1[1] += DP2[2];
        DP1[2] += DP2[1];
        DP1[2] += DP2[3];
        DP1[3] += DP2[2];
        DP1[3] += DP2[4];
        DP1[4] += DP2[3];
        }

        for (int j = 0; j < 5; ++j)
            if (i % 2) DP1[j].length = 0; else
            DP2[j].length = 0;
    }

    for (i = 0; i < 5; ++i) res += ((N % 2) ? (DP1[i]) : (DP2[i]));

    for (i = res.length; i >= 1; --i) show[pos++] = res.num[i] + '0';
    out << show << '\n';
    in.close(), out.close();
    return 0;
}
