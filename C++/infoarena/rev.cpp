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

const int BUFFER_SIZE = 1 << 20, oo = 0x7fffffff;

class InputReader {
    public:
        InputReader() {}
        InputReader(const char* filename) {
            file = fopen(filename, "r");
            cursor = 0;
            fread(buffer, BUFFER_SIZE, 1, file);
        }
        inline InputReader & operator >> (int &n) {
            n = 0;
            sign = 1;
            while(!isdigit(buffer[cursor])) {
                if (buffer[cursor] == '-') sign = -1;
                advance();
            }
            while(isdigit(buffer[cursor])) {
                n = n * 10 + buffer[cursor] - '0';
                advance();
            }
            n *= sign;
            return *this;
        }
        inline void close() {
            fclose(file);
        }
    private:
        int cursor, sign;
        char buffer[BUFFER_SIZE];
        FILE* file;
        inline void advance() {
            ++cursor;
            if(cursor == BUFFER_SIZE) {
                cursor = 0;
                fread(buffer, BUFFER_SIZE, 1, file);
            }
        }
};

InputReader in("rev.in");
ofstream out("rev.out");

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

void Reverse(Treap *node) {
    if (node->rev == false) return;

    node->rev = false;
    swap(node->left, node->right);

    node->left->rev ^= 1;
    node->right->rev ^= 1;
}

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

void Balance(Treap *&node) {
    if (node->left->priority > node->priority) {
        Reverse(node);
        Reverse(node->left);
        RotateLeft(node);
    }
    else if (node->right->priority > node->priority) {
        Reverse(node);
        Reverse(node->right);
        RotateRight(node);
    }
}

void Insert(Treap *&node, int pos, int value, int priority) {
    if (node == nil) {
        node = new Treap(value, priority, 1, nil, nil);
        return;
    }

    Reverse(node);

    if (pos <= node->left->size + 1) Insert(node->left, pos, value, priority);
    else Insert(node->right, pos - node->left->size - 1, value, priority);

    Balance(node);
}

void Erase(Treap *&node) {
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
    }
    else {
        Reverse(node->right);
        RotateRight(node);
        Erase(node->left);
    }

    ComputeSize(node);
}

void Split(Treap *T, Treap *&left, Treap *&right, int pos) {
    Insert(T, pos, 0, oo);
    left = T->left;
    right = T->right;
    delete T;
}

void Join(Treap *&T, Treap *left, Treap *right) {
    T = new Treap(0, 0, left->size + right->size + 1, left, right);
    Erase(T);
}

int Access(Treap *node, int pos) {
    Reverse(node);

    if (pos == node->left->size + 1) return node->value;
    if (pos < node->left->size + 1) return Access(node->left, pos);
    return Access(node->right, pos - node->left->size - 1);
}

int N, M;

int main() {
    srand(time(NULL));
    T = nil = new Treap(0, 0, 0, NULL, NULL);

    in >> N >> M;
    for (int i = 1; i <= N; ++i) Insert(T, i, i, rand() + 1);

    int i, j, k;
    Treap *left, *center, *right, *aux;
    while(M--) {
        in >> i >> j >> k;

        Split(T, left, aux, i);
        Split(aux, center, right, j - i + 2);

        center->rev ^= 1;

        Join(aux, left, center);
        Join(T, aux, right);

        out << Access(T, k) << '\n';
    }

    in.close(), out.close();
    return 0;
}
