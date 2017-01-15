#include <bits/stdc++.h>

using namespace std;

const int PMAX = 35, KMAX = 20, MMAX = 30010, ALPHABET_SIZE = 26;

int N, K, M, P, Q;
char rd[KMAX][PMAX], rd2[MMAX][PMAX], proc[KMAX * PMAX];
int who[KMAX];

struct Trie {
    int value;
    Trie *next[ALPHABET_SIZE];

    Trie(): value(0) {
        memset(next, 0, sizeof(next));
    }
};

void Insert(Trie *node, char *str, int depth) {
    if (*str == 0)
        return;

    if (node->next[*str - 'a'] == 0)
        node->next[*str - 'a'] = new Trie();

    if (depth % K == 0)
        ++node->next[*str - 'a']->value;

    Insert(node->next[*str - 'a'], str + 1, depth + 1);
}

int GetValue(Trie *node, char *str) {
    if (*str == 0)
        return node->value;

    if (node->next[*str - 'a'] == 0)
        return 0;
    return GetValue(node->next[*str - 'a'], str + 1);
}

int main() {
	ios_base::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
	assert(freopen("sabin.in", "r", stdin) != NULL);
    assert(freopen("sabin.out", "w", stdout) != NULL);
    assert(freopen("debug.err", "w", stderr) != NULL);
    #endif

    int i, j, k;

    Trie *T = new Trie();

    cin >> N >> K >> M >> P >> Q;

    T->value = N;

    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= K; ++j)
            cin >> (rd[j] + 1);

        int pos = 0;
        for (j = 1; j <= P; ++j)
            for (k = 1; k <= K; ++k)
                proc[pos++] = rd[k][j];
        proc[pos] = 0;

        Insert(T, proc, 1);
    }

    for (i = 1; i <= M; ++i)
        cin >> (rd2[i] + 1);

    while (Q--) {
        int X;
        cin >> X;
        for (i = 1; i <= K; ++i)
            cin >> who[i];

        int pos = 0;
        for (j = 1; j <= X; ++j)
            for (k = 1; k <= K; ++k)
                proc[pos++] = rd2[who[k]][j];
        proc[pos] = 0;

        int answer = GetValue(T, proc);

        for (k = 1; k <= K; ++k)
            proc[pos++] = rd2[who[k]][X + 1];
        proc[pos] = 0;

        answer -= GetValue(T, proc);

        cout << answer << '\n';
    }

	return 0;
}
