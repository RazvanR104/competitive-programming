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

ifstream in("pscpld.in");
ofstream out("pscpld.out");

const int LMAX = 1000010;

int DP[2 * LMAX];
char str[LMAX], parsed[2 * LMAX];

int main() {
    int i, j, pos = 0;
    int64 res = 0;

    in.getline(str, LMAX);

    parsed[0] = '$';
    for(i = 0; str[i]; ++i) {
        parsed[++pos] = str[i];
        DP[pos] = 1;
        parsed[++pos] = '$';
    }

    int C = 0, R = 0;
    for(j = 1; j < pos; ++j) {
        int mirror = 2 * C - j;

        if(j <= R)
            DP[j] = min(DP[mirror], R - j + 1);

        int left = j - DP[j] + 1;
        int right = j + DP[j] - 1;

        while(left - 2 >= 1 && right + 2 < pos && parsed[left - 2] == parsed[right + 2]) {
            left -= 2;
            right += 2;
            DP[j] += 2;
        }

        if (right > R) {
            C = j;
            R = right;
        }

        res += (DP[j] + 1) / 2;
    }

    out << res << '\n';
    in.close(), out.close();
    return 0;
}
