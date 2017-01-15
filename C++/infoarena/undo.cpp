#include <bits/stdc++.h>

using namespace std;

const int NMAX = 530, MMAX = 500010;

int N, M;
int BIT[NMAX][NMAX];
int states[MMAX], answer[MMAX];
vector<tuple<int, int, int, int>> G[MMAX];
vector<tuple<int, int, int>> Query[MMAX];

const int BUFFER_SIZE = 1 << 20;
class Reader {
    public:
        Reader() {}
        Reader(const char* filename) {
            file = fopen(filename, "r");
            cursor = 0;
            fread(buffer, BUFFER_SIZE, 1, file);
        }
        inline Reader & operator >> (int &n) {
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

void UpdateBIT(int x, int y, int value) {
    for ( ; x <= N; x += x & -x)
        for (int cy = y; cy <= N; cy += cy & -cy)
            BIT[x][cy] += value;
}

int QueryBIT(int x, int y) {
    int ret = 0;
    for ( ; x; x -= x & -x)
        for (int cy = y; cy; cy -= cy & -cy)
            ret += BIT[x][cy];
    return ret;
}

void DFS(int node) {
    for (const auto &it: Query[node]) {
        int x, y, pos;
        tie(x, y, pos) = it;
        answer[pos] = QueryBIT(x, y);
    }

    for (const auto &it: G[node]) {
        int next, x, y, z;
        tie(next, x, y, z) = it;
        UpdateBIT(x, y, z);
        DFS(next);
        UpdateBIT(x, y, -z);
    }
}

int main() {
    Reader cin("undo.in");
    assert(freopen("undo.out", "w", stdout));

    int i, j;
    int type, x, y, z, query = 0;
    int node = 0, spos = 0;

    states[++spos] = ++node;
    cin >> N >> M;
    for (i = 1; i <= M; ++i) {
        cin >> type;
        if (type == 1) {
            cin >> x >> y >> z;
            states[++spos] = ++node;
            G[states[spos - 1]].push_back(make_tuple(node, x, y, z));
        } else if (type == 2) {
            cin >> x >> y;
            Query[states[spos]].push_back(make_tuple(x, y, ++query));
        } else {
            cin >> x;
            states[spos + 1] = states[spos - x];
            ++spos;
        }
    }

    DFS(1);

    for (i = 1; i <= query; ++i)
        cout << answer[i] << '\n';
    return 0;
}
