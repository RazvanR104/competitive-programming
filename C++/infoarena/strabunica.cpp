#include <bits/stdc++.h>

using namespace std;

const int NMAX = 200010;

int N;
int V[NMAX], lt[NMAX], rt[NMAX];

int main() {
    assert(freopen("strabunica.in", "r", stdin) != NULL);
    assert(freopen("strabunica.out", "w", stdout) != NULL);

    int i;

    scanf("%d", &N);
    for (i = 1; i <= N; ++i)
        scanf("%d", &V[i]);

    stack<int> S;
    for (i = 1; i <= N; ++i) {
        while (!S.empty() && V[i] <= V[S.top()])
            S.pop();
        if (S.empty())
            lt[i] = 0;
        else
            lt[i] = S.top();
        S.push(i);
    }

    S = stack<int>();
    for (i = N; i >= 1; --i) {
        while (!S.empty() && V[i] <= V[S.top()])
            S.pop();
        if (S.empty())
            rt[i] = N + 1;
        else
            rt[i] = S.top();
        S.push(i);
    }

    int64_t answer = 0;
    for (i = 1; i <= N; ++i)
        answer = max(answer, int64_t(rt[i] - lt[i] - 1) * V[i]);

    cout << answer << '\n';
    return 0;
}
