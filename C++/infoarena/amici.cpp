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

const int NMAX = 1024, BUFFER_SIZE = 1 << 20;

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
            while(!isdigit(buffer[cursor])) {
                advance();
            }
            while(isdigit(buffer[cursor])) {
                n = n * 10 + buffer[cursor] - '0';
                advance();
            }
            return *this;
        }
        inline void close() {
            fclose(file);
        }
    private:
        int cursor;
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

InputReader in("amici.in");
ofstream out("amici.out");

int T, N, M;
int cycle[NMAX], res[NMAX];
bool G[NMAX][NMAX];

int main() {
    int x, y, i, j;

    for (in >> T; T; --T) {
        in >> N >> M;

        memset(G, true, sizeof(G));
        for (i = 1; i <= N; ++i) cycle[i] = i;
        cycle[N + 1] = 1;

        while(M--) {
            in >> x >> y;
            G[x][y] = G[y][x] = false;
        }

        for (i = 1; i <= N; ++i) {
            if (G[cycle[i]][cycle[i + 1]]) continue;
            for (j = 1; j < i - 1; ++j)
                if (G[cycle[i]][cycle[j]] && G[cycle[i + 1]][cycle[j + 1]]) {
                    swap(cycle[i], cycle[j + 1]);
                    reverse(cycle + j + 2, cycle + i);
                    break;
                }

            if (j < i - 1) continue;

            for (j = i + 2; j <= N; ++j)
                if (G[cycle[i]][cycle[j]] && G[cycle[i + 1]][cycle[j + 1]]) {
                    swap(cycle[i + 1], cycle[j]);
                    reverse(cycle + i + 2, cycle + j);
                    break;
                }
        }

        for (i = 1; i <= N; ++i) res[cycle[i]] = cycle[i + 1];
        for (i = 1; i <= N; ++i) out << res[i] << ' ';
        out << '\n';
    }

    in.close(), out.close();
    return 0;
}
