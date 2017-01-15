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

ifstream in("stiva3.in");
ofstream out("stiva3.out");

const int DMAX = 50010, TESTS = 5, oo = 0x7fffffff;

int K, top;
int E[DMAX], ST[DMAX];

int main() {
    int i, T, Min, pos;
    bool is;

    in >> K;
    for (T = 0; T < TESTS; ++T) {
        Min = oo;
        for (i = 1; i <= K; ++i) {
            in >> E[i];
            Min = min(Min, E[i]);
        }

        for (i = 1; i <= K; ++i)
            E[i] -= Min;

        pos = 1;
        top = 0;
        ST[top] = 0;
        is = false;

        for (i = 1; i < DMAX; ++i) {
            while (top >= 0 && pos <= K && ST[top] == E[pos]) {
                --top;
                ++pos;
            }

            if (pos > K) {
                is = true;
                break;
            }

            ST[++top] = i;
        }

        if (is) out << "1\n";
        else out << "0\n";
    }

    in.close(), out.close();
    return 0;
}
