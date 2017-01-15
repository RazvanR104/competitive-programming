#include <bits/stdc++.h>

using namespace std;

const int NMAX = 250010, LMAX = 500010, MOD1 = 666013, MOD2 = 666019, MULT = 31;

int N, M, pos;
int pw1[LMAX], pw2[LMAX];
int BIT[LMAX];
char str[LMAX];

void UpdateBIT(int where, int value) {
    for ( ; where <= pos; where += where & -where)
        BIT[where] += value;
}

int GetPos(int target) {
    int ret = 0;
    for (int bit = (1 << 20); bit; bit >>= 1) {
        if (ret + bit <= pos && BIT[ret + bit] <= target) {
            ret += bit;
            target -= BIT[ret];
        }
    }
    return ret;
}

struct Query {
    int op, p, q1, q2, lg, pos;
    char x;
} Q[NMAX];

inline int Random() {
    return (rand() << 16) ^ rand();
}

struct Treap {
    char key;
    int pr, sz;
    Treap *left, *right;

    Treap(char key, int pr, int sz, Treap *left, Treap *right):
        key(key),
        pr(pr),
        sz(sz),
        left(left),
        right(right) {
    }
} *T, *nil;

void Update(Treap *node) {
    if (node == nil)
        return;
    node->sz = node->left->sz + node->right->sz + 1;
}

pair<Treap *, Treap *> Split(Treap *node, int pos) {
    if (node == nil)
        return {nil, nil};

    if (pos <= node->left->sz) {
        auto split = Split(node->left, pos);
        node->left = split.second;
        split.second = node;
        Update(node);
        return split;
    } else {
        auto split = Split(node->right, pos - 1 - node->left->sz);
        node->right = split.first;
        split.first = node;
        Update(node);
        return split;
    }
}

Treap *Unite(Treap *left, Treap *right) {
    if (left == nil)
        return right;
    if (right == nil)
        return left;

    if (left->pr >= right->pr) {
        left->right = Unite(left->right, right);
        Update(left);
        return left;
    } else {
        right->left = Unite(left, right->left);
        Update(right);
        return right;
    }
}

void GetFinalStr(Treap *node) {
    if (node == nil)
        return;
    GetFinalStr(node->left);
    str[++pos] = node->key;
    GetFinalStr(node->right);
}

void Fix(int &value, int MOD) {
    if (value >= MOD)
        value -= MOD;
    else if (value < 0)
        value += MOD;
}

int hash1[4 * LMAX], hash2[4 * LMAX], sum[4 * LMAX];
void BuildTree(int node, int left, int right) {
    if (left == right) {
        hash1[node] = hash2[node] = str[left] - 'a' + 1;
        sum[node] = 1;
        return;
    }

    int mid = (left + right) >> 1;
    BuildTree(node * 2, left, mid);
    BuildTree(node * 2 + 1, mid + 1, right);

    hash1[node] = (1ll * hash1[node * 2] * pw1[sum[node * 2 + 1]] + hash1[node * 2 + 1]) % MOD1;
    hash2[node] = (1ll * hash2[node * 2] * pw2[sum[node * 2 + 1]] + hash2[node * 2 + 1]) % MOD2;

    sum[node] = sum[node * 2] + sum[node * 2 + 1];
}

pair<int, int> Query(int node, int left, int right, int qleft, int qright, int &summ) {
    if (left >= qleft && right <= qright) {
        summ = sum[node];
        return {hash1[node], hash2[node]};
    }

    int mid = (left + right) >> 1;

    pair<int, int> hl(-1, -1), hr(-1, -1);
    int sleft = 0, sright = 0;
    if (qleft <= mid)
        hl = Query(node * 2, left, mid, qleft, qright, sleft);
    if (qright > mid)
        hr = Query(node * 2 + 1, mid + 1, right, qleft, qright, sright);
    summ = sleft + sright;

    if (sleft == 0 && sright == 0)
        return {-1, -1};
    else if (sleft == 0)
        return hr;
    else if (sright == 0)
        return hl;

    int h1 = 0, h2 = 0;
    h1 = (1ll * hl.first * pw1[sright] + hr.first) % MOD1;
    h2 = (1ll * hl.second * pw2[sright] + hr.second) % MOD2;
    return {h1, h2};
}

