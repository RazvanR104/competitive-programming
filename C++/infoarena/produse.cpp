#include <bits/stdc++.h>

using namespace std;

const int NMAX = 200010, MOD = 1e9 + 7;

int N, D, F[NMAX], InvF[NMAX], A[NMAX];
int DP[NMAX], Add[NMAX];
bool Seen[NMAX];

int FastExpo(int base, int expo) {
    int res = 1;
    while (expo) {
        if (expo & 1)
            res = (1LL * res * base) % MOD;
        base = (1LL * base * base) % MOD;
        expo >>= 1;
    }
    return res;
}

inline int Comb(int N, int K) {
    return ((1LL * F[N] * InvF[K]) % MOD * InvF[N - K]) % MOD;
}

int main() {
	ios_base::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
    freopen("produse.in", "r", stdin);
    freopen("produse.out", "w", stdout);
	freopen("debug.err", "w", stderr);
    #endif

    int i, j, k, value;

    cin >> N >> D;
    for (i = 1; i <= N; ++i) {
        cin >> value;
        ++A[value];
    }

    F[0] = 1;
    for (i = 1; i <= N; ++i)
        F[i] = (1LL * F[i - 1] * i) % MOD;
    InvF[N] = FastExpo(F[N], MOD - 2);
    for (i = N - 1; i >= 0; --i)
        InvF[i] = (1LL * InvF[i + 1] * (i + 1)) % MOD;

    vector<int> states;
    DP[1] = 1;
    for (i = 2; i <= D; ++i) {
        int prod = 1;
        states.clear();
        for (j = 1; j <= A[i]; ++j) {
            if (1LL * prod * i > D)
                break;
            prod *= i;
            for (k = 1; k <= D / prod; ++k) {
                if (Seen[k * prod] == 0) {
                    Seen[k * prod] = 1;
                    states.push_back(k * prod);
                }
                int last = DP[k] - Add[k];
                if (last < 0)
                    last += MOD;
                int curr = (1LL * Comb(A[i], j) * last) % MOD;
                DP[k * prod] += curr;
                if (DP[k * prod] >= MOD)
                    DP[k * prod] -= MOD;
                Add[k * prod] += curr;
                if (Add[k * prod] >= MOD)
                    Add[k * prod] -= MOD;
            }
        }
        for (const auto &it : states) {
            Add[it] = 0;
            Seen[it] = 0;
        }
    }

    int answer = 0;
    for (i = 2; i <= D; ++i) {
        answer += DP[i];
        if (answer >= MOD)
            answer -= MOD;
    }

    if (A[1] == 0) cout << answer << '\n';
    else {
        answer = 1LL * (answer + 1) * FastExpo(2, A[1]) % MOD;
        --answer;
        if (answer < 0)
            answer += MOD;
        cout << answer << '\n';
    }

	return 0;
}
