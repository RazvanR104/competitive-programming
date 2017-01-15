#include <cstdio>
#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

const int NMAX = 1010;

typedef int16_t i16;

int N, answer;
i16 V[NMAX][NMAX], BIT[2 * NMAX], RT[NMAX][NMAX], LT[NMAX][NMAX], LL[NMAX][NMAX], RR[NMAX][NMAX];
char P[NMAX][NMAX], tmp[NMAX][NMAX];

int Query(int pos) {
    pos += N;
    int res = 0;
    for ( ; pos > 0; pos -= pos & (-pos))
        res += BIT[pos];
    return res;
}

void Update(int pos, int value) {
    pos += N;
    for ( ; pos <= 2 * N; pos += pos & (-pos))
        BIT[pos] += value;
}


struct Event {
    int sign, pos;

    Event() {}
    Event(int sign, int pos) : sign(sign), pos(pos) {}
};
vector<Event> E[NMAX];

inline void Solve() {
    int i, j;

    for (i = N; i >= 1; --i) {
        for (j = 1; j <= N; ++j) {
            if (P[i][N - j + 1] == 0)
                LL[i][j] = 0;
            if (P[i][j] == 0)
                LL[i][j] = RR[i][j] = LT[i][j] = V[i][j] = 0;
            else {
                LT[i][j] = LT[i][j - 1] + 1;
                LL[i][j] = LL[i + 1][j + 1] + 1;
                RR[i][j] = RR[i + 1][j - 1] + 1;

                V[i][j] = min(LL[i][j], RR[i][j]) - 1;
            }
        }
        for (j = N; j >= 1; --j) {
            if (P[i][j] == 0)
                RT[i][j] = 0;
            else RT[i][j] = RT[i][j + 1] + 1;
            RT[i][j] = min(RT[i][j], LT[i][j]);
        }
    }

    bool seen[NMAX];
    for (j = 1; j <= N; ++j) {
        memset(seen, 0, sizeof(seen));
        memset(BIT, 0, sizeof(BIT));
        for (i = 1; i <= N; ++i) {
            if (P[i][j] == 0 || V[i][j] == 0)
                continue;
            if (seen[i + 1] == 0) {
                seen[i + 1] = 1;
                E[i + 1].clear();
            }
            if (seen[i + V[i][j] + 1] == 0) {
                seen[i + V[i][j] + 1] = 1;
                E[i + V[i][j] + 1].clear();
            }
            E[i + 1].push_back(Event(1, 1));
            E[i + V[i][j] + 1].push_back(Event(-1, V[i][j] + 1));
        }

        int pos = 1, add = 0;
        for (i = 1; i <= N; ++i) {
            while (pos <= i) {
                if (seen[pos] == 0) {
                    ++pos;
                    continue;
                }
                for (auto it : E[pos])
                    Update(it.pos - add, it.sign);
                ++pos;
            }
            answer += Query(RT[i][j] - add);
            ++add;
        }
    }
}

void Rotate() {
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            tmp[N - j + 1][i] = P[i][j];
        }
    }
    memcpy(P, tmp, sizeof(P));
}

int main() {
    ios_base::sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen("piramid.in", "r", stdin);
    freopen("piramid.out", "w", stdout);
    freopen("debug.err", "w", stderr);
    #endif

    int i, j;

    scanf("%d\n", &N);
    for (i = 1; i <= N; ++i) {
        gets(P[i] + 1);
        for (j = 1; j <= N; ++j)
            P[i][j] -= '0';
    }

    Solve();

    for (i = 0; i < 3; ++i) {
        Rotate();
        Solve();
    }

    cout << answer << '\n';
    return 0;
}
