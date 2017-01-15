#include <bits/stdc++.h>

using namespace std;

const int NMAX = 200010, LG2NMAX = 20;

int N;
int O[LG2NMAX][NMAX], SO[NMAX], Push[NMAX], pos[NMAX], from[2][NMAX], lcp[NMAX], lt[NMAX], rt[NMAX], DP[NMAX];
char Read[NMAX], str[NMAX], parsed[NMAX];

struct Suffix {
    int pos, pos1, pos2;

    Suffix() {}
    Suffix(int _pos, int _pos1, int _pos2) : pos(_pos), pos1(_pos1), pos2(_pos2) {}

    bool operator<(const Suffix &rhs) const {
        if (pos1 < rhs.pos1)
            return true;
        if (pos1 > rhs.pos1)
            return false;
        if (pos2 < rhs.pos2)
            return true;
        return false;
    }

    bool operator==(const Suffix &rhs) const {
        return pos1 == rhs.pos1 && pos2 == rhs.pos2;
    }
};
vector<Suffix> S;

int pw2(int value) {
    return (1 << value);
}

int LCP(int pos1, int pos2, int lg) {
    int res = 0;
    for (int bit = lg; bit >= 0; --bit) {
        if (pos1 + pw2(bit) - 1 <= N &&
            pos2 + pw2(bit) - 1 <= N &&
            O[bit][pos1] == O[bit][pos2]) {
            pos1 += pw2(bit);
            pos2 += pw2(bit);
            res += pw2(bit);
        }
    }
    return res;
}

int main() {
	ios_base::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
	assert(freopen("revsecv.in", "r", stdin) != NULL);
    assert(freopen("revsecv.out", "w", stdout) != NULL);
    assert(freopen("debug.err", "w", stderr) != NULL);
    #endif

    int i, j;

    cin >> (Read + 1);
    N = strlen(Read + 1);
    int _N = N;
    memcpy(str + 1, Read + 1, N * sizeof(char));
    reverse(Read + 1, Read + N + 1);
    str[N + 1] = '#';
    memcpy(str + N + 2, Read + 1, N * sizeof(char));
    N = 2 * N + 1;

    for (i = 1; i <= N; ++i)
        O[0][i] = str[i] - 'a' + 1;

    for (i = 1; pw2(i - 1) <= N; ++i) {
        S.clear();
        for (j = 1; j <= N; ++j)
            S.push_back(Suffix(j, O[i - 1][j], O[i - 1][j + pw2(i - 1)]));
        sort(S.begin(), S.end());
        for (j = 1; j <= N; ++j) {
            if (j > 1 && S[j - 1] == S[j - 2])
                O[i][S[j - 1].pos] = O[i][S[j - 2].pos];
            else
                O[i][S[j - 1].pos] = j;
        }
    }

    int lg = i - 1;
    for (i = 1; i <= N; ++i) {
        SO[O[lg][i] + Push[O[lg][i]]] = i;
        if (i <= _N)
            from[0][O[lg][i] + Push[O[lg][i]]] = 1;
        else if (i >= _N + 2)
            from[1][O[lg][i] + Push[O[lg][i]]] = 1;
        pos[i] = O[lg][i] + Push[O[lg][i]];
        ++Push[O[lg][i]];
    }

    for (i = 1; i <= N; ++i) {
        from[0][i] += from[0][i - 1];
        from[1][i] += from[1][i - 1];
    }

    for (i = 1; i < N; ++i)
        lcp[i] = LCP(SO[i], SO[i + 1], lg);

    for (i = 1; i <= N; ++i)
        cerr << (str + SO[i]) << '\n';

    stack<pair<int, int>> S;
    S.push({lcp[1], 1});

    for (i = 2; i < N; ++i) {
        while (!S.empty() && S.top().first >= lcp[i])
            S.pop();
        if (!S.empty())
            lt[i] = S.top().second;
        S.push({lcp[i], i});
    }

    S = stack<pair<int, int>>();
    S.push({lcp[N - 1], N - 1});
    for (i = N - 2; i >= 1; --i) {
        while (!S.empty() && S.top().first >= lcp[i])
            S.pop();
        if (!S.empty())
            rt[i] = S.top().second;
        else
            rt[i] = N;
        S.push({lcp[i], i});
    }
    rt[N - 1] = N;

    unordered_set<int64_t> seen;
    int64_t answer = 0;
    for (i = 1; i < N; ++i) {
        int64_t key = 1ll * lt[i] * NMAX + rt[i];
        if (seen.count(key))
            continue;
        int left = lt[i], right = rt[i];
        seen.insert(key);
        int first = from[0][right] - from[0][left];
        int second = from[1][right] - from[1][left];
        int lower = max(lcp[left], lcp[right]);
        answer += 1LL * first * second * (lcp[i] - lower);
    }

    int pos = 0;
    parsed[0] = '$';
    for(i = 1; i <= _N; ++i) {
        parsed[++pos] = str[i];
        DP[pos] = 1;
        parsed[++pos] = '$';
    }

    int C = 0, R = 0;
    int64_t sub = 0;
    for (j = 1; j < pos; ++j) {
        int mirror = 2 * C - j;

        if(j <= R)
            DP[j] = min(DP[mirror], R - j + 1);

        int left = j - DP[j] + 1;
        int right = j + DP[j] - 1;

        while(left - 2 >= 1 && right + 2 < pos && parsed[left - 2] == parsed[right + 2]) {
            left -= 2;
            right += 2;
            DP[j] += 2;
        }

        if (right > R) {
            C = j;
            R = right;
        }

        sub += 1LL * ((DP[j] + 1) / 2) * ((DP[j] + 1) / 2);
    }

    cout << (answer - sub) / 2 << '\n';

	return 0;
}
