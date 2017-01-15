#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1010;

int N;
int V[NMAX];

int main() {
	ios_base::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
	assert(freopen("tdeque.in", "r", stdin) != NULL);
    assert(freopen("tdeque.out", "w", stdout) != NULL);
    assert(freopen("debug.err", "w", stderr) != NULL);
    #endif

    int i, j;
    deque<int> D;
    vector<int> answer;

    cin >> N;
    for (i = 1; i <= N; ++i)
        cin >> V[i];

    for (i = 1; i <= N; ++i) {
        int pos = -1;
        for (j = 0; j < int(D.size()); ++j) {
            if ((V[i] > D[j] && V[i] < D[(j + 1) % D.size()]) ||
                (V[i] > D[j] && D[j] > D[(j + 1) % D.size()]) ||
                (V[i] < D[(j + 1) % D.size()] && D[j] > D[(j + 1) % D.size()])) {
                pos = j;
                break;
            }
        }
        if (pos == -1) {
            answer.push_back(1);
            D.push_back(V[i]);
            continue;
        }

        int left = pos + 1, right = D.size() - pos - 1;
        if (left < right) {
            while (left--) {
                answer.push_back(3);
                D.push_back(D[0]);
                D.pop_front();
            }
        } else {
            while (right--) {
                answer.push_back(2);
                D.push_front(D.back());
                D.pop_back();
            }
        }

        answer.push_back(1);
        D.push_back(V[i]);
    }

    int pos = -1;
    for (i = 0; i < int(D.size() - 1); ++i) {
        if (D[i] > D[i + 1]) {
            pos = i;
            break;
        }
    }

    if (pos != -1) {
        int left = pos + 1, right = D.size() - pos - 1;
        if (left < right) {
            while (left--) {
                answer.push_back(3);
                D.push_back(D[0]);
                D.pop_front();
            }
        } else {
            while (right--) {
                answer.push_back(2);
                D.push_front(D.back());
                D.pop_back();
            }
        }
    }

    cout << answer.size() << '\n';
    for (const auto &it : answer)
        cout << it;
    cout << '\n';

	return 0;
}
