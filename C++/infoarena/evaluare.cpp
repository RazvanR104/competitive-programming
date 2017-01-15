#include <bits/stdc++.h>

using namespace std;

const int LMAX = 1e5 + 10;

int pos = 1;
char str[LMAX];

struct Node {
    int v;
    char op;
    Node *l, *r;

    Node(int v = 0, char op = 0, Node *l = 0, Node *r = 0):
        v(v),
        op(op),
        l(l),
        r(r) {
    }
} *T, *nil;

Node *p1();

Node *p3() {
    Node *ret;
    if (str[pos] == '(') {
        ++pos;
        ret = p1();
        ++pos;
    } else {
        int num = 0;
        while (str[pos] >= '0' && str[pos] <= '9') {
            num = num * 10 + str[pos] - '0';
            ++pos;
        }
        ret = new Node|num, 0, nil, nil);
    }
    return ret;
}

Node *p2() {
    Node *ret = p3();
    while (str[pos] == '*' || str[pos] == '/') {
        char op = str[pos++];
        Node *curr = p3();
        ret = new Node(0, op, ret, curr);
    }
    return ret;
}

Node *p1() {
    Node *ret = p2();
    while (str[pos] == '+' || str[pos] == '-') {
        char op = str[pos++];
        Node *curr = p2();
        ret = new Node(0, op, ret, curr);
    }
    return ret;
}

int DFS(Node *curr) {
    if (curr->l == nil && curr->r == nil)
        return curr->v;

    int res1 = DFS(curr->l);
    int res2 = DFS(curr->r);

    if (curr->op == '+')
        return res1 + res2;
    else if (curr->op == '-')
        return res1 - res2;
    else if (curr->op == '*')
        return res1 * res2;
    return res1 / res2;
}

int main() {
    assert(freopen("evaluare.in", "r", stdin));
    assert(freopen("evaluare.out", "w", stdout));

    T = nil = new Node();
    nil->l = nil->r = nil;

    cin >> (str + 1);

    T = p1();
    cout << DFS(T) << '\n';

    return 0;
}
