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

typedef long long int64;

const int BUFFER_SIZE = 1 << 20, NMAX = 100010;

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

InputReader in("distancesum.in");
ofstream out("distancesum.out");

int N, M;
int PointsX[NMAX], PointsY[NMAX];
int64 SX[NMAX], SY[NMAX];

int main() {
    int i, x, y;
    int64 res = 0;

    in >> N >> M;
    for (i = 1; i <= N; ++i) {
        in >> x >> y;
        PointsX[i] = x + y;
        PointsY[i] = y - x;
    }

    sort(PointsX + 1, PointsX + N + 1);
    sort(PointsY + 1, PointsY + N + 1);

    for (i = 1; i <= N; ++i) {
        SX[i] = SX[i - 1] + PointsX[i];
        SY[i] = SY[i - 1] + PointsY[i];
    }

    while(M--) {
        in >> x >> y;
        int nx = x + y, ny = y - x;

        int posX = upper_bound(PointsX + 1, PointsX + N + 1, nx) - PointsX - 1;
        res = 1LL * posX * nx - SX[posX] + SX[N] - SX[posX] - 1LL * (N - posX) * nx;

        int posY = upper_bound(PointsY + 1, PointsY + N + 1, ny) - PointsY - 1;
        res += 1LL * posY * ny - SY[posY] + SY[N] - SY[posY] - 1LL * (N - posY) * ny;

        out << res / 2 << '\n';
    }

    in.close(), out.close();
    return 0;
}
