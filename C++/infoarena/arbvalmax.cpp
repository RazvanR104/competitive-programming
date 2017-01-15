#include <bits/stdc++.h>

using namespace std;

const int NMAX = 300010, HMAX = 100010, BUFFER_SIZE = 1 << 21;

int N, M, top;
int val[NMAX], S[HMAX], pos[NMAX], answer[NMAX], ST[4 * NMAX], LOL[HMAX];

vector<int> T[NMAX];
vector<pair<int, int>> Q[NMAX];

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

        inline InputReader & operator >> (char *str) {
            while(!isalpha(buffer[cursor]))
                advance();
            while(isalpha(buffer[cursor])) {
                *str = buffer[cursor];
                str++;
                advance();
            }
            *str = 0;
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

void Update(int node, int left, int right, int pos, int value) {
    if (left == right && left == pos) {
        ST[node] = value;
        return;
    }

    if (left >= right)
        return;

    int mid = (left + right) / 2;
    if (pos <= mid)
        Update(node * 2, left, mid, pos, value);
    else
        Update(node * 2 + 1, mid + 1, right, pos, value);

    ST[node] = max(ST[node * 2], ST[node * 2 + 1]);
}

int Query(int node, int left, int right, int qleft, int qright) {
    if (left >= qleft && right <= qright)
        return ST[node];

    if (left >= right)
        return 0;

    int ret = 0;
    int mid = (left + right) / 2;
    if (qleft <= mid)
        ret = max(ret, Query(node * 2, left, mid, qleft, qright));
    if (qright > mid)
        ret = max(ret, Query(node * 2 + 1, mid + 1, right, qleft, qright));

    return ret;
}

void DFS(int node) {
    S[++top] = node;
    pos[node] = top;
    LOL[top] = max(val[S[top - 1]], val[node]);
    //Update(ST, 1, 1, HMAX - 1, top, val[node]);
    //Max.erase(Max.find(val[node]));
    Update(1, 1, N, node, 0);

    for (const pair<int, int> &now : Q[node])
        answer[now.second] = max(ST[1], LOL[pos[now.first] - 1]);

    for (int next : T[node])
        DFS(next);

    --top;
    //Update(ST, 1, 1, HMAX - 1, top + 1, 0);
    Update(1, 1, N, node, val[node]);
    //Max.insert(val[node]);
}

int main() {
	ios_base::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
	assert(freopen("arbvalmax.in", "r", stdin) != NULL);
    assert(freopen("arbvalmax.out", "w", stdout) != NULL);
    assert(freopen("debug.err", "w", stderr) != NULL);
    #endif

    InputReader cin("arbvalmax.in");

    int i, j;

    cin >> N >> M;
    for (i = 2; i <= N; ++i) {
        cin >> j;
        T[j].push_back(i);
    }

    for (i = 1; i <= N; ++i) {
        cin >> val[i];
        //Max.insert(val[i]);
        Update(1, 1, N, i, val[i]);
    }

    int x, y;
    for (i = 1; i <= M; ++i) {
        cin >> x >> y;
        Q[y].push_back({x, i});
    }

    DFS(1);

    for (i = 1; i <= M; ++i)
        printf("%d\n", answer[i]);

	return 0;
}
