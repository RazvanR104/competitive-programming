#include <bits/stdc++.h>

using namespace std;

struct Treap {
    int key, priority;
    Treap *left, *right;

    Treap() {
    }
    Treap(int key, int priority, Treap *left, Treap *right): key(key), priority(priority), left(left), right(right) {
    }
} *T, *nil;

void RotLeft(Treap *&node) {
    Treap *temp = node;
    node = node->left;
    temp->left = node->right;
    node->right = temp;
}

void RotRight(Treap *&node) {
    Treap *temp = node;
    node = node->right;
    temp->right = node->left;
    node->left = temp;
}

void Balance(Treap *&node) {
    if (node->left->priority >= node->right->priority && node->left->priority > node->priority)
        RotLeft(node);
    else if (node->left->priority < node->right->priority && node->right->priority > node->priority)
        RotRight(node);
}

void Insert(Treap *&node, int key) {
    if (node == nil) {
        node = new Treap(key, rand() + 1, nil, nil);
        return;
    }

    if (node->key == key)
        return;

    if (key < node->key)
        Insert(node->left, key);
    else if (key > node->key)
        Insert(node->right, key);

    Balance(node);
}

void Erase(Treap *&node, int key) {
    if (node == nil)
        return;

    if (key < node->key)
        Erase(node->left, key);
    else if (key > node->key)
        Erase(node->right, key);

    if (key == node->key) {
        if (node->left == nil && node->right == nil) {
            delete node;
            node = nil;
            return;
        }

        if (node->left->priority >= node->right->priority) {
            RotLeft(node);
            Erase(node->right, key);
        } else {
            RotRight(node);
            Erase(node->left, key);
        }
    }

    Balance(node);
}

int Check(Treap *node, int key) {
    if (node == nil)
        return 0;

    if (node->key == key)
        return 1;

    if (key < node->key)
        return Check(node->left, key);
    return Check(node->right, key);
}

int N;

int main() {
    assert(freopen("hashuri.in", "r", stdin));
    assert(freopen("hashuri.out", "w", stdout));

    srand(time(0));

    T = nil = new Treap(0, 0, 0, 0);
    nil->left = nil->right = nil;

    scanf("%d", &N);
    while (N--) {
        int op, key;
        scanf("%d %d", &op, &key);
        if (op == 1)
            Insert(T, key);
        else if (op == 2)
            Erase(T, key);
        else cout << Check(T, key) << '\n';
    }

    return 0;
}
