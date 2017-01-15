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

const int BUFFER_SIZE = 1 << 21;
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

InputReader in("mine.in");
ofstream out("mine.out");

const int NMAX = 10010, WMAX = 1000010, oo = 0x7fffffff, MMAX = 100010;

int N, M, Ws, hsize;
int W[WMAX];
bool visited[NMAX];
pair<int, int> H[MMAX];
vector<int> add;
vector<pair<int, int> > G[NMAX];

void downheap(int POS) {
    int son;
    do {
        son = 0;
        if (POS * 2 <= hsize) {
            son = POS * 2;
            if (POS * 2 + 1 <= hsize && H[POS * 2 + 1].second < H[POS * 2].second)
                son = POS * 2 + 1;
            if (H[POS].second <= H[son].second) son = 0;
        }

        if (son) {
            swap(H[POS], H[son]);
            POS = son;
        }
    }
    while(son);
}

void upheap(int POS) {
    while(POS > 1 && H[POS].second < H[POS / 2].second) {
        swap(H[POS], H[POS / 2]);
        POS /= 2;
    }
}

int main() {
    int i, j, x, y, w, extract, k;

    in >> N >> M;
    while(M--) {
        in >> x >> y >> w;
        G[x].push_back(make_pair(y, w));
        G[y].push_back(make_pair(x, w));
    }

    in >> Ws;
    for (i = 1; i <= Ws; ++i) in >> W[i];

    for (j = 0; j < (int)G[1].size(); ++j) {
        H[++hsize] = G[1][j];
        upheap(hsize);
    }

    visited[1] = true;
    for (i = 1; i <= Ws; ++i) {
        while(hsize && W[i] >= H[1].second) {
            extract = H[1].first;
            H[1] = H[hsize--];
            if (hsize) downheap(1);
            if (visited[extract]) continue;
            visited[extract] = true;
            add.push_back(extract);
            if (extract == N) {
                out << i << '\n';
                return 0;
            }
        }
        for (j = 0; j < (int)add.size(); ++j)
            for (k = 0; k < (int)G[add[j]].size(); ++k) {
                if (visited[G[add[j]][k].first]) continue;
                H[++hsize] = G[add[j]][k];
                upheap(hsize);
            }
        add.clear();
    }

    out << "-1\n";

    in.close(), out.close();
    return 0;
}