void Update(int node, int left, int right, int pos) {
    if (left == right) {
        hash1[node] = hash2[node] = -1;
        sum[node] = 0;
        return;
    }

    if (left >= right)
        return;

    int mid = (left + right) >> 1;
    if (pos <= mid)
        Update(node * 2, left, mid, pos);
    else
        Update(node * 2 + 1, mid + 1, right, pos);

    if (sum[node * 2] && sum[node * 2 + 1]) {
        hash1[node] = (1ll * hash1[node * 2] * pw1[sum[node * 2 + 1]] + hash1[node * 2 + 1]) % MOD1;
        hash2[node] = (1ll * hash2[node * 2] * pw2[sum[node * 2 + 1]] + hash2[node * 2 + 1]) % MOD2;
    } else if (sum[node * 2] == 0 && sum[node * 2 + 1] == 0)
        hash1[node] = hash2[node] = -1;
    else if (sum[node * 2 + 1] == 0) {
        hash1[node] = hash1[node * 2];
        hash2[node] = hash2[node * 2];
    } else {
        hash1[node] = hash1[node * 2 + 1];
        hash2[node] = hash2[node * 2 + 1];
    }

    sum[node] = sum[node * 2] + sum[node * 2 + 1];
}

int answer[NMAX];

int main() {
    freopen("diez.in", "r", stdin);
    freopen("diez.out", "w", stdout);

    srand(time(0));

    int i;

    scanf("%d %d\n", &N, &M);
    gets(str + 1);

    T = nil = new Treap(-1, -1, 0, 0, 0);
    nil->left = nil->right = nil;

    for (i = 1; i <= N; ++i) {
        Treap *temp = new Treap(str[i], Random(), 1, nil, nil);
        T = Unite(T, temp);
    }

    int now = 0;
    for (i = 1; i <= M; ++i) {
        scanf("%d", &Q[i].op);
        if (Q[i].op == 1) {
            scanf("%d %c", &Q[i].p, &Q[i].x);
            ++Q[i].p;
            auto split = Split(T, Q[i].p - 1);
            Treap *temp = new Treap(Q[i].x, Random(), 1, nil, nil);
            T = Unite(split.first, temp);
            T = Unite(T, split.second);
        } else {
            scanf("%d %d %d", &Q[i].q1, &Q[i].q2, &Q[i].lg);
            ++Q[i].q1;
            ++Q[i].q2;
            Q[i].pos = ++now;
        }
    }

    GetFinalStr(T);

    pw1[0] = pw2[0] = 1;
    for (i = 1; i <= pos; ++i) {
        pw1[i] = pw1[i - 1] * MULT % MOD1;
        pw2[i] = pw2[i - 1] * MULT % MOD2;
    }

    BuildTree(1, 1, pos);

    for (i = 1; i <= pos; ++i)
        UpdateBIT(i, 1);

    for (i = M; i >= 1; --i) {
        if (Q[i].op == 1) {
            int where = GetPos(Q[i].p - 1) + 1;
            UpdateBIT(where, -1);
            Update(1, 1, pos, where);
        } else {
            int left1 = Q[i].q1, right1 = Q[i].q1 + Q[i].lg - 1, left2 = Q[i].q2, right2 = Q[i].q2 + Q[i].lg - 1;
            pair<int, int> hash1, hash2;

            left1 = GetPos(left1 - 1) + 1;
            right1 = GetPos(right1 - 1) + 1;
            left2 = GetPos(left2 - 1) + 1;
            right2 = GetPos(right2 - 1) + 1;

            int wtf = 0;
            hash1 = Query(1, 1, pos, left1, right1, wtf);
            hash2 = Query(1, 1, pos, left2, right2, wtf);

            answer[Q[i].pos] = (hash1 == hash2);
        }
    }

    for (i = 1; i <= now; ++i)
        cout << answer[i] << '\n';

    return 0;
}
