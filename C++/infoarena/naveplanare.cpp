#include <bits/stdc++.h>

using namespace std;

const int NMAX = 210, inf = 0x3f3f3f3f, CMAX = 2020, offset = 1010;

int N, K;
int ln[NMAX], col[NMAX];

struct Edge {
    int from, to, cost, cap, flow;
    Edge *rev;

    Edge(int from, int to, int cost, int cap):
        from(from),
        to(to),
        cost(cost),
        cap(cap),
        flow(0),
        rev(0) {
    }
};

vector<Edge *> G[CMAX + NMAX + 10];

void NewEdge(int from, int to, int cost, int cap) {
    Edge *dir = new Edge(from, to, cost, cap);
    Edge *rev = new Edge(to, from, -cost, 0);
    dir->rev = rev;
    rev->rev = dir;

    G[from].push_back(dir);
    G[to].push_back(rev);
}

int dist[CMAX + NMAX + 10];
bool inq[CMAX + NMAX + 10];
Edge *from[CMAX + NMAX + 10];
bool BellmanFord(int S, int D) {
    queue<int> Q;
    Q.push(S);
    inq[S] = 1;
    memset(dist, inf, sizeof dist);
    dist[S] = 0;

    while (!Q.empty()) {
        int now = Q.front();
        Q.pop();
        inq[now] = 0;

        for (const auto &it: G[now]) {
            if (it->cap - it->flow == 0)
                continue;
            if (dist[it->to] > dist[now] + it->cost) {
                dist[it->to] = dist[now] + it->cost;
                from[it->to] = it;
                if (inq[it->to] == 0) {
                    inq[it->to] = 1;
                    Q.push(it->to);
                }
            }
        }
    }

    return dist[D] != inf;
}

int ComputeMaxFlowMinCost(int S, int D) {
    int answer = 0;
    while (BellmanFord(S, D)) {
        Edge *curr = from[D];
        int add = inf;
        while (curr != 0) {
            add = min(add, curr->cap - curr->flow);
            curr = from[curr->from];
        }

        curr = from[D];
        while (curr != 0) {
            curr->flow += add;
            curr->rev->flow -= add;
            curr = from[curr->from];
        }

        answer += add * dist[D];
    }

    return answer;
}

int Solve() {
    int S = 0, D = 1, preD = 2, i;
    for (i = 10; i <= CMAX; ++i) {
        NewEdge(i, preD, 0, 1);
        if (i > 10)
            NewEdge(i, i - 1, 1, inf);
        if (i < CMAX)
            NewEdge(i, i + 1, 1, inf);
    }
    NewEdge(preD, D, 0, K);

    for (i = 1; i <= N; ++i) {
        NewEdge(S, CMAX + i, 0, 1);
        NewEdge(CMAX + i, ln[i] + offset, 0, 1);
    }

    return ComputeMaxFlowMinCost(S, D);
}

int main() {
    assert(freopen("naveplanare.in", "r", stdin));
    assert(freopen("naveplanare.out", "w", stdout));

    int i;

    cin >> N >> K;
    for (i = 1; i <= N; ++i)
        cin >> ln[i] >> col[i];

    int answer = Solve();

    for (i = 1; i <= N; ++i)
        swap(ln[i], col[i]);

    for (i = 0; i < CMAX + NMAX + 10; ++i)
        G[i].clear();

    answer += Solve();

    cout << answer << '\n';
    return 0;
}
