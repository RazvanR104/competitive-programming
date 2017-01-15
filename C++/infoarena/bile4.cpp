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

const int BUFFER_SIZE = 1 << 21;

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

InputReader in("bile2.in");
ofstream out("bile2.out");

const int NMAX = 30010, LG2NMAX = 128;

int N, M, pos, stpos;

struct Treap {
    int key, value, priority, size;
    Treap *left, *right;

    Treap(int key, int value, int priority, int size, Treap *left, Treap *right) {
        this->key = key, this->value = value, this->priority = priority, this->size = size;
        this->left = left, this->right = right;
    }
} *nil, *A[4 * NMAX], *B[4 * NMAX], **STACK[NMAX];

inline void ComputeSize(Treap *node) {
    node->size = node->value + node->left->size + node->right->size;
}

inline void RotateLeft(Treap *&node) {
    Treap *aux = node->left;
    node->left = aux->right;
    aux->right = node;
    node = aux;

    ComputeSize(node->right);
    ComputeSize(node);
}

inline void RotateRight(Treap *&node) {
    Treap *aux = node->right;
    node->right = aux->left;
    aux->left = node;
    node = aux;

    ComputeSize(node->left);
    ComputeSize(node);
}

inline void Balance(Treap *&node) {
    if (node->left->priority > node->priority) RotateLeft(node);
    else if (node->right->priority > node->priority) RotateRight(node);
    else ComputeSize(node);
}

void Insert(Treap *&node, int key, int value) {
    int top = 0;
    STACK[top] = &node;
    while(*STACK[top] != nil && (*STACK[top])->key != key) {
        if (key < (*STACK[top])->key) STACK[top + 1] = &((*STACK[top])->left);
        else STACK[top + 1] = &((*STACK[top])->right);
        ++top;
    }

    if (*STACK[top] == nil) *STACK[top] = new Treap(key, value, rand() + 1, value, nil, nil);
    else {
        (*STACK[top])->value += value;
        ComputeSize(*STACK[top]);
    }

    while(--top >= 0) Balance(*STACK[top]);
}

int Query(Treap *node, int key) {
    int ret = 0;

    while(node != nil && node->key != key) {
        if (key < node->key) node = node->left;
        else {
            ret += node->value + node->left->size;
            node = node->right;
        }
    }

    if (node == nil) return ret;
    return (node->value + node->left->size + ret);
}

inline int Intersect(int left, int right, int qleft, int qright) {
    if (qleft >= left && qright <= right) return qright - qleft + 1;
    if (qleft <= left && qright >= right) return right - left + 1;
    if (qleft <= left && qright >= left && qright <= right) return qright - left + 1;
    if (qleft >= left && qleft <= right && qright >= right) return right - qleft + 1;

    return 0;
}

void UpdateSegmentTREE(int node, int left, int right, int qleft, int qright, int key) {
    Insert(A[node], key, Intersect(left, right, qleft, qright));

    if (qleft <= left && qright >= right) {
        Insert(B[node], key, 1);
        return;
    }

    if (left == right) return;

    int mid = (left + right) / 2;
    if (qleft <= mid) UpdateSegmentTREE(node * 2, left, mid, qleft, qright, key);
    if (qright > mid) UpdateSegmentTREE(node * 2 + 1, mid + 1, right, qleft, qright, key);
}

void QuerySegmentTREE(int node, int left, int right, int qleft, int qright, int key) {
    if (qleft <= left && qright >= right) {
        stpos += Query(A[node], key - 1);
        pos += Query(A[node], key);
        return;
    }

    stpos += Intersect(left, right, qleft, qright) * Query(B[node], key - 1);
    pos += Intersect(left, right, qleft, qright) * Query(B[node], key);

    if (left == right) return;

    int mid = (left + right) / 2;
    if (qleft <= mid) QuerySegmentTREE(node * 2, left, mid, qleft, qright, key);
    if (qright > mid) QuerySegmentTREE(node * 2 + 1, mid + 1, right, qleft, qright, key);
}

int main() {
    int i, operation, a, b, k, left, right, mid;
    srand(time(NULL));

    nil = new Treap(0, 0, 0, 0, NULL, NULL);
    for (i = 1; i < 4 * NMAX; ++i) A[i] = B[i] = nil;

    in >> N >> M;
    while(M--) {
        in >> operation >> a >> b >> k;
        ++a, ++b;
        if (operation == 1) UpdateSegmentTREE(1, 1, N, a, b, k);
        else {
            pos = 0;
            QuerySegmentTREE(1, 1, N, 1, N, NMAX);
            if (pos < k) {
                out << "-1\n";
                continue;
            }
            left = 1, right = NMAX;
            for (mid = (left + right) / 2; left <= right; mid = (left + right) / 2) {
                stpos = pos = 0;
                QuerySegmentTREE(1, 1, N, a, b, mid);

                if (stpos < k && pos >= k) {
                    out << mid << '\n';
                    break;
                }
                else if (stpos < k && pos < k) left = mid + 1;
                else right = mid - 1;
            }

            if (left > right) out << "-1\n";
        }
    }

    in.close(), out.close();
    return 0;
}
