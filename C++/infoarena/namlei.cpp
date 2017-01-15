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

ifstream in("namlei.in");
ofstream out("namlei.out");

const int NMAX = 30010, KMAX = 8, MOD = 997;

int N, K, X, Y, a, b, c, d;
int path[NMAX][KMAX][KMAX], tree[4 * NMAX][KMAX][KMAX], RES[KMAX][KMAX], AUX[KMAX][KMAX];

void matrix_multiplication(int A[][KMAX], int B[][KMAX], int RES[][KMAX]) {
    for(int i = 0; i < KMAX; ++i)
        for(int j = 0; j < KMAX; ++j)
            for(int k = 0; k < KMAX; ++k)
                RES[i][j] = (RES[i][j] + A[i][k] * B[k][j]) % MOD;
}

void build_tree(const int node, const int left, const int right) {
    if(left == right) {
        memcpy(tree[node], path[left], sizeof(tree[node]));
        return;
    }

    int mid = (left + right) / 2;
    build_tree(node * 2, left, mid);
    build_tree(node * 2 + 1, mid + 1, right);

    matrix_multiplication(tree[node * 2], tree[node * 2 + 1], tree[node]);
}

void update(const int node, const int left, const int right) {
    //a - i; b - cnt; c - j; d - k
    if(left == right) {
        for(int i = 0; i < K; ++i)
            for(int j = 0; j < K; ++j)
                tree[node][i][j] = 1;
        int _c, _d;
        for(int w = 0; w < b; ++w) {
            ++tree[node][c][d];
            _c = (c * X + d * w * Y + 1) % K;
            _d = (c * w * X + d * Y + 1) % K;
            c = _c, d = _d;
        }
        return;
    }

    int mid = (left + right) / 2;
    if(a <= mid) update(node * 2, left, mid);
    else update(node * 2 + 1, mid + 1, right);

    memset(tree[node], 0, sizeof(tree[node]));
    matrix_multiplication(tree[node * 2], tree[node * 2 + 1], tree[node]);
}

void query(const int node, const int left, const int right) {
    //a - i, b - x, c - j, d - y
    if (a <= left && c >= right) {
        matrix_multiplication(RES, tree[node], AUX);
        memcpy(RES, AUX, sizeof(RES));
        return;
    }

    int mid = (left + right) / 2;
    if(a <= mid) query(node * 2, left, mid);
    if(c > mid) query(node * 2 + 1, mid + 1, right);
}

int main() {
    int i, j, k, cnt, _j, _k, w;
    char Q;

    in >> N >> K >> X >> Y;
    for(i = 0; i < N; ++i) {
        in >> cnt >> j >> k;
        for(w = 0; w < cnt; ++w) {
            ++path[i][j][k];
            _j = (j * X + k * w * Y) % K;
            _k = (j * w * X + k * Y) % K;
            j = _j, k = _k;
        }
    }

    build_tree(1, 0, N - 1);

    in >> Q;
    while(!in.eof()) {
        in >> a >> b >> c >> d;
        switch(Q) {
            case 'U': update(1, 0, N - 1); break;
            case 'Q':
                memset(RES, 0, sizeof(RES));
                for(i = 0; i < K; ++i) RES[i][i] = 1;
                --c;
                query(1, 0, N - 1);
                out << RES[b][d] << '\n';
        }
        in >> Q;
    }

    in.close(), out.close();
    return 0;
}
