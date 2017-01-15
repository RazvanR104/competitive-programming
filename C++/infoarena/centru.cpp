#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1010, inf = 0x3f3f3f3f, BUFFER_SIZE = 1 << 20;
const int dl[] = {-1, 0, 1, 0};
const int dc[] = {0, -1, 0, 1};

int N, K;
int dist[NMAX][NMAX];
int YMin[NMAX], YMax[NMAX];

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
} fin("centru.in");

bool Check(int value) {
    int i, j;

    for (i = 0; i < N; ++i) {
        YMin[i] = inf;
        YMax[i] = -inf;
        for (j = 0; j < N; ++j)
            if (dist[i][j] > value) {
                YMin[i] = min(YMin[i], j);
                YMax[i] = max(YMax[i], j);
            }
    }

    for (i = 0; i < N; ++i) {
        int bottom = 0, top = N - 1;
        for (j = 0; j < N && bottom <= top; ++j) {
            if (YMin[j] == inf)
                continue;
            top = min(top, value - abs(i - j) + YMin[j]);
            top = min(top, value - abs(i - j) + YMax[j]);
            bottom = max(bottom, YMin[j] - value + abs(i - j));
            bottom = max(bottom, YMax[j] - value + abs(i - j));
        }

        if (bottom <= top)
            return 1;
    }

    return 0;
}

int main() {
    assert(freopen("centru.in", "r", stdin));
    assert(freopen("centru.out", "w", stdout));

    int i, j, x, y;
    queue<pair<int, int>> Q;

//  scanf("%d %d", &N, &K);
    fin >> N >> K;
    for (i = 1; i <= K; ++i) {
//      scanf("%d %d", &x, &y);
        fin >> x >> y;
        dist[x][y] = 1;
        Q.push({x, y});
    }

    while (!Q.empty()) {
        tie(x, y) = Q.front();
        Q.pop();

        for (i = 0; i < 4; ++i) {
            int nx = x + dl[i];
            int ny = y + dc[i];

            if (nx < 0 || nx > N - 1 || ny < 0 || ny > N - 1 || dist[nx][ny])
                continue;

            dist[nx][ny] = dist[x][y] + 1;
            Q.push({nx, ny});
        }
    }

    for (i = 0; i < N; ++i)
        for (j = 0; j < N; ++j)
            --dist[i][j];

    int answer = 0, lg2 = 1;
    while (lg2 < N + N)
        lg2 <<= 1;

    for ( ; lg2; lg2 >>= 1)
        if (!Check(answer + lg2))
            answer += lg2;

    cout << answer + 1 << '\n';
    return 0;
}
