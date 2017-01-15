#include <bits/stdc++.h>

using namespace std;

const int NMAX = 100010;

int N, M;
int V[NMAX];
int where[2 * NMAX];
pair<int, int> answer[2 * NMAX];

int main() {
    assert(freopen("diff.in", "r", stdin));
    assert(freopen("diff.out", "w", stdout));

    int i, j;

    scanf("%d %d", &N, &M);
    for (i = 1; i <= N; ++i) {
        scanf("%d", &V[i]);
        if (V[i] == 0)
            V[i] = -1;
        V[i] += V[i - 1];
    }

    where[V[1] + NMAX] = 1;
    answer[V[1] + NMAX] = {1, 1};
    int left = V[1], right = V[1];
    for (i = 2; i <= N && left >= -N && right <= N; ++i) {
        if (V[i] > right)
            right = V[i];
        else if (V[i] < left)
            left = V[i];
        where[V[i] + NMAX] = i;
        answer[V[i] + NMAX] = {1, i};

        while (where[V[i] - right - 1 + NMAX] && right <= N) {
            answer[right + 1 + NMAX] = {where[V[i] - right - 1 + NMAX] + 1, i};
            ++right;
        }

        while (where[V[i] - left + 1 + NMAX] && left >= -N) {
            answer[left - 1 + NMAX] = {where[V[i] - left + 1 + NMAX] + 1, i};
            --left;
        }
    }

    while (M--) {
        int query;
        scanf("%d", &query);
        if (query > N || query < -N || answer[query + NMAX].first == 0) {
            cout << "-1\n";
            continue;
        }

        cout << answer[query + NMAX].first << ' ' << answer[query + NMAX].second << '\n';
    }

    return 0;
}
