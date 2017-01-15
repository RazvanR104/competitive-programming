#include <iostream>
#include <iomanip>
#include <fstream>

#include <algorithm>
#include <bitset>
#include <deque>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <utility>
#include <vector>

#if __cplusplus > 199711L
#include <unordered_map>
#include <unordered_set>
#endif

#include <cstdio>
#include <ctime>
#include <cmath>
#include <cstring>
#include <cstdlib>

using namespace std;

const int CMAX = 1025, BUFFER_SIZE = 1 << 20;

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

InputReader in("patrate4.in");
ofstream out("patrate4.out");

int N, K;
int DP[CMAX][CMAX];
vector<pair<pair<int, int>, int> > result;

void solve(const int x, const int y, const int len) {
    int points = DP[x + len - 1][y + len - 1] - DP[x + len - 1][y - 1] - DP[x - 1][y + len - 1] + DP[x - 1][y - 1];

    if (len == 0 || points == 0) return;

    if (points * K < len * len) {
        solve(x, y, len / 2);
        solve(x + len / 2, y, len / 2);
        solve(x, y + len / 2, len / 2);
        solve(x + len / 2, y + len / 2, len / 2);
        return;
    }

    result.push_back(make_pair(make_pair(x, y), len));
}

int main() {
    int i, j, x, y;

    in >> N >> K;
    for (i = 0; i < N; ++i) {
        in >> x >> y;
        DP[x][y] = 1;
    }

    for (i = 1; i < CMAX; ++i)
        for (j = 1; j < CMAX; ++j)
            DP[i][j] += DP[i - 1][j] + DP[i][j - 1] - DP[i - 1][j - 1];

    solve(1, 1, CMAX - 1);

    out << result.size() << '\n';
    for (i = 0; i < (int)result.size(); ++i)
        out << result[i].first.first << ' ' << result[i].first.second << ' ' << result[i].second << '\n';

    in.close(), out.close();
    return 0;
}
