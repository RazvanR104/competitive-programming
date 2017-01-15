#include <bits/stdc++.h>

#define pb push_back

using namespace std;

const int NMAX = 20010, LG2NMAX = 16, ASZ = 255;

int N, K;
int O[LG2NMAX][2 * NMAX], C[ASZ], Push[NMAX], SO[NMAX];
char str[NMAX], sstr[NMAX];

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

int lg2(int value) {
    int res = -1;
    while (value) {
        ++res;
        value /= 2;
    }
    return res;
}

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
    freopen("substr.in", "r", stdin);
    freopen("substr.out", "w", stdout);
	freopen("debug.err", "w", stderr);
    #endif

    int i, j;

    cin >> N >> K;
    cin >> (str + 1);

    memcpy(sstr, str, sizeof(sstr));
    sort(sstr + 1, sstr + N + 1);

    int pos = 1;
    for (i = 1; i <= N; ++i) {
        if (C[sstr[i]] == 0)
            C[sstr[i]] = pos++;
    }

    for (i = 1; i <= N; ++i) {
        O[0][i] = C[str[i]];
    }

    for (i = 1; pw2(i - 1) <= N; ++i) {
        S.clear();
        for (j = 1; j <= N; ++j)
            S.pb(Suffix(j, O[i - 1][j], O[i - 1][j + pw2(i - 1)]));
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
        SO[O[lg][i] + Push[O[lg][i]]++] = i;
    }

    int answer = 0;
    for (i = 1; i + K - 1 <= N; ++i) {
        answer = max(answer, LCP(SO[i], SO[i + K - 1], lg));
    }

    cout << answer << '\n';
	return 0;
}
