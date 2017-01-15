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
#include <cassert>

using namespace std;

const int NMAX = 200010, BUFFER_SIZE = 1 << 20, LG2NMAX = 18;

typedef pair<int, int> PII;

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

InputReader in("reborn.in");
ofstream out("reborn.out");

int N, M, Q;
int teleport[NMAX], DP[LG2NMAX][NMAX];
vector<PII> weapons;

struct compare {
    bool operator()(const PII &lhs, const PII &rhs) {
        if (lhs.first < rhs.first) return true;
        if (lhs.first > rhs.first) return false;
        if (lhs.second > rhs.second) return true;
        return false;
    }
};

int main() {
    int i, j, k, x, y;

    in >> N >> M >> Q;

    for (i = 0; i < M; ++i) {
        in >> x >> y;
        weapons.push_back(make_pair(x, y));
    }

    sort(weapons.begin(), weapons.end());

    for (i = 0; i < M; ) {
        for (j = i + 1; j < M && weapons[j].first >= weapons[i].first && weapons[j].second <= weapons[i].second; ++j);
        for (k = weapons[i].first; k < weapons[i].second; ++k) {
            teleport[k] = weapons[i].second;
        }
        i = j;
    }

    for (i = 1; i <= N; ++i) DP[0][i] = teleport[i];

    for (i = 1; (1 << i) < N; ++i)
        for (j = 1; j <= N; ++j)
            DP[i][j] = DP[i - 1][DP[i - 1][j]];

    while(Q--) {
        in >> x >> y;
        if (x > y) swap(x, y);
        int left = 0, right = NMAX, mid, res = -1;

        for (mid = (left + right) >> 1; left <= right; mid = (left + right) >> 1) {
            int cx = x;

            for (int bit = 0; (1 << bit) <= mid; ++bit)
                if (mid & (1 << bit))
                    cx = DP[bit][cx];

            if (cx >= y) {
                res = mid;
                right = mid - 1;
            }
            else if (cx == 0) right = mid - 1;
            else left = mid + 1;
        }

        out << res << '\n';
    }

    in.close(), out.close();
    return 0;
}
