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

ifstream in("puteri4.in");
ofstream out("puteri4.out");

const int MAX = 1000000000;
const int64 oo = 0x7fffffffffffffffLL;

int T;
int64 X, Y;

/*int64 FastExpo(int64 base, int expo) {
    int64 res = 1, prev, prev_base;
    while (expo) {
        if (expo & 1) {
            prev = res;
            res *= base;
            if (res / base != prev) return oo;
        }

        prev_base = base;
        base *= base;
        if (base / prev_base != prev_base) return oo;
        expo >>= 1;
    }
    return res;
}*/

int64 Expo(int64 base, int expo) {
    int64 ret = 1, prev;

    while (expo--) {
        prev = ret;
        ret *= base;
        if (ret / base != prev) return oo;
    }
    return ret;
}

bool not_prime(int value) {
    for (int i = 2; i < value; ++i)
        if (value % i == 0)
            return true;
    return false;
}

int64 Compute(int64 value, int limit = 61) {
    int64 i, ret = 0, left, right, mid, res;
    int64 power;
    for (i = 2; i < limit; ++i) {
        if (not_prime(i)) continue;
        left = 2, right = value;
        res = 0;
        for (mid = (left + right) / 2; left <= right; mid = (left + right) / 2) {
            power = Expo(mid, i);
            if (power <= value) {
                res = mid;
                left = mid + 1;
            } else right = mid - 1;
        }

        if (res > 1) {
            ret += res - 1;
            ret -= Compute(res, i);
        } else break;
    }
    return ret;
}

int main() {
    for (in >> T; T; --T) {
        in >> X >> Y;
        int64 res = Compute(Y) - Compute(X - 1);
        if (X == 1) ++res;
        out << res << '\n';
    }

    in.close(), out.close();
    return 0;
}
