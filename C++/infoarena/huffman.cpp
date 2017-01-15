#include <bits/stdc++.h>

using namespace std;

typedef int64_t i64;
const int NMAX = 1e6 + 10;
const i64 inf = 0x3f3f3f3f3f3f3f3fLL;

int N;
int curr;
i64 answer;
int Q1[NMAX], Q2[NMAX], len[NMAX];
i64 val[NMAX];
int l1, r1 = -1, l2, r2 = -1;

struct Node {
    int sons[2];
    i64 value;
} nodes[2 * NMAX];

void DFS(int node, int level, i64 value) {
    if (node <= N) {
        len[node] = level;
        val[node] = value;
        return;
    }
    answer += nodes[node].value;
    DFS(nodes[node].sons[0], level + 1, value * 2);
    DFS(nodes[node].sons[1], level + 1, value * 2 + 1);
}

int main() {
    assert(freopen("huffman.in", "r", stdin));
    assert(freopen("huffman.out", "w", stdout));

    int i, j;

    scanf("%d", &N);
    for (i = 1; i <= N; ++i) {
        scanf("%d", &nodes[i].value);
        Q1[++r1] = i;
    }
    curr = N;

    while (1) {
        i64 val1 = inf, val2 = inf, val3 = inf;
        if (l1 + 1 <= r1)
            val1 = nodes[Q1[l1]].value + nodes[Q1[l1 + 1]].value;
        if (l2 + 1 <= r2)
            val2 = nodes[Q2[l2]].value + nodes[Q2[l2 + 1]].value;
        if (l1 <= r1 && l2 <= r2)
            val3 = nodes[Q1[l1]].value + nodes[Q2[l2]].value;
        i64 min_val = min(val1, min(val2, val3));

        if (min_val == inf)
            break;

        Q2[++r2] = ++curr;
        if (val1 == min_val) {
            nodes[curr].sons[0] = Q1[l1];
            nodes[curr].sons[1] = Q1[l1 + 1];
            nodes[curr].value = nodes[Q1[l1]].value + nodes[Q1[l1 + 1]].value;
            l1 += 2;
        } else if (val2 == min_val) {
            nodes[curr].sons[0] = Q2[l2];
            nodes[curr].sons[1] = Q2[l2 + 1];
            nodes[curr].value = nodes[Q2[l2]].value + nodes[Q2[l2 + 1]].value;
            l2 += 2;
        } else {
            nodes[curr].sons[0] = Q1[l1];
            nodes[curr].sons[1] = Q2[l2];
            nodes[curr].value = nodes[Q1[l1]].value + nodes[Q2[l2]].value;
            ++l1, ++l2;
        }
    }

    DFS(curr, 0, 0);

    printf("%lld\n", answer);
    for (i = 1; i <= N; ++i)
        printf("%d %lld\n", len[i], val[i]);

    return 0;
}
