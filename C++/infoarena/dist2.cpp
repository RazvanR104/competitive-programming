#include <fstream>
#include <algorithm>

using namespace std;

typedef long long int64;

ifstream in("dist2.in");
ofstream out("dist2.out");

const int NMAX = 100010, LG2NMAX = 18, LMAX = 100;

int N;
int Max[LG2NMAX][NMAX], Min[LG2NMAX][NMAX];
char line[LMAX];
pair<int, int> Points[NMAX];

inline int Abs(int value) {
    if (value < 0) return -value;
    return value;
}

inline int lg2(int value) {
    int ret = -1;
    while (value) {
        ++ret;
        value >>= 1;
    }
    return ret;
}

#define pw2(x) (1 << (x))

int Search(int value) {
    int left = 1, right = N, mid, ret;
    for (mid = (left + right) >> 1; left <= right; mid = (left + right) >> 1) {
        if (value >= Points[mid].first) {
            ret = mid;
            left = mid + 1;
        } else right = mid - 1;
    }
    return ret;
}

bool TestValue(int value) {
    int i, pos, lgdist, MinY, MaxY;
    for (i = 1; i <= N; ++i) {
        pos = Search(Points[i].first + value) + 1;
        lgdist = lg2(N - pos + 1);
        if (lgdist != -1) {
            MinY = min(Min[lgdist][pos], Min[lgdist][N - pw2(lgdist) + 1]);
            MaxY = max(Max[lgdist][pos], Max[lgdist][N - pw2(lgdist) + 1]);
            if (Abs(Points[i].second - MinY) > value || Abs(Points[i].second - MaxY) > value) return false;
        }
    }
    return true;
}

int main() {
    int i, j, sign;

    in >> N;
    in.getline(line, LMAX);
    for (i = 1; i <= N; ++i) {
        in.getline(line, LMAX);
        j = 0;
        sign = 1;
        if (line[j] == '-') sign = -1, ++j;
        for ( ; line[j] != ' '; ++j) Points[i].first = Points[i].first * 10 + line[j] - '0';
        Points[i].first *= sign;

        sign = 1;
        if (line[++j] == '-') sign = -1, ++j;
        for ( ; line[j]; ++j) Points[i].second = Points[i].second * 10 + line[j] - '0';
        Points[i].second *= sign;
    }
    sort(Points + 1, Points + N + 1);

    for (i = 1; i <= N; ++i)
        Min[0][i] = Max[0][i] = Points[i].second;

    for (i = 1; pw2(i) <= N; ++i)
        for (j = 1; j + pw2(i) - 1 <= N; ++j) {
            Min[i][j] = min(Min[i - 1][j], Min[i - 1][j + pw2(i - 1)]);
            Max[i][j] = max(Max[i - 1][j], Max[i - 1][j + pw2(i - 1)]);
        }

    int left = 0, right = 2000000, mid, res = 0;
    for (mid = (left + right) >> 1; left <= right; mid = (left + right) >> 1) {
        if (TestValue(mid)) {
            res = mid;
            right = mid - 1;
        } else left = mid + 1;
    }

    out << res << '\n';
    in.close(), out.close();
    return 0;
}
