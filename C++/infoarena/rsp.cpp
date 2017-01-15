//http://www.infoarena.ro/job_detail/1556511

#include <bits/stdc++.h>

using namespace std;

const int LMAX = 100010, MAX_LEVEL = 2, inf = 0x3f3f3f3f;

int T, pos, current = 0;
int DP[LMAX][2][2];
char S[LMAX];

struct Node {
    int node;
    char value;
    Node *left, *right;

    Node(char value = 0, Node *left = 0, Node *right = 0) : value(value), left(left), right(right) {
        node = current++;
    }
} *ET;

const char op[] = "SP";

Node *Expr(int level) {
    Node *ret;
    if (level == MAX_LEVEL) {
        if (S[pos] == '(') {
                ++pos;
                ret = Expr(0);
                ++pos;
        } else {
            ret = new Node('B');
            ++pos;
        }
    } else {
        Node *tmp;
        for (ret = Expr(level + 1); S[pos] == op[level]; ret = tmp) {
            ++pos;
            tmp = new Node(op[level], ret, Expr(level + 1));
        }
    }
    return ret;
}

void DFS(Node *curr) {
    if (curr->left == 0 && curr->right == 0) {
        DP[curr->node][0][0] = inf;
        DP[curr->node][0][1] = DP[curr->node][1][0] = 1;
        DP[curr->node][1][1] = 2;
        return;
    }

    DFS(curr->left);
    DFS(curr->right);

    if (curr->value == 'S') {
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                DP[curr->node][i][j] = min(DP[curr->left->node][i][0] + DP[curr->right->node][0][j], DP[curr->left->node][i][1] + DP[curr->right->node][1][j] - 1);
                if (DP[curr->node][i][j] >= inf)
                    DP[curr->node][i][j] = inf;
            }
        }
    } else {
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                DP[curr->node][i][j] = DP[curr->left->node][i][j] + DP[curr->right->node][i][j] - i - j;
                if (DP[curr->node][i][j] >= inf)
                    DP[curr->node][i][j] = inf;
            }
        }
    }
}

int main() {
	ios_base::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
	assert(freopen("rsp.in", "r", stdin) != NULL);
    assert(freopen("rsp.out", "w", stdout) != NULL);
    assert(freopen("debug.err", "w", stderr) != NULL);
    #endif

    for (cin >> T; T; --T) {
        cin >> S;
        pos = 0;
        current = 0;
        ET = Expr(0);

        memset(DP, inf, sizeof(DP));
        DFS(ET);
        cout << min(DP[ET->node][0][0], min(DP[ET->node][0][1], min(DP[ET->node][1][0], DP[ET->node][1][1]))) << '\n';
    }

	return 0;
}
