#include <bits/stdc++.h>

using namespace std;

const int BUFFER_SIZE = 1 << 22;
class Reader {
    public:
        Reader() {}
        Reader(const char* filename) {
            file = fopen(filename, "r");
            cursor = 0;
            fread(buffer, BUFFER_SIZE, 1, file);
        }
        inline Reader & operator >> (int &n) {
            n = 0;
            while(!isdigit(buffer[cursor])) {
                advance();
            }
            while(isdigit(buffer[cursor])) {
                n = n * 10 + buffer[cursor] - '0';
                advance();
            }
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

int N;

struct Node {
    int sum;
    Node *l, *r;

    Node(int sum = 0, Node *l = 0, Node *r = 0):
        sum(sum),
        l(l),
        r(r) {
    }
} *nil;

Node *Update(Node *node, int left, int right, int value, int add) {
    if (left == right)
        return new Node(node->sum + add, nil, nil);

    int mid = (left + right) >> 1;
    if (value <= mid)
        return new Node(node->sum + add, Update(node->l, left, mid, value, add), node->r);
    return new Node(node->sum + add, node->l, Update(node->r, mid + 1, right, value, add));
}

int Query(Node *Minus, Node *Plus, int left, int right, int pos) {
    if (left == right)
        return left;

    int mid = (left + right) >> 1;
    int many = Plus->l->sum - Minus->l->sum;
    if (pos <= many)
        return Query(Minus->l, Plus->l, left, mid, pos);
    return Query(Minus->r, Plus->r, mid + 1, right, pos - many);
}

int main() {
    Reader cin("kthvalue.in");
    assert(freopen("kthvalue.out", "w", stdout));

    int x, y, k, i, v;
    cin >> N;

    nil = new Node();
    nil->l = nil->r = nil;

    deque<Node *> D;
    D.push_back(nil);

    for (i = 1; i <= N; ++i) {
        int type;
        cin >> type;
        if (type == 1) {
            cin >> v;
            D.push_front(Update(D.front(), 1, N, v, -1));
        } else if (type == 2) {
            cin >> v;
            D.push_back(Update(D.back(), 1, N, v, 1));
        } else if (type == 3)
            D.pop_front();
        else if (type == 4)
            D.pop_back();
        else {
            cin >> x >> y >> k;
            cout << Query(D[x - 1], D[y], 1, N, k) << '\n';
        }
    }

    return 0;
}
