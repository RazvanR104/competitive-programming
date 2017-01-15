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

ifstream in("amedie.in");
ofstream out("amedie.out");

const int NMAX = 810;

int N, M, Q;
int V[NMAX][NMAX];

struct Treap {
    Treap *left, *right;
    int value, sz, priority;

    Treap(int value, int sz, int priority, Treap *left, Treap *right) {
        this->value = value;
        this->sz = sz;
        this->priority = priority;
        this->left = left;
        this->right = right;
    }
} *T, *nil;

void Compute(Treap *node) {
    node->sz = node->left->sz + node->right->sz + 1;
}

inline void LeftRotate(Treap *&node) {
    Treap *aux;
    aux = node->left;
    node->left = aux->right;
    aux->right = node;
    node = aux;

    Compute(node->right);
    Compute(node);
}

inline void RightRotate(Treap *&node) {
    Treap *aux;
    aux = node->right;
    node->right = aux->left;
    aux->left = node;
    node = aux;

    Compute(node->left);
    Compute(node);
}

void Balance(Treap *&node) {
    if (node->left->priority > node->priority) LeftRotate(node);
    else if (node->right->priority > node->priority) RightRotate(node);
}

void Insert(Treap *&node, int value) {
    if (node == nil) {
        node = new Treap(value, 1, rand() + 1, nil, nil);
        return;
    }

    if (value <= node->value) Insert(node->left, value);
    if (value > node->value) Insert(node->right, value);

    Compute(node);
    Balance(node);
}

void Erase(Treap *&node, int value) {
    if (node == nil) return;

    if (value < node->value) Erase(node->left, value);
    else if (value > node->value) Erase(node->right, value);
    else {
        if (node->left == nil && node->right == nil) {
            delete node;
            node = nil;
            return;
        }

        if (node->left->priority > node->right->priority) {
            LeftRotate(node);
            Erase(node->right, value);
        }
        else {
            RightRotate(node);
            Erase(node->left, value);
        }
    }
    Compute(node);
}

int GetValuebyPosition(Treap *node, int pos) {
    if (node->left->sz + 1 == pos)
        return node->value;

    if (pos <= node->left->sz) return GetValuebyPosition(node->left, pos);
    return GetValuebyPosition(node->right, pos - node->left->sz - 1);
}

int main() {
    srand(time(NULL));

    int i, j, num = 0;
    T = nil = new Treap(0, 0, 0, NULL, NULL);

    in >> N >> M >> Q;
    for (i = 1; i <= N; ++i)
        for (j = 1; j <= M; ++j) {
            in >> V[i][j];
            Insert(T, V[i][j]);
            ++num;
        }

    int where;
    char opnow;
    while (Q--) {
        in >> opnow;
        if (opnow == 'L') {
            in >> where;
            for (i = 1; i <= M; ++i)
                if (V[where][i] != -1) {
                    Erase(T, V[where][i]);
                    V[where][i] = -1;
                    --num;
                }
        } else if (opnow == 'C') {
            in >> where;
            for (i = 1; i <= N; ++i)
                if (V[i][where] != -1) {
                    Erase(T, V[i][where]);
                    V[i][where] = -1;
                    --num;
                }
        } else {
            if (num % 2)
                out << GetValuebyPosition(T, num / 2 + 1) << '\n';
            else out << min(GetValuebyPosition(T, num / 2), GetValuebyPosition(T, num / 2 + 1)) << '\n';
        }
    }

    in.close(), out.close();
    return 0;
}
