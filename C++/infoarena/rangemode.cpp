#include <iostream>
#include <iomanip>
#include <fstream>

#include <algorithm>
#include <bitset>
#include <deque>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <utility>
#include <vector>

#if __cplusplus > 199711L
#include <unordered_map>
#include <unordered_set>
#endif

#include <cstdio>
#include <ctime>
#include <cmath>
#include <cstring>
#include <cstdlib>

using namespace std;

typedef long long int64;

ifstream in("rangemode.in");
ofstream out("rangemode.out");

const int NMAX = 100010, SQRTNMAX = 320;

int N, M, K;
int V[NMAX], Mode[SQRTNMAX][SQRTNMAX][2], VV[NMAX], pos[NMAX];
vector<int> Where[NMAX];

int main() {
    int i, j, k, lt, rt;

    in >> N >> M;
    K = sqrt(N);

    for (i = 1; i <= N; ++i) {
        in >> V[i];
        Where[V[i]].push_back(i);
        pos[i] = Where[V[i]].size() - 1;
    }

    for (i = 0; i < N / K; ++i) {
        int mode, freq = 0;
        for (j = i; j < N / K; ++j) {
            for (k = j * K + 1; k <= (j + 1) * K; ++k) {
                ++VV[V[k]];
                if (VV[V[k]] == freq && V[k] < mode) mode = V[k];
                else if (VV[V[k]] > freq) {
                    mode = V[k];
                    freq = VV[V[k]];
                }
            }
            Mode[i][j][0] = mode;
            Mode[i][j][1] = freq;
        }
        memset(VV, 0, sizeof(VV));
    }

    while (M--) {
        in >> lt >> rt;
        int leftpos = (lt - 1) / K + 1;
        int rightpos = (rt - 1) / K - 1;

        if (lt % K == 1) --leftpos;
        if (rt % K == 0) ++rightpos;

        int mode, freq = 0, new_freq;

        if (leftpos > rightpos) {
            for (i = lt; i <= rt; ++i) {
                if (freq && (pos[i] + freq - 1 >= Where[V[i]].size() || Where[V[i]][pos[i] + freq - 1] > rt)) continue;
                new_freq = upper_bound(Where[V[i]].begin(), Where[V[i]].end(), rt) - lower_bound(Where[V[i]].begin(), Where[V[i]].end(), lt);
                if (new_freq == freq && V[i] < mode) mode = V[i];
                else if (new_freq > freq) {
                    mode = V[i];
                    freq = new_freq;
                }
            }
            out << mode << '\n';
        } else {
            mode = Mode[leftpos][rightpos][0];
            freq = Mode[leftpos][rightpos][1];

            for (i = lt; i <= leftpos * K; ++i) {
                if (freq && (pos[i] + freq - 1 >= Where[V[i]].size() || Where[V[i]][pos[i] + freq - 1] > rt)) continue;
                new_freq = upper_bound(Where[V[i]].begin(), Where[V[i]].end(), rt) - lower_bound(Where[V[i]].begin(), Where[V[i]].end(), lt);
                if (new_freq == freq && V[i] < mode) mode = V[i];
                else if (new_freq > freq) {
                    mode = V[i];
                    freq = new_freq;
                }
            }

            for (i = (rightpos + 1) * K + 1; i <= rt; ++i) {
                if (freq && (pos[i] - freq + 1 < 0 || Where[V[i]][pos[i] - freq + 1] < lt)) continue;
                new_freq = upper_bound(Where[V[i]].begin(), Where[V[i]].end(), rt) - lower_bound(Where[V[i]].begin(), Where[V[i]].end(), lt);
                if (new_freq == freq && V[i] < mode) mode = V[i];
                else if (new_freq > freq) {
                    mode = V[i];
                    freq = new_freq;
                }
            }

            out << mode << '\n';
        }
    }

    in.close(), out.close();
    return 0;
}
