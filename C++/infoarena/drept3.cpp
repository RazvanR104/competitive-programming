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

ifstream in("drept3.in");
ofstream out("drept3.out");

const int NMAX = 10010;

int N;
int current[NMAX];
struct Square {
    int x, y, d;
} S[NMAX];
vector<int> event_started[NMAX], event_finished[NMAX];

int main() {
    int i, j, resA = 0, resB = 0, limit = 0, k, last_area = 0;

    in >> N;
    for (i = 0; i < N; ++i) {
        in >> S[i].x >> S[i].y >> S[i].d;
        event_started[S[i].x].push_back(i);
        event_finished[S[i].x + S[i].d].push_back(i);
        limit = max(limit, S[i].x + S[i].d);
    }

    for (i = 0; i <= limit; ++i) {
        for (j = 0; j < (int)event_finished[i].size(); ++j)
            for (k = S[event_finished[i][j]].y; k < S[event_finished[i][j]].y + S[event_finished[i][j]].d; ++k) {
                --current[k];
                resB = max(resB, current[k]);

                if (current[k] == 0) --last_area;
            }

        for (j = 0; j < (int)event_started[i].size(); ++j)
            for (k = S[event_started[i][j]].y; k < S[event_started[i][j]].y + S[event_started[i][j]].d; ++k) {
                ++current[k];
                resB = max(resB, current[k]);

                if (current[k] == 1) ++last_area;
            }

        resA += last_area;
    }

    out << resA << '\n' << resB << '\n';
    in.close(), out.close();
    return 0;
}
