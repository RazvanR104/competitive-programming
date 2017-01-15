#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> Point;

const int NMAX = 100010, oo = 0x3f3f3f3f, MOD = 666013, MULT = 1000000009;

int T, N;
int nxt[NMAX], prv[NMAX];
Point P[NMAX], PX[NMAX], PY[NMAX];
vector<int> Tree[4 * NMAX];

/*struct Hash {
    int x, y, pos;
    Hash() {}
    Hash(int x, int y, int pos) {
        this->x = x;
        this->y = y;
        this->pos = pos;
    }
};

vector<Hash> H[MOD];

int GetPosition(const Point &P) {
    int key = (1LL * P.first * MULT + P.second) % MOD;

    for (int i = 0; i < (int)H[key].size(); ++i)
        if (H[key][i].x == P.first && H[key][i].y == P.second)
            return H[key][i].pos;

    return -1;
}

void InsertHash(const Point &P, int pos) {
    int key = (1LL * P.first * MULT + P.second) % MOD;
    H[key].push_back(Hash(P.first, P.second, pos));
}*/

struct Compare {
    bool operator()(const Point &lhs, const Point &rhs) const {
        if (lhs.second < rhs.second) return true;
        if (lhs.second > rhs.second) return false;
        if (lhs.first < rhs.first) return true;
        return false;
    }
};

void BuildTree(int node, int left, int right) {
    Tree[node].clear();

    if (left == right)
        return Tree[node].push_back(PX[left].second);

    if (left > right) return;

    int mid = (left + right) / 2;
    BuildTree(node * 2, left, mid);
    BuildTree(node * 2 + 1, mid + 1, right);

    Tree[node].resize(right - left + 1);
    merge(Tree[node * 2].begin(), Tree[node * 2].end(),
          Tree[node * 2 + 1].begin(), Tree[node * 2 + 1].end(),
          Tree[node].begin());
}

int QueryTree(int node, int left, int right, int left_x, int right_x, int left_y, int right_y) {
    if (PX[left].first >= left_x && PX[right].first <= right_x)
        return upper_bound(Tree[node].begin(), Tree[node].end(), right_y) - lower_bound(Tree[node].begin(), Tree[node].end(), left_y);

    if (left == right) return 0;

    int mid = (left + right) / 2, ret = 0;
    if (left_x <= PX[mid].first)
        ret += QueryTree(node * 2, left, mid, left_x, right_x, left_y, right_y);
    if (right_x >= PX[mid + 1].first)
        ret += QueryTree(node * 2 + 1, mid + 1, right, left_x, right_x, left_y, right_y);

    return ret;
}

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

int GetPosition(const Point &P) {
    return lower_bound(PX + 1, PX + N + 1, P) - PX;
}

int main() {
	InputReader in("arbsat.in");
	ofstream out("arbsat.out");

	int i;

    for (in >> T; T; --T) {
        memset(nxt, 0, sizeof(nxt));
        memset(prv, 0, sizeof(prv));

        in >> N;

        for (i = 1; i <= N; ++i) {
            in >> P[i].first >> P[i].second;
            PX[i] = PY[i] = P[i];
        }

        sort(PX + 1, PX + N + 1);
        sort(PY + 1, PY + N + 1, Compare());

        BuildTree(1, 1, N);

        //for (i = 1; i <= N; ++i)
          //  InsertHash(PX[i], i);

        if (PY[1].second == PY[2].second)
            nxt[GetPosition(PY[1])] = 2;
        for (i = 2; i < N; ++i) {
            int pos = GetPosition(PY[i]);
            if (PY[i].second == PY[i - 1].second)
                prv[pos] = i - 1;
            if (PY[i].second == PY[i + 1].second)
                nxt[pos] = i + 1;
        }
        if (PY[N].second == PY[N - 1].second)
            prv[GetPosition(PY[N])] = N - 1;

        for (i = 1; i <= N; ++i) {
            Point up, down, left, right;

            if (PX[i].first == PX[i + 1].first)
                up = PX[i + 1];
            else
                up = make_pair(PX[i].first, oo);

            if (nxt[i])
                right = PY[nxt[i]];
            else
                right = make_pair(oo, PX[i].second);

            if (i > 1 && PX[i].first == PX[i - 1].first)
                down = PX[i - 1];
            else
                down = make_pair(PX[i].first, 0);

            if (prv[i])
                left = PY[prv[i]];
            else
                left = make_pair(0, PX[i].second);

            if (QueryTree(1, 1, N, min(up.first, right.first) + 1, max(up.first, right.first) - 1, min(up.second, right.second) + 1, max(up.second, right.second) - 1) != 0) break;
            if (QueryTree(1, 1, N, min(down.first, right.first) + 1, max(down.first, right.first) - 1, min(down.second, right.second) + 1, max(down.second, right.second) - 1) != 0) break;
//            if (QueryTree(1, 1, N, min(up.first, left.first) + 1, max(up.first, left.first) - 1, min(up.second, left.second) + 1, max(up.second, left.second) - 1) != 0) break;
//            if (QueryTree(1, 1, N, min(down.first, left.first) + 1, max(down.first, left.first) - 1, min(down.second, left.second) + 1, max(down.second, left.second) - 1) != 0) break;
        }

        if (i <= N) out << "0\n";
        else out << "1\n";
    }

	in.close();
	out.close();
	return 0;
}
