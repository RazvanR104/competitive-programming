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

const int BUFFER_SIZE = 1 << 18, MOD = 100021, NMAX = 2010;

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

typedef vector<int>::iterator _iterator;

InputReader in("progr.in");
ofstream out("progr.out");

int T, N;
vector<int> H[MOD], values;

inline bool exists(const int &value) {
    if (value < 0) return false;
    int pos = value % MOD;

    for (_iterator it = H[pos].begin(); it != H[pos].end(); ++it)
        if (*it == value) return true;

    return false;
}

inline void hash_insert(const int &value) {
    H[value % MOD].push_back(value);
}

int main() {
    int value, i, j, res;

    for (in >> T; T; --T) {
        res = 0;
        memset(H, 0, sizeof(H));
        values.clear();
        for (in >> N; N; --N) {
            in >> value;
            hash_insert(value);
            values.push_back(value);
        }

        sort(values.begin(), values.end());

        for (i = 0; i < (int)values.size() - 1; ++i)
            for (j = i + 1; j < (int)values.size(); ++j)
                if (!exists(2 * values[i] - values[j])) ++res;

        out << res << '\n';
    }

    out.close();
    return 0;
}
