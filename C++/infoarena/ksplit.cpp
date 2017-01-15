#include <bits/stdc++.h>

using namespace std;

const int NMAX = 100010, inf = 0x3f3f3f3f;
typedef int64_t i64;

int N;
int V[NMAX];
int NMaxR[NMAX], NMinR[NMAX];
i64 MaxR[NMAX], MinR[NMAX];

int main() {
	ios_base::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
	assert(freopen("ksplit.in", "r", stdin) != NULL);
    assert(freopen("ksplit.out", "w", stdout) != NULL);
    assert(freopen("debug.err", "w", stderr) != NULL);
    #endif

    int i;
    cin >> N;
    for (i = 1; i <= N; ++i)
        cin >> V[i];

    for (i = N; i >= 1; --i) {
        if (MaxR[i + 1] < 0) {
            MaxR[i] = V[i];
            NMaxR[i] = 1;
        } else {
            MaxR[i] = MaxR[i + 1] + V[i];
            NMaxR[i] = NMaxR[i + 1] + 1;
        }

        if (MinR[i + 1] > 0) {
            MinR[i] = V[i];
            NMinR[i] = 1;
        } else {
            MinR[i] = MinR[i + 1] + V[i];
            NMinR[i] = NMinR[i + 1] + 1;
        }
    }

    i64 answer = 0;
    int len = 0;
    i64 MinL = 0, MaxL = 0;
    int NMinL = 0, NMaxL = 0;
    for (i = 1; i < N; ++i) {
        if (MaxL < 0) {
            MaxL = V[i];
            NMaxL = 1;
        } else {
            MaxL += V[i];
            ++NMaxL;
        }

        if (MinL > 0) {
            MinL = V[i];
            NMinL = 1;
        } else {
            MinL += V[i];
            ++NMinL;
        }

        if (answer < abs(MaxL - MinR[i + 1])) {
            answer = abs(MaxL - MinR[i + 1]);
            len = NMaxL + NMinR[i + 1];
        } else if (answer == abs(MaxL - MinR[i + 1]) && len < NMaxL + NMinR[i + 1])
            len = NMaxL + NMinR[i + 1];

        if (answer < abs(MinL - MaxR[i + 1])) {
            answer = abs(MinL - MaxR[i + 1]);
            len = NMinL + NMaxR[i + 1];
        } else if (answer == abs(MinL - MaxR[i + 1]) && len < NMinL + NMaxR[i + 1])
            len = NMinL + NMaxR[i + 1];
    }

    cout << answer << '\n' << len << '\n';
	return 0;
}
