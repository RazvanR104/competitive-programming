#include <bits/stdc++.h>

using namespace std;

const int LMAX = 1e6 + 10, ALPHABET_SIZE = 26, WMAX = 1e4 + 10, NMAX = 110;

int N;
int answer[NMAX];
char str[LMAX], word[WMAX];

struct Node {
    vector<int> pos;
    int answer;
    Node *next[ALPHABET_SIZE], *fail;

    Node():
        answer(0),
        fail(0) {
        memset(next, 0, sizeof next);
    }
} *T;

void InsertWord(Node *node, char *str, int pos) {
    if (*str == 0) {
        node->pos.push_back(pos);
        return;
    }
    if (node->next[*str - 'a'] == 0)
        node->next[*str - 'a'] = new Node();
    InsertWord(node->next[*str - 'a'], str + 1, pos);
}

vector<Node *> Q;
int lt, rt;
void BFS() {
    T->fail = T;
    Q.push_back(T);

    while (lt <= rt) {
        Node *now = Q[lt++];
        for (int i = 0; i < ALPHABET_SIZE; ++i) {
            if (now->next[i] == 0)
                continue;
            Node *fail;
            for (fail = now->fail; fail->next[i] == 0 && fail != T; fail = fail->fail);
            if (fail->next[i] != now->next[i] && fail->next[i] != 0)
                fail = fail->next[i];
            now->next[i]->fail = fail;

            Q.push_back(now->next[i]);
            ++rt;
        }
    }

    T->fail = 0;
}

void ABFS() {
    while (rt) {
        Node *now = Q[rt--];
        now->fail->answer += now->answer;
        for (const int &it: now->pos)
            answer[it] = now->answer;
    }
}

int main() {
    ifstream cin("ahocorasick.in");
    ofstream cout("ahocorasick.out");

    int i, j;

    T = new Node();

    cin >> (str + 1) >> N;
    for (i = 1; i <= N; ++i) {
        cin >> (word + 1);
        InsertWord(T, word + 1, i);
    }

    BFS();
    Node *now = T;
    for (i = 1; str[i]; ++i) {
        for ( ; now->next[str[i] - 'a'] == 0 && now != T; now = now->fail);
        if (now->next[str[i] - 'a']) {
            now = now->next[str[i] - 'a'];
            ++now->answer;
        }
    }

    ABFS();
    for (i = 1; i <= N; ++i)
        cout << answer[i] << '\n';

    return 0;
}
