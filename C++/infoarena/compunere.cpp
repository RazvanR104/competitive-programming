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

ifstream in("compunere.in");
ofstream out("compunere.out");

const int NMAX = 100010, MOD = 666013, oo = 0x3f3f3f3f;

int N, M, Max = -1;
int A[NMAX], B[NMAX], from[NMAX], res[2 * NMAX], where[NMAX], DP[NMAX], first[NMAX], cnt[NMAX], MaxTree[4 * NMAX];
pair<int, int> STree[4 * NMAX];
vector<pair<int, int> > H[MOD];
unordered_set<int> restricted;

void Insert(int value, int pos) {
    int key = value % MOD;
    if (key < 0) key += MOD;

    H[key].push_back(make_pair(value, pos));
}

int GetPosition(int value) {
    int key = value % MOD;
    if (key < 0) key += MOD;

    for (int i = 0; i < (int)H[key].size(); ++i)
        if (H[key][i].first == value) return H[key][i].second;
    return -1;
}

void Update(int node, int left, int right, int pos, int value) {
    if (left == right) {
        STree[node].first = value;
        STree[node].second = pos;
        return;
    }

    int mid = (left + right) / 2;
    if (pos <= mid) Update(node * 2, left, mid, pos, value);
    else Update(node * 2 + 1, mid + 1, right, pos, value);

    if (STree[node * 2].first > STree[node * 2 + 1].first)
        STree[node] = STree[node * 2];
    else STree[node] = STree[node * 2 + 1];
}

pair<int, int> Query(int node, int left, int right, int qleft, int qright) {
    if (left >= qleft && right <= qright)
        return STree[node];

    if (left == right) return make_pair(-oo, 0);

    pair<int, int> ret(0, 0), res;

    int mid = (left + right) / 2;
    if (qleft <= mid) ret = Query(node * 2, left, mid, qleft, qright);
    if (qright > mid) {
        res = Query(node * 2 + 1, mid + 1, right, qleft, qright);
        if (res.first > ret.first)
            ret = res;
    }

    return ret;
}

void build_tree(int node, int left, int right) {
    if (left == right) {
        MaxTree[node] = DP[left];
        return;
    }

    int mid = (left + right) / 2;
    build_tree(node * 2, left, mid);
    build_tree(node * 2 + 1, mid + 1, right);

    MaxTree[node] = max(MaxTree[node * 2], MaxTree[node * 2 + 1]);
}

void Clear(int node, int left, int right, int pos) {
    if (left == right) {
        MaxTree[node] = 0;
        return;
    }

    int mid = (left + right) / 2;
    if (pos <= mid) update(node * 2, left, mid, pos);
    else update(node * 2 + 1, mid + 1, right, pos);

    MaxTree[node] = max(MaxTree[node * 2], MaxTree[node * 2 + 1]);
}

inline int LCS(int it_A, int it_B) {

}

int main() {
    int i, Pos;
    pair<int, int> ret;

    in >> N >> M;
    for (i = 1; i <= N; ++i) in >> A[i];
    for (i = 1; i <= M; ++i) in >> B[i];

    reverse(A + 1, A + N + 1);
    reverse(B + 1, B + M + 1);

    for (i = 1; i <= N; ++i) Insert(A[i], i);
    for (i = 1; i <= M; ++i) {
        Pos = GetPosition(B[i]);
        if (Pos == -1) continue;
        where[N - Pos + 1] = M - i + 1;
        ret = Query(1, 1, N, 1, Pos);
        DP[M - i + 1] = ret.first + 1;
        ++cnt[ret.first + 1];
        if (first[ret.first + 1] == 0) first[ret.first + 1] = M - i + 1;
        from[Pos] = ret.second;
        if (Max < ret.first + 1)
            Max = ret.first + 1;
        Update(1, 1, N, Pos, ret.first + 1);
    }

    out << N + M - Max << '\n';

    reverse(A + 1, A + N + 1);
    reverse(B + 1, B + M + 1);

    build_tree(1, 1, M);
    int it_A = 1, it_B = 1, limit = N + M - Max, pos = 0, incA, incB;

    while (pos < limit) {
        if (A[it_A] == B[it_B]) {
            res[pos++] = A[it_A];
            ++it_A, ++it_B;
        } else if () {
        }
    }

    for (i = 0; i < pos; ++i)
        out << res[i] << ' ';
    out << '\n';

    in.close(), out.close();
    return 0;
}
