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

ifstream in("triunghi6.in");
ofstream out("triunghi6.out");

const int NMAX = 50;

int P, N, K;
int value[NMAX];
vector<int> res;

int main() {
    int i, min_value = 0x7fffffff;

    in >> P >> N >> K;
    for (i = 1; i <= N; ++i) {
        in >> value[i];
        min_value = min(min_value, value[i]);
    }

    if (P == 1) {
        res.push_back(min_value);
        res.push_back(min_value);
    } else {
        for (i = 1; i <= N; ++i)
            res.push_back(value[i]);
        sort(res.begin(), res.end());
    }

    if (P == 1) {
        while((int)res.size() < K)
            res.push_back(res[res.size() - 2] + res[res.size() - 1]);
    } else {
        if (1 + res[0] <= res[1]) {
            res.push_back(1);
            sort(res.begin(), res.end());
        }

        if (1 + res[0] <= res[1] && (int)res.size() < K) {
            res.push_back(1);
            sort(res.begin(), res.end());
        }

        for (i = 1; i < (int)res.size() - 1 && (int)res.size() < K; ++i) {
            int add = res[i - 1] + res[i];
            if (res[i] + add <= res[i + 1]) {
                res.push_back(add);
                sort(res.begin(), res.end());
            }
        }

        while((int)res.size() < K)
            res.push_back(res[res.size() - 2] + res[res.size() - 1]);
    }

    for (i = 0; i < K; ++i)
        out << res[i] << ' ';
    out << '\n';
    in.close(), out.close();
    return 0;
}
