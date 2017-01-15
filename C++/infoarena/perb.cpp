#include <bits/stdc++.h>

using namespace std;

const int NMAX = 610, AMAX = 100, inf = 0x3f3f3f3f, BUFFER_SIZE = 1 << 21;

int N, M;
int C[AMAX], DP[NMAX][NMAX], answer[NMAX][NMAX], cnt[NMAX / 2][5], added[NMAX], MOD[NMAX], max_index[NMAX], DIV[NMAX];
char str[NMAX];

class InputReader {
    public:
        InputReader() {}
        InputReader(const char* filename) {
            file = fopen(filename, "r");
            cursor = 0;
            fread(buffer, BUFFER_SIZE, 1, file);
        }
        inline InputReader & operator >> (int &n) {
            n = 0;
            sign = 1;
            while(!isdigit(buffer[cursor])) {
                if (buffer[cursor] == '-') sign = -1;
                advance();
            }
            while(isdigit(buffer[cursor])) {
                n = n * 10 + buffer[cursor] - '0';
                advance();
            }
            n *= sign;
            return *this;
        }

        inline InputReader & operator >> (char *str) {
            while(!isalpha(buffer[cursor]))
                advance();
            while(isalpha(buffer[cursor])) {
                *str = buffer[cursor];
                str++;
                advance();
            }
            *str = 0;
            return *this;
        }

        inline void close() {
            fclose(file);
        }
    private:
        int cursor, sign;
        char buffer[BUFFER_SIZE];
        FILE* file;
        inline void advance() {
            ++cursor;
            if(cursor == BUFFER_SIZE) {
                cursor = 0;
                fread(buffer, BUFFER_SIZE, 1, file);
            }
        }
};

int main() {
	ios_base::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
	assert(freopen("perb.in", "r", stdin) != NULL);
    assert(freopen("perb.out", "w", stdout) != NULL);
    assert(freopen("debug.err", "w", stderr) != NULL);
    #endif

    InputReader cin("perb.in");

    C['A'] = 0;
    C['C'] = 1;
    C['G'] = 2;
    C['T'] = 3;

    int d, i, j, k;

    cin >> N >> M;
    cin >> (str + 1);

    for (i = 1; i <= N; ++i)
        str[i] = C[str[i]];

    memset(answer, inf, sizeof(answer));
    for (d = 1; d <= N / 2; ++d) {
        for (i = 1; i <= N; ++i) {
            MOD[i] = MOD[i - 1] + 1;
            DIV[i] = DIV[i - 1];
            if (MOD[i] >= d) {
                MOD[i] -= d;
                ++DIV[i];
            }
        }


        for (i = 1; i <= N; ++i) {
            //memset(cnt, 0, sizeof(cnt));
            //memset(added, 0, sizeof(added));
            //memset(max_index, 0, sizeof(max_index));

            for (j = 0; j < d; ++j) {
                added[j] = max_index[j] = 0;
                cnt[j][0] = cnt[j][1] = cnt[j][2] = cnt[j][3] = cnt[j][4] = 0;
            }

            for (j = i; j <= N; ++j) {
                int index = MOD[j - i + 1];
                ++cnt[index][str[j]];
                ++cnt[index][4];

                if (cnt[index][str[j]] > cnt[index][max_index[index]])
                    max_index[index] = str[j];

                int add = cnt[index][4] - cnt[index][max_index[index]];

                DP[i][j] = DP[i][j - 1] - added[index] + add;
                added[index] = add;

                if (index == 0 && DIV[j - i + 1] > 1)
                    answer[i][j] = min(answer[i][j], DP[i][j]);
            }
        }
    }

    char line[20];
    getchar();
    while (M--) {
        cin >> i >> j;
        //cout << answer[i][j] << '\n';
        printf("%d\n", answer[i][j]);
    }

	return 0;
}
