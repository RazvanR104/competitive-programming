#include <bits/stdc++.h>

#define pb push_back

using namespace std;

const int NMAX = 1100, PMAX = 600, LMAX = 10, MAX = 250, inf = 0x3f3f3f3f, MOD = 666013, MLT = 33767;

int N, M, P;
int C[NMAX], T[PMAX][LMAX], curr[NMAX], DP[MAX][NMAX], sgn[NMAX];
bool locked[MAX][NMAX];
vector<int> G[NMAX];

struct Hash {
    int from, to, time, key;
    Hash() {}
    Hash(int _from, int _to, int _time) : from(_from), to(_to), time(_time) {
        key = ((1LL * from * MLT + to) * MLT + time) % MOD;
    }
    bool operator==(const Hash &rhs) const {
        return (from == rhs.from && to == rhs.to && time == rhs.time);
    }
};

vector<Hash> H[MOD];

bool Check(const Hash &curr) {
    int key = curr.key;
    for (const auto &it : H[key]) {
        if (it == curr)
            return true;
    }
    return false;
}

void Insert(const Hash &curr) {
    int key = curr.key;
    H[key].pb(curr);
}

struct State {
    int time, node, cost;
    State() {}
    State(int _time, int _node, int _cost) : time(_time), node(_node), cost(_cost) {}

    bool operator>(const State &rhs) const {
        return cost > rhs.cost;
    }
};

int GCD(int a, int b) {
    int r;
    while (b) {
        r = a % b;
        a = b;
        b = r;
    }
    return a;
}

int LCM(int a, int b) {
    int gcd = GCD(a, b);
    int res = a / gcd * b;
    return res;
}

int main() {
	ios_base::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
    freopen("patrol.in", "r", stdin);
    freopen("patrol.out", "w", stdout);
	freopen("debug.err", "w", stderr);
    #endif

    int i, j;

    cin >> N >> M >> P;
    for (i = 1; i <= N; ++i)
        cin >> C[i];

    while (M--) {
        int x, y;
        cin >> x >> y;
        G[x].pb(y);
        G[y].pb(x);
    }

    for (i = 1; i <= P; ++i) {
        cin >> T[i][0];

        for (j = 1; j <= T[i][0]; ++j) {
            cin >> T[i][j];
        }
    }

    int lcm = 2 * (T[1][0] - 1);
    for (i = 2; i <= P; ++i)
        lcm = LCM(lcm, 2 * (T[i][0] - 1));

    for (i = 1; i <= P; ++i) {
        curr[i] = 1;
        locked[0][T[i][1]] = 1;
        sgn[i] = 1;
    }

    for (i = 1; i < lcm; ++i) {
        for (j = 1; j <= P; ++j) {
            int from = T[j][curr[j]];
            if (curr[j] + sgn[j] >= 1 && curr[j] + sgn[j] <= T[j][0])
                curr[j] += sgn[j];
            else {
                sgn[j] *= -1;
                curr[j] += sgn[j];
            }
            int to = T[j][curr[j]];
            Insert(Hash(from, to, i));
            locked[i][T[j][curr[j]]] = 1;
        }
    }

    memset(DP, inf, sizeof(DP));
    DP[0][1] = C[1];

    priority_queue<State, vector<State>, greater<State>> Q;
    Q.push(State(0, 1, DP[0][1]));

    while (!Q.empty()) {
        State now = Q.top();
        Q.pop();

        if (now.node == N) {
            cout << now.cost << '\n';
            return 0;
        }

        int cnode = now.node, ctime = now.time, ccost = now.cost;
        for (const auto &it : G[cnode]) {
            int ntime = (ctime + 1) % lcm;
            if (locked[ntime][it]) continue;
            Hash chk = Hash(it, cnode, ntime);
            if (Check(chk)) continue;
            if (DP[ntime][it] > ccost + C[it]) {
                DP[ntime][it] = ccost + C[it];
                Q.push(State(ntime, it, DP[ntime][it]));
            }
        }
    }


	return 0;
}
