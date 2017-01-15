#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

const int BUFFER_SIZE = 1 << 10;

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

InputReader in("zoo.in");
ofstream out("zoo.out");

const int NMAX = 16010;

int N, M;
vector<int> tree[4 * NMAX];
pair<int, int> P[NMAX];

void build_tree(const int node, const int left, const int right) {
    tree[node].resize(right - left + 1);
    if (left == right) {
        tree[node][0] = P[left].second;
        return;
    }

    int mid = (left + right) >> 1;
    build_tree(node * 2, left, mid);
    build_tree(node * 2 + 1, mid + 1, right);

    merge(tree[node * 2].begin(), tree[node * 2].end(), tree[node * 2 + 1].begin(), tree[node * 2 + 1].end(), tree[node].begin());
}

int query(const int node, const int left, const int right, const int x1, const int y1, const int x2, const int y2) {
    int ret = 0;

    if (x1 <= P[left].first && x2 >= P[right].first)
        return (upper_bound(tree[node].begin(), tree[node].end(), y2) - lower_bound(tree[node].begin(), tree[node].end(), y1));

    if (left == right) return 0;

    int mid = (left + right) >> 1;
    if (x1 <= P[mid].first) ret += query(node * 2, left, mid, x1, y1, x2, y2);
    if (x2 >= P[mid + 1].first) ret += query(node * 2 + 1, mid + 1, right, x1, y1, x2, y2);

    return ret;
}

int main() {
    int x1, x2, y1, y2, i;

    in >> N;
    for (i = 1; i <= N; ++i) in >> P[i].first >> P[i].second;
    sort(P + 1, P + N + 1);

    build_tree(1, 1, N);

    for (in >> M; M; --M) {
        in >> x1 >> y1 >> x2 >> y2;
        out << query(1, 1, N, x1, y1, x2, y2) << '\n';
    }

    return 0;
}
