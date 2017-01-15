#include <bits/stdc++.h>

using namespace std;

const int NMAX = 110;

int N, M;
int values[NMAX][2];

int main() {
    assert(freopen("numar2.in", "r", stdin));
    assert(freopen("numar2.out", "w", stdout));

    int i, j;
    priority_queue<pair<int, int>> PQ;

    cin >> N >> M;
    for (i = 1; i <= N; ++i) {
        cin >> values[i][0];
        values[i][1] = 2;
        PQ.push({-values[i][0], i});
    }

    int answer = -1;

    while (M && !PQ.empty()) {
        while (!PQ.empty()) {
            auto it = PQ.top();
            PQ.pop();
            PQ.push({-(values[it.second][0] * (values[it.second][1]++)), it.second});

            if (-it.first != answer) {
                answer = -it.first;
                break;
            }
        }
        --M;
    }

    cout << answer << '\n';
    return 0;
}
