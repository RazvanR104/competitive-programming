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

const int BUFFER_SIZE = 1 << 25;

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

InputReader in("dist2.in");
ofstream out("dist2.out");

const int NMAX = 100010;

int N;
pair<int, int> Points[NMAX];

inline int Abs(int value) {
    if (value < 0) return -value;
    return value;
}

bool TestValue(int value) {
    int i, j;
    int MinY = Points[1].second, MaxY = Points[1].second;

    for (i = 2, j = 1; i <= N; ++i) {
        while (Points[i].first - Points[j].first > value) {
            MinY = min(MinY, Points[j].second);
            MaxY = max(MaxY, Points[j].second);
            ++j;
        }

        if (Abs(Points[i].second - MinY) > value || Abs(Points[i].second - MaxY) > value) return false;
    }
    return true;
}

int main() {
    int i;

    in >> N;
    for (i = 1; i <= N; ++i)
        in >> Points[i].first >> Points[i].second;
    sort(Points + 1, Points + N + 1);

    int left = 0, right = 2000000, mid, res;

    for (mid = (left + right) >> 1; left <= right; mid = (left + right) >> 1) {
        if (TestValue(mid)) {
            res = mid;
            right = mid - 1;
        } else left = mid + 1;
    }

    out << res << '\n';
    in.close(), out.close();
    return 0;
}
