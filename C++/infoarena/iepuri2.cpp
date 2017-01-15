#include <bits/stdc++.h>

using namespace std;

const int NMAX = 110, MOD = 30011;

int N, K;
int DP[NMAX][NMAX];
int sum[NMAX];
bool notroot[NMAX];
vector<int> T[NMAX];

void DFS(int node) {
    if (T[node].size() == 0) {
        for (int i = 1; i <= K; ++i)
            DP[node][i] = 1;
        return;
    }

    for (const int &it: T[node])
        DFS(it);

    memset(sum, 0, sizeof sum);
    for (int i = K - 1; i >= 1; --i) {
        int prod = 1;
        for (const int &it: T[node]) {
            sum[it] += DP[it][i + 1];
            if (sum[it] >= MOD) sum[it] -= MOD;
            prod = (prod * sum[it]) % MOD;
        }
        DP[node][i] = prod;
    }
}

int main() {
    assert(freopen("iepuri2.in", "r", stdin));
    assert(freopen("iepuri2.out", "w", stdout));

    int i, x, y;

    cin >> N >> K;
    for (i = 1; i < N; ++i) {
        cin >> x >> y;
        T[x].push_back(y);
        notroot[y] = 1;
    }

    int root = 1;
    while (notroot[root])
        ++root;

    DFS(root);
    int answer = 0;
    for (i = 1; i <= K; ++i) {
        answer += DP[root][i];
        if (answer >= MOD)
            answer -= MOD;
    }

    cout << answer << '\n';
    return 0;
}
