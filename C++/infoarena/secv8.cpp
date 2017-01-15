#include <fstream>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

ifstream in("secv8.in");
ofstream out("secv8.out");

const int oo = 0x7fffffff;

struct Treap {
    int value, priority, size;
    bool rev;
    Treap *left, *right;

    Treap(int value, int priority, int size, Treap *left, Treap *right) {
        this->value = value, this->priority = priority, this->size = size;
        this->left = left, this->right = right;
        this->rev = false;
    }
} *T, *nil;

void ComputeSize(Treap *node) {
    node->size = node->left->size + node->right->size + 1;
}

void RotateLeft(Treap *&node) {
    Treap *aux = node->left;
    node->left = aux->right;
    aux->right = node;
    node = aux;

    ComputeSize(node->right);
    ComputeSize(node);
}

void RotateRight(Treap *&node) {
    Treap *aux = node->right;
    node->right = aux->left;
    aux->left = node;
    node = aux;

    ComputeSize(node->left);
    ComputeSize(node);
}

void Reverse(Treap *node) {
    if (node->rev == false) return;
    node->rev = false;

    swap(node->left, node->right);
    node->left->rev ^= 1;
    node->right->rev ^= 1;
}

void Balance(Treap *&node) {
    if (node->left->priority > node->priority) { Reverse(node); Reverse(node->left); RotateLeft(node); }
    else if (node->right->priority > node->priority) { Reverse(node); Reverse(node->right); RotateRight(node); }
}

void Insert(Treap *&node, int pos, int value, int priority) {
    if (node == nil) {
        node = new Treap(value, priority, 1, nil, nil);
        return;
    }

    Reverse(node);

    if (pos <= node->left->size + 1) Insert(node->left, pos, value, priority);
    else Insert(node->right, pos - node->left->size - 1, value, priority);

    ComputeSize(node);
    Balance(node);
}

void Erase(Treap *&node) {
    if (node == nil) return;

    if (node->left == nil && node->right == nil) {
        delete node;
        node = nil;
        return;
    }

    Reverse(node);

    if (node->left->priority > node->right->priority) {
        Reverse(node->left);
        RotateLeft(node);
        Erase(node->right);
        ComputeSize(node);
    }
    else {
        Reverse(node->right);
        RotateRight(node);
        Erase(node->left);
        ComputeSize(node);
    }
}

int Access(Treap *node, int pos) {
    Reverse(node);
    if (pos == node->left->size + 1) return node->value;
    else if (pos <= node->left->size) return Access(node->left, pos);
    return Access(node->right, pos - node->left->size - 1);
}

void Split(Treap *&T, Treap *&T1, Treap *&T2, int pos) {
    Insert(T, pos, 0, oo);
    T1 = T->left;
    T2 = T->right;
    delete T;
}

void Join(Treap *&T, Treap *&T1, Treap *&T2) {
    T = new Treap(0, 0, T1->size + T2->size + 1, T1, T2);
    Erase(T);
}

void Print(Treap *node) {
    if (node == nil) return;
    Reverse(node);
    Print(node->left);
    out << node->value << ' ';
    Print(node->right);
}

int N, REV;

int main() {
    srand(time(NULL));
    T = nil = new Treap(0, 0, 0, NULL, NULL);

    in >> N >> REV;
    char op;
    int x, y;

    for (int i = 1; i <= N; ++i) {
        in >> op;
        if (op == 'I') {
            in >> x >> y;
            Insert(T, x, y, rand() + 1);
        }
        else if (op == 'A') {
            in >> x;
            out << Access(T, x) << '\n';
        }
        else if (op == 'R') {
            in >> x >> y;

            Treap *left, *center, *right, *aux;
            Split(T, left, aux, x);
            Split(aux, center, right, y - x + 2);

            center->rev ^= 1;

            Join(aux, left, center);
            Join(T, aux, right);
        }
        else {
            in >> x >> y;

            Treap *left, *center, *right, *aux;
            Split(T, left, aux, x);
            Split(aux, center, right, y - x + 2);

            Join(T, left, right);
        }
    }

    Print(T);
    out << '\n';
    in.close(), out.close();
}
