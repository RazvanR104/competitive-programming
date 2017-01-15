//http://www.infoarena.ro/job_detail/1566224

#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e6 + 10, MOD = 666013;

int t, N, K;
int X[NMAX], C[NMAX];
int T[NMAX];

struct Element {
    int value, pos;
    bool operator<(const Element &rhs) const {
        return value < rhs.value;
    }
    bool operator<(const int &rhs) const {
        return value < rhs;
    }
} E[NMAX];

void Fix(int &value) {
    if (value >= MOD)
        value -= MOD;
    else if (value < 0)
        value += MOD;
}

int Query(int pos) {
    int ret = 0;
    for ( ; pos; pos -= (pos & -pos)) {
        ret += T[pos];
        Fix(ret);
    }
    return ret;
}

void Update(int pos, int value) {
    for ( ; pos <= N; pos += (pos & -pos)) {
        T[pos] += value;
        Fix(T[pos]);
    }
}

int main() {
	ios_base::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
	assert(freopen("subsiruri3.in", "r", stdin) != NULL);
    assert(freopen("subsiruri3.out", "w", stdout) != NULL);
    assert(freopen("debug.err", "w", stderr) != NULL);
    #endif

    int i;

    for (assert(scanf("%d", &t) == 1); t; --t) {
        assert(scanf("%d %d", &N, &K) == 2);
        memset(T, 0, sizeof(T));

        for (i = 1; i <= N; ++i) {
            assert(scanf("%d", &X[i]) == 1);
            E[i].value = X[i];
            E[i].pos = i;
        }

        stable_sort(E + 1, E + N + 1);
        for (i = 1; i <= N; ++i)
            C[E[i].pos] = i;

        int answer = 0;
        for (i = 1; i <= N; ++i) {
            int right = C[i];
            int left = lower_bound(E + 1, E + N + 1, X[i] - K) - E;
            int current = Query(right) - Query(left - 1);
            Fix(current);
            ++current;
            Fix(current);
            answer += current;
            Fix(answer);
            Update(C[i], current);
        }

        cout << answer << '\n';
    }

	return 0;
}
