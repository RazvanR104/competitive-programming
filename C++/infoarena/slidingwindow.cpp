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

ifstream in("slidingwindow.in");
ofstream out("slidingwindow.out");

const int NMAX = 1000010, inf = 0x3f3f3f3f;

int N, D;
pair<int, int> A[NMAX];

struct compare {
    bool operator()(const pair<int, int> &lhs, const pair<int, int> &rhs) {
        if (lhs.first < rhs.first) return true;
        if (lhs.first > rhs.first) return false;
        if (lhs.second < rhs.second) return true;
        return false;
    }
};

int main() {
    int i;

    in >> N >> D;
    for (i = 1; i <= N; ++i) {
        in >> A[i].first;
        A[i].second = i;
    }
    sort(A + 1, A + N + 1, compare());

    int res = inf;

    for (i = 1; i <= N; ++i) {
        if (A[i + 1].second - A[i].second <= D && A[i + 1].second - A[i].second >= -D &&
            A[i + 1].first - A[i].first < res)
            res = A[i + 1].first - A[i].first;
    }

    out << res << '\n';

    in.close(), out.close();
    return 0;
}
