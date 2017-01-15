#include <bits/stdc++.h>

using namespace std;

const int NMAX = 50010, MMAX = 150010, BUCKET = 20000, BUFFER_SIZE = 1 << 21;

struct Edge {
    int from, to, cost;
    bool type;
    bool operator<(const Edge &rhs) const {
        return cost < rhs.cost;
    }
} E[MMAX], old[NMAX], current[NMAX + BUCKET + 10];

int N, M, pos;
int disj1[NMAX], disj2[NMAX], father[NMAX], level[NMAX];
int comp[NMAX], comproot[BUCKET + 10], compfather[BUCKET + 10], compcost[BUCKET + 10];
bool vis[BUCKET + 10], used[MMAX + BUCKET + 10];
vector<int> T[NMAX];

int Root(int *disjoint, int node) {
    int _node = node;
    while (_node != disjoint[_node])
        _node = disjoint[_node];

    while (node != disjoint[node]) {
        int temp = disjoint[node];
        disjoint[node] = _node;
        node = temp;
    }

    return _node;
}

void Unite(int *disjoint, int node1, int node2) {
    disjoint[Root(disjoint, node1)] = Root(disjoint, node2);
}

inline int Next(int edge, int node) {
    return node == old[edge].from ? old[edge].to : old[edge].from;
}

void DFS(int node, int from, int curr_level) {
    level[node] = curr_level;
    for (const int &it: T[node]) {
        if (it == from)
            continue;
        int next = Next(it, node);
        father[next] = it;
        DFS(next, it, curr_level + 1);
    }
}

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

int main() {
    //assert(freopen("rutier.in", "r", stdin));
    //assert(freopen("rutier.out", "w", stdout));
    InputReader cin("rutier.in");
    ofstream cout("rutier.out");

    int i, j, node, cost;
    int64_t answer = 0;

    cin >> N;
    for (i = 2; i <= N; ++i) {
        cin >> node >> cost;
        old[++pos].from = i;
        old[pos].to = node;
        old[pos].cost = cost;
        old[pos].type = 1;

        T[node].push_back(pos);
        T[i].push_back(pos);

        answer += cost;
    }

    cin >> M;
    for (i = 1; i <= M; ++i)
        cin >> E[i].from >> E[i].to >> E[i].cost;

    father[1] = -1;
    DFS(1, -1, 0);

    for (i = 1; i <= M; i += BUCKET) {
        int right = min(M, i + BUCKET - 1);

        for (j = 1; j <= N; ++j)
            disj1[j] = disj2[j] = j;

        memcpy(current + 1, old + 1, (N - 1) * sizeof(Edge));
        memcpy(current + N, E + i, (right - i + 1) * sizeof(Edge));
        int length = N - 1 + right - i + 1;
        sort(current + 1, current + length + 1);

        for (j = 1; j <= length; ++j) {
            int from = current[j].from, to = current[j].to;

            if (Root(disj1, from) != Root(disj1, to)) {
                used[j] = 1;
                Unite(disj1, from, to);

                if (current[j].type == 1) {
                    if (level[Root(disj2, from)] > level[Root(disj2, to)])
                        Unite(disj2, from, to);
                    else
                        Unite(disj2, to, from);
                }
            }
        }

        int curr_comp = 0;
        for (j = 1; j <= N; ++j) {
            if (disj2[j] == j) {
                comp[j] = ++curr_comp;
                comproot[curr_comp] = j;
            }
        }

        for (j = 1; j <= curr_comp; ++j) {
            int father_edge = father[comproot[j]];
            if (father_edge == -1) {
                compfather[j] = -1;
                compcost[j] = -1;
            } else {
                int nextnode = Next(father_edge, comproot[j]);
                int nextroot = Root(disj2, nextnode);
                compfather[j] = comp[nextroot];
                compcost[j] = old[father_edge].cost;
            }
        }

        for (j = i; j <= right; ++j) {
            int from = E[j].from, to = E[j].to;

            memset(vis, 0, sizeof vis);

            from = comp[Root(disj2, from)];
            while (from != -1) {
                vis[from] = 1;
                from = compfather[from];
            }

            int lca = comp[Root(disj2, to)];
            while (vis[lca] == 0)
                lca = compfather[lca];

            int costmax = -1, where = -1;

            from = comp[Root(disj2, E[j].from)];
            to = comp[Root(disj2, E[j].to)];

            bool reversed = 0;

            while (from != lca) {
                if (costmax < compcost[from]) {
                    costmax = compcost[from];
                    where = from;
                }
                from = compfather[from];
            }

            while (to != lca) {
                if (costmax < compcost[to]) {
                    costmax = compcost[to];
                    where = to;
                    reversed = 1;
                }
                to = compfather[to];
            }

            if (costmax > E[j].cost) {
                from = comp[Root(disj2, E[j].from)];
                to = comp[Root(disj2, E[j].to)];
                if (reversed)
                    swap(from, to);

                int cost = E[j].cost;
                while (from != where) {
                    int next = compfather[from];
                    int nextcost = compcost[from];
                    compfather[from] = to;
                    compcost[from] = cost;
                    to = from;
                    from = next;
                    cost = nextcost;
                }

                if (from == where) {
                    compfather[from] = to;
                    compcost[from] = cost;
                }

                answer += E[j].cost - costmax;
            }

            cout << answer << '\n';
        }

        for (j = 1; j <= N; ++j)
            T[j].clear();

        pos = 0;
        for (j = 1; j <= length; ++j)
            if (used[j]) {
                old[++pos] = current[j];
                old[pos].type = 1;
                T[old[pos].from].push_back(pos);
                T[old[pos].to].push_back(pos);
            }
        memset(used, 0, sizeof used);

        DFS(1, -1, 0);
    }

    return 0;
}
