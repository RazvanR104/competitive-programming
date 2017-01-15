#include <bits/stdc++.h>

using namespace std;

const int NMAX = 100010;

int N, M;
int DFN[NMAX], low[NMAX];
vector<int> G[NMAX];
stack<pair<int, int>> edges;
vector<vector<int>> Components;

void Save(int _first, int _second) {
    vector<int> C;
    int first, second;

    do {
        first = edges.top().first, second = edges.top().second;
        edges.pop();
        C.push_back(second);
        C.push_back(first);
    } while (_first != first || _second != second);

    sort(C.begin(), C.end());
    C.erase(unique(C.begin(), C.end()), C.end());
    Components.push_back(C);
}

void DFS(int node, int father, int dfn) {
    DFN[node] = low[node] = dfn;
    for (int i = 0; i < int(G[node].size()); ++i) {
        if (G[node][i] == father) continue;
        int troll = G[node][i];
        if (DFN[G[node][i]] == -1) {
            edges.push(make_pair(node, G[node][i]));
            DFS(G[node][i], node, dfn + 1);
            low[node] = min(low[node], low[G[node][i]]);
            if (low[G[node][i]] >= DFN[node])
                Save(node, G[node][i]);
        } else {
            low[node] = min(low[node], DFN[G[node][i]]);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
	ifstream in("biconex.in");
	ofstream out("biconex.out");

	int i, j, x, y;

	in >> N >> M;
	while (M--) {
        in >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x);
	}

	memset(DFN, -1, sizeof(DFN));
    DFS(1, 0, 0);

    out << Components.size() << '\n';
    for (i = 0; i < int(Components.size()); ++i) {
        for (j = 0; j < int(Components[i].size()); ++j)
            out << Components[i][j] << ' ';
        out << '\n';
    }

	in.close();
	out.close();
	return 0;
}
