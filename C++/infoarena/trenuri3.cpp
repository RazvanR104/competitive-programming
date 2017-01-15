#include <bits/stdc++.h>

using namespace std;

const int NMAX = 100010;

int N, M;
int where[NMAX], currcap[NMAX];

struct Train {
    int stat, cap;
} T[NMAX];

struct Pass {
    int from, to;
} P[NMAX];

struct Event {
    int time, type, train, pass;
    Event(int time = 0, int type = 0, int train = 0, int pass = 0) : time(time), type(type), train(train), pass(pass) {}

    bool operator >(const Event &rhs) const {
        return time == rhs.time ? type < rhs.type : time > rhs.time;
    }
};
vector<Event> E;

int main() {
	ios_base::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
	assert(freopen("trenuri3.in", "r", stdin) != NULL);
    assert(freopen("trenuri3.out", "w", stdout) != NULL);
    assert(freopen("debug.err", "w", stderr) != NULL);
    #endif


    int i;

    assert(scanf("%d %d", &N, &M) == 2);
    for (i = 1; i <= N; ++i) {
        //cin >> T[i].stat >> T[i].cap;
        assert(scanf("%d %d", &T[i].stat, &T[i].cap) == 2);
        E.push_back(Event(T[i].stat, 0, i, 0));
    }

    for (i = 1; i <= M; ++i) {
        //cin >> P[i].from >> P[i].to;
        assert(scanf("%d %d", &P[i].from, &P[i].to) == 2);
        E.push_back(Event(P[i].from, 1, 0, i));
        E.push_back(Event(P[i].to, 2, 0, i));
    }

    sort(E.begin(), E.end(), greater<Event>());

    set<tuple<int, int, int>> ps;
    set<pair<int, int>, greater<pair<int, int>>> available;

    int capacity = 0;
    for (const auto &now : E) {
        if (now.type == 0) {
            capacity += T[now.train].cap;
            available.insert({T[now.train].cap, now.train});
            currcap[now.train] = T[now.train].cap;
        } else if (now.type == 1) {
            if (ps.count(make_tuple(P[now.pass].from, now.pass, where[now.pass])) == 0)
                continue;
            ps.erase(make_tuple(P[now.pass].from, now.pass, where[now.pass]));
            available.erase({currcap[where[now.pass]], where[now.pass]});
            ++currcap[where[now.pass]];
            available.insert({currcap[where[now.pass]], where[now.pass]});
        } else {
            if (int(ps.size()) < capacity) {
                int cap, tr;
                tie(cap, tr) = *available.begin();
                available.erase(available.begin());
                ps.insert(make_tuple(P[now.pass].from, now.pass, tr));
                where[now.pass] = tr;
                --currcap[tr];
                available.insert({currcap[tr], tr});
            } else if (capacity != 0) {
                int from, pass, tr;
                tie(from, pass, tr) = *ps.begin();
                if (P[now.pass].from <= from) continue;
                ps.erase(ps.begin());
                where[pass] = 0;
                ps.insert(make_tuple(P[now.pass].from, now.pass, tr));
                where[now.pass] = tr;
            }
        }
    }

    int answer = 0;
    for (i = 1; i <= M; ++i)
        answer += where[i] > 0;

    cout << answer << '\n';
    for (i = 1; i <= M; ++i)
        cout << where[i] << '\n';

	return 0;
}
