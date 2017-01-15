#include <bits/stdc++.h>

using namespace std;

const int NMAX = 5, LMAX = 50010, MOD1 = 43271, MOD2 = 43403, M1 = 2, M2 = 3;

int N;
int H1[NMAX][LMAX], H2[NMAX][LMAX], pw1[LMAX], pw2[LMAX], len[NMAX];
char str[NMAX][LMAX];
vector<pair<int, char>> HT[MOD1];

char Insert(int hash1, int hash2, int pos) {
    for (auto &it : HT[hash1])
        if (it.first == hash2) {
            it.second |= (1 << pos);
            return it.second;
        }

    HT[hash1].push_back({hash2, (1 << pos)});
    return (1 << pos);
}

void Clear(const vector<int> &where) {
    for (int pos : where)
        HT[pos].clear();
}

pair<int, int> ComputeHash(int pos, int lo, int hi) {
    int hash1 = (H1[pos][hi] - pw1[hi - lo + 1] * H1[pos][lo - 1]) % MOD1;
    int hash2 = (H2[pos][hi] - pw2[hi - lo + 1] * H2[pos][lo - 1]) % MOD2;
    if (hash1 < 0) hash1 += MOD1;
    if (hash2 < 0) hash2 += MOD2;
    return {hash1, hash2};
}

int Check(int value) {
    vector<int> hashes;
    for (int i = 0; i < N; ++i) {
        for (int j = 1; j + value - 1 <= len[i]; ++j) {
            int hash1, hash2;
            tie(hash1, hash2) = ComputeHash(i, j, j + value - 1);
            int val = Insert(hash1, hash2, i);
            hashes.push_back(hash1);
            if (val == (1 << N) - 1) {
                Clear(hashes);
                return 1;
            }
        }
    }
    Clear(hashes);
    return 0;
}

int main() {
	ios_base::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
	assert(freopen("subsecvente2.in", "r", stdin) != NULL);
    assert(freopen("subsecvente2.out", "w", stdout) != NULL);
    assert(freopen("debug.err", "w", stderr) != NULL);
    #endif

    int i, j, lenmax = 0, lenmin = 1e9;

    cin >> N;

    for (i = 0; i < N; ++i) {
        cin >> (str[i] + 1);
        len[i] = strlen(str[i] + 1);
        lenmax = max(lenmax, len[i]);
        lenmin = min(lenmin, len[i]);
    }

    for (i = 0; i < N; ++i) {
        for (j = 1; j <= len[i]; ++j) {
            H1[i][j] = (H1[i][j - 1] * M1 + str[i][j]) % MOD1;
            H2[i][j] = (H2[i][j - 1] * M2 + str[i][j]) % MOD2;
        }
    }

    pw1[0] = pw2[0] = 1;
    for (i = 1; i <= lenmax; ++i) {
        pw1[i] = pw1[i - 1] * M1 % MOD1;
        pw2[i] = pw2[i - 1] * M2 % MOD2;
    }

    int answer = 0;
    for (int bit = (1 << 15); bit; bit >>= 1)
        if (answer + bit <= lenmin && Check(answer + bit))
            answer += bit;

    cout << answer << '\n';
	return 0;
}
