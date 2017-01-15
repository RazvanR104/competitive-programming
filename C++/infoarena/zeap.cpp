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

const int oo = 0x3f3f3f3f, LMAX = 100;

ifstream in("zeap.in");
ofstream out("zeap.out");

int size;
char line[LMAX];

inline int Abs(const int &value) {
    if (value < 0) return -value;
    return value;
}

struct Treap {
    int key, priority, _max, _min, min_diff;
    Treap *left, *right;

    Treap(int key, int priority, int _max, int _min, int min_diff, Treap *left, Treap *right) {
        this->key = key, this->priority = priority;
        this->_max = _max, this->_min = _min, this->min_diff = min_diff;
        this->left = left, this->right = right;
    }
} *T, *nil;

void Compute(Treap *node) {
    node->_min = min(node->key, node->left->_min);
    node->_max = max(node->key, node->right->_max);
    node->min_diff = min(min(node->left->min_diff, node->right->min_diff), min(Abs(node->key - node->left->_max), Abs(node->key - node->right->_min)));
}

void RotateLeft(Treap *&node) {
    Treap *aux = node->left;
    node->left = aux->right;
    aux->right = node;
    node = aux;

    Compute(node->right);
    Compute(node);
}

void RotateRight(Treap *&node) {
    Treap *aux = node->right;
    node->right = aux->left;
    aux->left = node;
    node = aux;

    Compute(node->left);
    Compute(node);
}

void Balance(Treap *&node) {
    if (node->left->priority > node->priority) RotateLeft(node);
    else if (node->right->priority > node->priority) RotateRight(node);
    else Compute(node);
}

void Insert(Treap *&node, int key) {
    if (node == nil) {
        node = new Treap(key, rand() + 1, key, key, oo, nil, nil);
        ++size;
        return;
    }

    if (key == node->key) return;
    if (key < node->key) Insert(node->left, key);
    else Insert(node->right, key);

    Balance(node);
}

bool Find(Treap *node, int key) {
    if (node == nil) return false;
    if (node->key == key) return true;

    if (key < node->key) return Find(node->left, key);
    return Find(node->right, key);
}

bool existed;
void Erase(Treap *&node, int key) {
    if (node == nil) return;

    if (key < node->key) {
        Erase(node->left, key);
        Compute(node);
    }
    else if (key > node->key) {
        Erase(node->right, key);
        Compute(node);
    }
    else {
        if (node->left == nil && node->right == nil) {
            delete node;
            node = nil;
            --size;
            existed = true;
            return;
        }

        if (node->left->priority > node->right->priority) {
            RotateLeft(node);
            Erase(node->right, key);
        }
        else {
            RotateRight(node);
            Erase(node->left, key);
        }

        Compute(node);
    }
}

int main() {
    int x, i;

    srand(time(NULL));
    T = nil = new Treap(0, 0, -oo, oo, oo, NULL, NULL);

    in.getline(line, LMAX);

    while(!in.eof()) {
        if (line[0] == 'I') {
            for (x = 0, i = 2; line[i]; ++i) x = x * 10 + line[i] - '0';
            Insert(T, x);
        }
        else if (line[0] == 'S') {
            for (x = 0, i = 2; line[i]; ++i) x = x * 10 + line[i] - '0';
            existed = false;
            Erase(T, x);
            if (!existed) out << "-1\n";
        }
        else if (line[0] == 'C') {
            for (x = 0, i = 2; line[i]; ++i) x = x * 10 + line[i] - '0';
            if (Find(T, x)) out << "1\n";
            else out << "0\n";
        }
        else if (line[1] == 'A') {
            if (size < 2) out << "-1\n";
            else out << Abs(T->_max - T->_min) << '\n';
        }
        else {
            if (size < 2) out << "-1\n";
            else out << T->min_diff << '\n';
        }

        in.getline(line, LMAX);
    }

    in.close(), out.close();
    return 0;
}
