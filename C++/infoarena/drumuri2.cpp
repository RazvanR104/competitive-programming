#include <bits/stdc++.h>

using namespace std;

const int NMAX = 110, inf = 0x3f3f3f3f;

struct Edge {
    int from, to, cap, flow;
    Edge *rev;

    Edge(int from, int to, int cap):
        from(from),
        to(to),
        cap(cap),
        flow(0),
        rev(0) {
    }
};

const int S = 2 * NMAX + 1, D = 2 * NMAX + 2;
vector<Edge *> G[2 * NMAX + 10];

inline int in(int node) {
    return 2 * node - 1;
}

inline int out(int node) {
    return 2 * node;
}

Edge *father[2 * NMAX + 10];
bool vis[2 * NMAX + 10];
bool BFS(int S, int D) {
    memset(vis, 0, sizeof vis);
    memset(father, 0, sizeof father);

    queue<int> Q;
    Q.push(S);
    vis[S] = 1;

    while (!Q.empty()) {
        int now = Q.front();
        Q.pop();

        for (const auto &it: G[now]) {
            if (it->flow == it->cap || vis[it->to])
                continue;
            vis[it->to] = 1;
            Q.push(it->to);
            father[it->to] = it;
        }
    }

    return vis[D];
}

int MaxFlow(int S, int D) {
    int answer = 0;
    while (BFS(S, D)) {
        for (const auto &it: G[D]) {
            Edge *curr = it->rev;
            int flow = inf;
            while (curr) {
                flow = min(flow, curr->cap - curr->flow);
                curr = father[curr->from];
            }

            curr = it->rev;
            while (curr) {
                curr->flow += flow;
                curr->rev->flow -= flow;
                curr = father[curr->from];
            }
            answer += flow;
        }
    }
    return answer;
}

void AddEdge(int from, int to, int cap_dir, int cap_rev) {
    Edge *dir = new Edge(from, to, cap_dir);
    Edge *rev = new Edge(to, from, cap_rev);
    dir->rev = rev;
    rev->rev = dir;
    G[from].push_back(dir);
    G[to].push_back(rev);
}

int N, M;

int main() {
    assert(freopen("drumuri2.in", "r", stdin));
    assert(freopen("drumuri2.out", "w", stdout));

    int i, j;
    int x, y;

    cin >> N >> M;
    for (i = 1; i <= M; ++i) {
        cin >> x >> y;
        AddEdge(out(x), in(y), N, 0);
    }

    for (i = 1; i <= N; ++i) {
        AddEdge(in(i), out(i), N - 1, 0);
        AddEdge(S, in(i), N - 1, 1);
        AddEdge(out(i), D, N - 1, 1);
    }

    cout << N - MaxFlow(D, S) << '\n';

    return 0;
}
