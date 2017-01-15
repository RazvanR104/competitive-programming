#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1010, inf = 0x3f3f3f3f;

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

int N, M;
vector<Edge *> G[NMAX];
Edge *father[NMAX];
bool vis[NMAX];

void AddEdge(int from, int to, int cap) {
    Edge *dir = new Edge(from, to, cap);
    Edge *rev = new Edge(to, from, 0);

    dir->rev = rev;
    rev->rev = dir;

    G[from].push_back(dir);
    G[to].push_back(rev);
}

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
            if (it->cap - it->flow == 0)
                continue;
            if (vis[it->to])
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
            int add = inf;
            Edge *curr = it->rev;
            while (curr) {
                add = min(add, curr->cap - curr->flow);
                curr = father[curr->from];
            }

            curr = it->rev;
            while (curr) {
                curr->flow += add;
                curr->rev->flow -= add;
                curr = father[curr->from];
            }

            answer += add;
        }
    }

    return answer;
}

int main() {
    assert(freopen("maxflow.in", "r", stdin));
    assert(freopen("maxflow.out", "w", stdout));

    int i;
    int x, y, c;

    cin >> N >> M;
    for (i = 1; i <= M; ++i) {
        cin >> x >> y >> c;
        AddEdge(x, y, c);
    }

    cout << MaxFlow(1, N) << '\n';

    return 0;
}
