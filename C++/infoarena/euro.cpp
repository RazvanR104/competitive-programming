#include <bits/stdc++.h>

using namespace std;

const int NMAX = 40000;
typedef int64_t i64;

int N, T;
int V[NMAX], OUT[NMAX];
i64 S[NMAX], DP[NMAX];

int main() {
	ios_base::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
    freopen("euro.in", "r", stdin);
    freopen("euro.out", "w", stdout);
	freopen("debug.err", "w", stderr);
    #endif

    int i, j;

    cin >> N >> T;
    for (i = 1; i <= N; ++i) {
        cin >> V[i];
        S[i] = S[i - 1] + V[i];
    }

    deque<int> D;
    D.push_front(0);

    for (i = 1; i <= N; ++i) {
        while (D.size() >= 2 && OUT[D[1]] == i)
            D.pop_front();
        DP[i] = DP[D.front()] + (S[i] - S[D.front()]) * i - T;

        while (!D.empty()) {
            int bk = D.back();
            OUT[i] = i;
            for (int bit = (1 << 16); bit > 0; bit >>= 1) {
                if (OUT[i] + bit <= N) {
                    i64 value_i = DP[i] + (S[OUT[i] + bit] - S[i]) * (OUT[i] + bit) - T;
                    i64 value_bk = DP[bk] + (S[OUT[i] + bit] - S[bk]) * (OUT[i] + bit) - T;
                    if (value_bk > value_i)
                        OUT[i] += bit;
                }
            }
            ++OUT[i];

            if (OUT[i] <= OUT[bk])
                D.pop_back();
            else
                break;
        }
        D.push_back(i);
    }

    cout << DP[N] << '\n';
	return 0;
}
