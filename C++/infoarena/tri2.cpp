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
 
const int BUFFER_SIZE = 1 << 20, NMAX = 1010;
 
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
 
InputReader in("tri2.in");
ofstream out("tri2.out");
 
typedef pair<int, int> point;
 
int N, M, rx, ry;
int BIT[NMAX], res[NMAX][NMAX];
vector<point> P(1, point(-1, -1));
vector<int> X(1, -1), normalization(1, -1), _left, _right;
 
inline void split(const int pos) {
    for(int i = 1; i < (int)P.size(); ++i) {
        if (i == pos) continue;
        if (P[i].first < P[pos].first) _left.push_back(i);
        else _right.push_back(i);
    }
}
 
bool left_compare(const int &lhs, const int &rhs) {
    return (1LL * (P[lhs].second - ry) * (P[rhs].first - rx) > 1LL * (P[rhs].second - ry) * (P[lhs].first - rx));
}
 
bool right_compare(const int &lhs, const int &rhs) {
    return (1LL * (P[lhs].second - ry) * (P[rhs].first - rx) < 1LL * (P[rhs].second - ry) * (P[lhs].first - rx));
}
 
inline int LSB(const int value) {
    return (value & (-value));
}
 
inline int query(const int pos) {
    int ret = 0;
    for (int i = pos; i; i -= LSB(i)) ret += BIT[i];
    return ret;
}
 
inline void update(const int pos) {
    for (int i = pos; i < NMAX; i += LSB(i)) ++BIT[i];
}
 
inline void compute(const int pos, const vector<int> &p) {
    int i;
    memset(BIT, 0, sizeof(BIT));
 
    for(i = 1; i < (int)p.size(); ++i) {
        update(normalization[p[i - 1]]);
        res[pos][p[i]] = query(max(normalization[pos], normalization[p[i]])) - query(min(normalization[pos], normalization[p[i]]));
    }
}
 
inline void normalize() {
    int i;
 
    sort(X.begin() + 1, X.end());
    unique(X.begin() + 1, X.end());
    for(i = 1; i < (int)P.size(); ++i) normalization.push_back(lower_bound(X.begin(), X.end(), P[i].first) - X.begin());
 
    for(i = 1; i < (int)P.size(); ++i) {
        _left.clear(), _right.clear();
        split(i);
 
        rx = P[i].first, ry = P[i].second;
        sort(_left.begin(), _left.end(), left_compare);
        sort(_right.begin(), _right.end(), right_compare);
 
        compute(i, _left);
        compute(i, _right);
    }
}
 
int main() {
    int i, x, y, z;
 
    in >> N;
    for(i = 1; i <= N; ++i) {
        in >> x >> y;
        P.push_back(make_pair(x, y));
        X.push_back(x);
    }
 
    normalize();
 
    for(in >> M; M; --M) {
        in >> x >> y >> z;
 
        if(P[x].first > P[y].first) swap(x, y);
        if(P[x].first > P[z].first) swap(x, z);
        if(P[y].first > P[z].first) swap(y, z);
 
        rx = P[x].first, ry = P[x].second;
        if(right_compare(y, z)) out << res[x][z] - res[x][y] - res[y][z] - 1 << '\n';
        else out << res[x][y] + res[y][z] - res[x][z] << '\n';
    }
 
    in.close(), out.close();
    return 0;
}