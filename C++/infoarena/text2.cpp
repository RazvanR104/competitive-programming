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

ifstream in("text.in");
ofstream out("text.out");

const int LMAX = 210, oo = 0x3f3f3f3f, MOD = 1000003;

int N;
int DP[LMAX][LMAX], M[LMAX][LMAX], from[LMAX][LMAX];
bool Vowel[LMAX][LMAX];
char str[LMAX];
vector<int> pos;

int main() {
    int i, j, k;

    in.getline(str, LMAX);
    int len = strlen(str);
    in >> N;

    for (i = 0; i < len; ++i) {
        for (j = i; j < len; ++j) {
            if (j > 0 && Vowel[i][j - 1] == true) Vowel[i][j] = true;
            if (Vowel[i][j] == false &&
                ((str[j] == 'a' || str[j] == 'e' || str[j] == 'i' || str[j] == 'o' || str[j] == 'u' || str[j] == 'y')))
                Vowel[i][j] = true;
        }
    }

    memset(DP, oo, sizeof(DP));
    for (i = 0; i < 20 && str[i]; ++i) {
        if (Vowel[0][i] == false) continue;
        DP[0][i] = (i + 1) * (i + 1);
        M[0][i] = 1;
    }

    for (i = 1; i < N; ++i) {
        for (j = i; str[j]; ++j) {
            for (k = j; k >= i && j - k + 1 <= 20; --k) {
                if (DP[i - 1][k - 1] == oo || Vowel[k][j] == false) continue;
                if (DP[i][j] >= DP[i - 1][k - 1] + (j - k + 1) * (j - k + 1)) {
                    DP[i][j] = DP[i - 1][k - 1] + (j - k + 1) * (j - k + 1);
                    from[i][j] = k - 1;
                }
                M[i][j] += M[i - 1][k - 1];
                if (M[i][j] >= MOD) M[i][j] -= MOD;
            }
        }
    }

    out << M[N - 1][len - 1] << '\n' << DP[N - 1][len - 1] << '\n';

    int fr = len - 1;
    for (i = N - 1; i > 0; --i) {
        fr = from[i][fr];
        pos.push_back(fr);
    }

    reverse(pos.begin(), pos.end());
    int _pos = 0;
    for (i = 0; i < len; ++i) {
        out << str[i];
        if (N > 1 && i == pos[_pos]) {
            out << ' ';
            ++_pos;
        }
    }
    out << '\n';
    in.close(), out.close();
    return 0;
}
