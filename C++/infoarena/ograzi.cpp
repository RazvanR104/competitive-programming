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
typedef unsigned int uint;
typedef vector<pair<int, int > >::iterator _iterator;

const int BUFFER_SIZE = 1 << 20, MOD = 666013, MULT = 4201;

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

InputReader in("ograzi.in");
ofstream out("ograzi.out");

int N, M, WW, HH;
vector<pair<int, int> > H[MOD];

inline int generate_hash(const int &x, const int &y) {
    uint _x = x / WW - (x % WW == 0);
    uint _y = y / HH - (y % HH == 0);

    return (_x * MULT + _y) % MOD;
}

inline bool check_if_hash_exists(const int &x, const int &y, const int &hash_key) {
    for (_iterator it = H[hash_key].begin(); it != H[hash_key].end(); ++it)
        if (x >= it->first && y >= it->second && x <= it->first + WW && y <= it->second + HH) return true;

    return false;
}

inline void insert_hash(const int &x, const int &y) {
    int hash_key = generate_hash(x + WW, y + HH);
    H[hash_key].push_back(make_pair(x, y));
}

int main() {
    int i, x, y, res = 0;

    in >> N >> M >> WW >> HH;
    for (i = 0; i < N; ++i) {
        in >> x >> y;
        insert_hash(x, y);
    }

    for (i = 0; i < M; ++i) {
        in >> x >> y;
        if (check_if_hash_exists(x, y, generate_hash(x, y)) || check_if_hash_exists(x, y, generate_hash(x + WW, y)) || check_if_hash_exists(x, y, generate_hash(x, y + HH)) || check_if_hash_exists(x, y, generate_hash(x + WW, y + HH)))
            ++res;
    }

    out << res << '\n';
    in.close(), out.close();
    return 0;
}
