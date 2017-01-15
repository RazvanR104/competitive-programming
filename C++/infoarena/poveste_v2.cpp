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

ifstream in("poveste.in");
ofstream out("poveste.out");

const int NMAX = 1010, LG2NMAX = 10, oo = 0x3f3f3f3f;

int T, N, M;
int last_sorted[NMAX], sorted[NMAX], preRMQ[LG2NMAX][NMAX], RMQ[LG2NMAX][NMAX], where[NMAX], Disjoint[NMAX], lt[NMAX], rt[NMAX], height[NMAX];
vector<int> front0, front1;
char B[NMAX][NMAX];

inline int pw2(int value) {
    return (1 << value);
}

inline int lg2(int value) {
    int res = -1;
    while (value) {
        ++res;
        value /= 2;
    }
    return res;
}

void ComputeRMQ(int RMQ[][NMAX], int num) {
    int i, j;
    for (i = 1; i <= lg2(num); ++i)
        for (j = 1; j + pw2(i) - 1 <= num; ++j)
            RMQ[i][j] = min(RMQ[i - 1][j], RMQ[i - 1][j + pw2(i - 1)]);
}

inline int LCP(int RMQ[][NMAX], int pos1, int pos2) {
    int lgdist = lg2(pos2 - pos1 + 1);
    return min(RMQ[lgdist][pos1], RMQ[lgdist][pos2 - pw2(lgdist) + 1]);
}

inline int Abs(int value) {
    if (value < 0) return (-value);
    return value;
}

struct LCP {
    int x, y, length;

    bool operator<(const LCP &rhs) const {
        if (length > rhs.length) return true;
        return false;
    }
} L[NMAX];

int GetRoot(int node) {
    int x, y, ret;
    for (ret = node; ret != Disjoint[ret]; ret = Disjoint[ret]);

    x = node;
    while (x != Disjoint[x]) {
        y = Disjoint[x];
        Disjoint[x] = ret;
        x = y;
    }

    return ret;
}

int Unite(int root1, int root2) {
    int root;
    if (height[root1] < height[root2]) {
        Disjoint[root1] = root2;
        lt[root2] = min(lt[root2], lt[root1]);
        rt[root2] = max(rt[root2], rt[root1]);
        root = root2;
    } else {
        Disjoint[root2] = root1;
        lt[root1] = min(lt[root1], lt[root2]);
        rt[root1] = max(rt[root1], rt[root2]);
        root = root1;
    }

    if (height[root1] == height[root2]) ++height[root1];
    return root;
}

int main() {
    int i, j, k, AMax, pos1, pos2, last_pos1, last_pos2;

    for (in >> T; T; --T) {
        in >> N >> M;
        in.getline(B[0], NMAX);
        AMax = N;

        for (i = 1; i <= N; ++i) in.getline(B[i] + 1, NMAX);

        for (i = 1; i <= M; ++i)
            last_sorted[i] = where[i] = i;

        for (i = 1; i <= N; ++i) {
            for (j = 1; j <= M; ++j) {
                int pos = last_sorted[j];
                if (B[i][pos] == '0') front0.push_back(pos);
                else front1.push_back(pos);
            }

            k = 0;
            for (j = 0; j < (int)front0.size(); ++j) sorted[++k] = front0[j];
            for (j = 0; j < (int)front1.size(); ++j) sorted[++k] = front1[j];
            front0.clear();
            front1.clear();

            for (j = 1; j < M; ++j) {
                pos1 = sorted[j];
                pos2 = sorted[j + 1];
                last_pos1 = min(where[pos1], where[pos2]);
                last_pos2 = max(where[pos1], where[pos2]) - 1;

                if (B[i][pos1] == B[i][pos2]) RMQ[0][j] = 1 + LCP(preRMQ, last_pos1, last_pos2);
                else RMQ[0][j] = 0;

                L[j].x = min(sorted[j], sorted[j + 1]);
                L[j].y = max(sorted[j], sorted[j + 1]);
                L[j].length = RMQ[0][j];
            }

            for (j = 1; j <= M; ++j) {
                Disjoint[j] = j;
                lt[j] = oo;
                rt[j] = -oo;
                height[j] = 0;
            }
            sort(L + 1, L + M);

            for (j = 1; j < M; ++j) {
                int root1 = GetRoot(L[j].x);
                int root2 = GetRoot(L[j].y);
                int root = Unite(root1, root2);
                lt[root] = min(lt[root], L[j].x);
                rt[root] = max(rt[root], L[j].y);
                AMax = max(AMax, (rt[root] - lt[root] + 1) * L[j].length);
            }

            for (j = 1; j <= M; ++j) where[sorted[j]] = j;

            ComputeRMQ(RMQ, M - 1);
            memcpy(preRMQ, RMQ, sizeof(preRMQ));
            memcpy(last_sorted, sorted, sizeof(last_sorted));
        }
        out << AMax << '\n';
    }

    in.close(), out.close();
    return 0;
}
