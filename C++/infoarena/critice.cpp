#include <bits/stdc++.h>

using namespace std;

const int MMAX = 10010, NMAX = 1010, inf = 0x3f3f3f3f;

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
Edge *E[MMAX];

void AddEdge(int from, int to, int cap, int pos) {
    Edge *dir = new Edge(from, to, cap);
    Edge *rev = new Edge(to, from, cap);
    dir->rev = rev;
    rev->rev = dir;
    G[from].push_back(dir);
    G[to].push_back(rev);
    E[pos] = dir;
}

Edge *father[NMAX];
bool vis[NMAX];
bool BFS(int S, int D) {
    memset(vis, 0, sizeof vis);

    queue<int> Q;
    Q.push(S);
    vis[S] = 1;

    while (!Q.empty()) {
        int now = Q.front();
        Q.pop();

        for (const auto &it: G[now]) {
            if (it->flow >= 0 && it->flow == it->cap)
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

void MaxFlow(int S, int D) {
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
        }
    }
}

bool source[NMAX], sink[NMAX];
void BFS(int S, bool vis[]) {
    vis[S] = 1;
    queue<int> Q;
    Q.push(S);

    while (!Q.empty()) {
        int now = Q.front();
        Q.pop();

        for (const auto &it: G[now]) {
            if (it->cap == it->flow || it->rev->cap == it->rev->flow)
                continue;
            if (vis[it->to])
                continue;
            vis[it->to] = 1;
            Q.push(it->to);
        }
    }
}

int main() {
    assert(freopen("critice.in", "r", stdin));
    assert(freopen("critice.out", "w", stdout));

    int i, j;
    int x, y, cap;

    cin >> N >> M;
    for (i = 1; i <= M; ++i) {
        cin >> x >> y >> cap;
        AddEdge(x, y, cap, i);
    }

    MaxFlow(1, N);

    vector<int> answer;

    BFS(1, source);
    BFS(N, sink);

    for (i = 1; i <= M; ++i)
        if ((source[E[i]->from] && sink[E[i]->to]) ||
            (source[E[i]->to] && sink[E[i]->from]))
            answer.push_back(i);

    cout << answer.size() << '\n';
    for (const int &it: answer)
        cout << it << '\n';

    return 0;
}
