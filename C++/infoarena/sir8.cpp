#include <bits/stdc++.h>

using namespace std;

const int LMAX = 800010, BASE = 131, MOD1 = 38053, MOD2 = 40087, SMAX = 100010;

int N, M;
int pw1[SMAX], pw2[SMAX], hash1[LMAX], hash2[LMAX], len[LMAX];
char str[LMAX];

inline int Random() {
    return (rand() << 16) ^ rand();
}

struct Node {
    char key;
    int pr, sz, hash1, hash2;
    Node *l, *r;

    Node(char key, int pr, int sz, Node *l, Node *r):
        key(key),
        pr(pr),
        sz(sz),
        hash1(key),
        hash2(key),
        l(l),
        r(r) {
    }
} *T, *nil;

void Update(Node *node) {
    if (node == nil)
        return;
    node->sz = node->l->sz + node->r->sz + 1;
    node->hash1 = (((node->l->hash1 * BASE + node->key) % MOD1) * pw1[node->r->sz] + node->r->hash1) % MOD1;
    node->hash2 = (((node->l->hash2 * BASE + node->key) % MOD2) * pw2[node->r->sz] + node->r->hash2) % MOD2;
}

Node *Unite(Node *l, Node *r) {
    if (l == nil)
        return r;
    if (r == nil)
        return l;

    if (l->pr >= r->pr) {
        l->r = Unite(l->r, r);
        Update(l);
        return l;
    } else {
        r->l = Unite(l, r->l);
        Update(r);
        return r;
    }
}

pair<Node *, Node *> Split(Node *node, int pos) {
    if (node == nil)
        return {nil, nil};

    if (pos <= node->l->sz) {
        auto splitted = Split(node->l, pos);
        node->l = splitted.second;
        splitted.second = node;
        Update(node);
        return splitted;
    } else {
        auto splitted = Split(node->r, pos - 1 - node->l->sz);
        node->r = splitted.first;
        splitted.first = node;
        Update(node);
        return splitted;
    }
}

Node *Insert(Node *node, char key, int pos, int pr) {
    if (node == nil)
        return new Node(key, pr, 1, nil, nil);

    if (pr >= node->pr) {
        Node *temp = new Node(key, pr, 1, nil, nil);
        tie(temp->l, temp->r) = Split(node, pos - 1);
        Update(temp);
        return temp;
    } else if (pos <= node->l->sz + 1) {
        node->l = Insert(node->l, key, pos, pr);
        Update(node);
        return node;
    } else {
        node->r = Insert(node->r, key, pos - 1 - node->l->sz, pr);
        Update(node);
        return node;
    }
}

int main() {
    ifstream fin("sir8.in");
    ofstream fout("sir8.out");

    int i, j;

    srand(time(0));

    T = nil = new Node(-1, -1, 0, 0, 0);
    nil->l = nil->r = nil;
    nil->hash1 = nil->hash2 = 0;

    pw1[0] = pw2[0] = 1;
    for (i = 1; i < SMAX; ++i) {
        pw1[i] = pw1[i - 1] * BASE % MOD1;
        pw2[i] = pw2[i - 1] * BASE % MOD2;
    }

    fin >> (str + 1);
    for (i = 1; str[i]; ++i) {
        //Node *temp = new Node(str[i], Random(), 1, nil, nil);
        //T = Unite(T, temp);
        T = Insert(T, str[i], i, Random());
    }

    fin >> N;
    for (i = 1; i <= N; ++i) {
        fin >> (str + 1);
        for (j = 1; str[j]; ++j) {
            hash1[i] = (hash1[i] * BASE + str[j]) % MOD1;
            hash2[i] = (hash2[i] * BASE + str[j]) % MOD2;
        }
        len[i] = j - 1;
    }

    int last_query = 0, poz, a, b, op, ind;
    char c;
    fin >> M;
    for (i = 1; i <= M; ++i) {
        fin >> op;
        if (op == 0) {
            fin >> poz >> c >> a >> b;
            (last_query == 0) ? (poz ^= a) : (poz ^= b);

            //Node *temp = new Node(c, Random(), 1, nil, nil);
            //auto splitted = Split(T, poz - 1);
            //T = Unite(Unite(splitted.first, temp), splitted.second);
            T = Insert(T, c, poz, Random());
        } else {
            fin >> poz >> ind >> a >> b;
            (last_query == 0) ? (poz ^= a) : (poz ^= b);

            int left = poz - len[ind] + 1;
            if (left < 1) {
                fout << "0\n";
                last_query = 0;
                continue;
            }

            auto splitted1 = Split(T, left - 1);
            auto splitted2 = Split(splitted1.second, len[ind]);

            if (splitted2.first->hash1 == hash1[ind] && splitted2.first->hash2 == hash2[ind]) {
                fout << "1\n";
                last_query = 1;
            } else {
                fout << "0\n";
                last_query = 0;
            }

            T = Unite(Unite(splitted1.first, splitted2.first), splitted2.second);
        }
    }

    return 0;
}
