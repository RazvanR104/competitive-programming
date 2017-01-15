#include <bits/stdc++.h>

using namespace std;

const int LMAX = 25, MMAX = 8, ALPHABET_SIZE = 4, MOD = 666013;

inline int C(char x) {
    switch (x) {
        case 'A': return 0;
        case 'G': return 1;
        case 'C': return 2;
    }
    return 3;
}

void Fix(int &value) {
    if (value >= MOD)
        value -= MOD;
}

int curr;
struct Node {
    int node, fail, finish;
    int child[ALPHABET_SIZE], next[ALPHABET_SIZE];

    Node(int node = 0) : node(node), fail(0), finish(0) {
        memset(child, -1, sizeof(child));
        memset(next, -1, sizeof(next));
    }
} T[MMAX * LMAX];

int t, N, M;
char str[LMAX];

void InsertWord(int node, char *str, int pos) {
    if (*str == 0) {
        T[node].finish ^= (1 << pos);
        return;
    }

    if (T[node].child[C(*str)] == -1) {
        T[node].child[C(*str)] = ++curr;
        T[curr] = Node(curr);
    }

    InsertWord(T[node].child[C(*str)], str + 1, pos);
}

void BFS() {
    queue<int> Q;
    Q.push(1);
    T[1].fail = 1;

    while (!Q.empty()) {
        int now = Q.front();
        Q.pop();

        for (int i = 0; i < ALPHABET_SIZE; ++i) {
            if (T[now].child[i] == -1) {
                int fail = T[now].fail;
                for ( ; T[fail].child[i] == -1 && fail != 1; fail = T[fail].fail);
                if (T[fail].child[i] != -1 && T[fail].child[i] != T[now].child[i])
                    fail = T[fail].child[i];

                T[now].next[i] = fail;
                continue;
            }

            int fail = T[now].fail;
            for ( ; T[fail].child[i] == -1 && fail != 1; fail = T[fail].fail);
            if (T[fail].child[i] != -1 && T[fail].child[i] != T[now].child[i])
                fail = T[fail].child[i];

            T[T[now].child[i]].fail = fail;

            T[T[now].child[i]].finish |= T[fail].finish;

            Q.push(T[now].child[i]);
        }
    }

    T[1].fail = 0;
}

int DP1[MMAX * LMAX][1 << MMAX], DP2[MMAX * LMAX][1 << MMAX];

int main() {
	ios_base::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
	assert(freopen("adn2.in", "r", stdin) != NULL);
    assert(freopen("adn2.out", "w", stdout) != NULL);
    assert(freopen("debug.err", "w", stderr) != NULL);
    #endif

    int i, j, mask, k;

    for (cin >> t; t; --t) {
        cin >> N >> M;
        cin.get();

        curr = 0;
        T[++curr] = Node(1);

        for (i = 0; i < M; ++i) {
            cin >> str;
            InsertWord(1, str, i);
        }

        BFS();

        DP1[1][0] = 1;
        for (i = 1; i <= N; ++i) {
            for (j = 1; j <= curr; ++j) {
                for (mask = 0; mask < (1 << M); ++mask) {
                    if (DP1[j][mask] == 0)
                        continue;
                    for (k = 0; k < ALPHABET_SIZE; ++k) {
                        int son;
                        if (T[j].child[k] != -1)
                            son = T[j].child[k];
                        else
                            son = T[j].next[k];

                        DP2[son][mask | T[son].finish] += DP1[j][mask];
                        Fix(DP2[son][mask | T[son].finish]);
                    }
                }
            }

            memcpy(DP1, DP2, sizeof(DP1));
            memset(DP2, 0, sizeof(DP2));
        }

        int answer = 0;
        for (j = 1; j <= curr; ++j) {
            answer += DP1[j][(1 << M) - 1];
            Fix(answer);
        }

        cout << answer << '\n';

        for (i = 1; i <= curr; ++i)
            T[i] = Node();

        memset(DP1, 0, sizeof(DP1));
    }

	return 0;
}
