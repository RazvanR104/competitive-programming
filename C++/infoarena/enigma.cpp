#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

const int ALPHABET_SIZE = 26, NMAX = 300010, SMAX = 110, MOD = 31333;

int N, M;
int DP[NMAX];
char S[NMAX], L[SMAX];

struct Trie {
    int sum;
    Trie *child[ALPHABET_SIZE];

    Trie() {
        sum = 0;
        memset(child, 0, sizeof(child));
    }
} *T;

void Insert(Trie *node, char *str) {
    if (*str == 0) {
        return;
    }

    if (node->child[*str - 'a'] == 0) {
        node->child[*str - 'a'] = new Trie();
        node->child[*str - 'a']->sum = 1;
    }
    else
        ++node->child[*str - 'a']->sum;
    return Insert(node->child[*str - 'a'], str + 1);
}

int main() {
	ios_base::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
    freopen("enigma.in", "r", stdin);
    freopen("enigma.out", "w", stdout);
	freopen("debug.err", "w", stderr);
    #endif

    int i, j;

    scanf("%d %d\n", &N, &M);
    gets(S + 1);

    T = new Trie();

    for (i = 1; i <= M; ++i) {
        gets(L + 1);
        Insert(T, L + 1);
    }

    DP[N + 1] = 1;
    Trie *node;
    for (i = N; i >= 1; --i) {
        node = T;
        for (j = i; j <= N && j <= i + 100; ++j) {
            node = node->child[S[j] - 'a'];
            if (node == 0)
                break;
            int times = node->sum;
            DP[i] = (DP[i] + DP[j + 1] * times) % MOD;
        }
    }

    cout << DP[1] << '\n';
	return 0;
}
