#include <fstream>
#include <cstdio>
#include <algorithm>

using namespace std;

ifstream in("pscpld2d.in");
ofstream out("pscpld2d.out");

const int NMAX = 1010, LG2NMAX = 10;

int N, i, j;
short p[2 * NMAX], p1[NMAX][NMAX], p2[NMAX][NMAX], aux[NMAX][NMAX], RMQ[NMAX][LG2NMAX][NMAX], CRMQ[LG2NMAX][NMAX];
char M[NMAX][NMAX], t[2 * NMAX];

void Manacher(short P[][NMAX]) {
    static int *ii = &i, *jj = &j;
    for (i = 1; i <= N; ++i) {
        int dim = 0;
        t[0] = '$';
        p[0] = 0;
        for (j = 1; j <= N; ++j) {
            t[++dim] = M[*ii][*jj];
            p[dim] = 1;
            t[++dim] = '$';
            p[dim] = 0;
        }

        if (ii == &j) reverse(t, t + dim + 1);

        int C = 0, R = 0;
        for (j = 1; j < dim; j++) {
            int mirror = 2 * C - j;

            if(j <= R)
                p[j] = min((int)p[mirror], R - j + 1);

            int l = j - p[j] + 1;
            int r = j + p[j] - 1;

            while(l - 2 >= 1 && r + 2 <= dim && t[l - 2] == t[r + 2]) {
                l -= 2;
                r += 2;
                p[j] += 2;
            }

            if(r > R) {
                R = r;
                C = j;
            }

            if (j % 2) P[i][++P[i][0]] = p[j];
        }
    }
    swap(ii, jj);
}

inline int lg2(int value) {
    int ret = -1;
    while(value) {
        ++ret;
        value >>= 1;
    }
    return ret;
}

inline int pw2(const int &value) {
    return (1 << value);
}

int main() {
    int i, j, k, res = 0;

    in >> N;
    in.getline(M[0], NMAX);
    for (i = 1; i <= N; ++i) in.getline(M[i] + 1, NMAX);

    Manacher(p1); Manacher(aux);

    for (i = 1; i <= N; ++i)
        for (j = 1; j <= N; ++j)
            p2[i][j] = aux[j][N - i + 1];

    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= N; ++j) RMQ[i][0][j] = p1[j][i];
        for (j = 1; pw2(j) <= N; ++j)
            for (k = 1; k + pw2(j) - 1 <= N; ++k)
                RMQ[i][j][k] = min(RMQ[i][j - 1][k], RMQ[i][j - 1][k + pw2(j - 1)]);
    }


    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= N; ++j) CRMQ[0][j] = p2[i][j];
        for (j = 1; pw2(j) <= N; ++j)
            for (k = 1; k + pw2(j) - 1 <= N; ++k)
                CRMQ[j][k] = min(CRMQ[j - 1][k], CRMQ[j - 1][k + pw2(j - 1)]);

        for (j = 1; j <= N; ++j) {
            ++res;
            int left = 1, right = (min(p1[i][j], p2[i][j]) - 1) / 2, mid, add = 0;
            for (mid = (left + right) / 2; left <= right; mid = (left + right) / 2) {
                int lgdist = lg2(mid * 2 + 1);
                int mmin = min(min(RMQ[j][lgdist][i - mid], RMQ[j][lgdist][i + mid - pw2(lgdist) + 1]),
                               min(CRMQ[lgdist][j - mid], CRMQ[lgdist][j + mid - pw2(lgdist) + 1]));

                if (mmin == mid * 2 + 1) {
                    add = mid;
                    break;
                }
                else if (mmin > mid * 2 + 1) {
                    add = mid;
                    left = mid + 1;
                }
                else right = mid - 1;
            }

            res += add;
        }
    }

    out << res << '\n';
    in.close(), out.close();
    return 0;
}
