#include <fstream>
#include <cstring>

using namespace std;

ifstream in("expozitie.in");
ofstream out("expozitie.out");

const int NMAX = 510, DIGITS = 210;

int N, D, K;
int DP[2][NMAX][DIGITS], Sum[DIGITS];

void Add(int *A, int *B) {
    int i, t = 0;
    for (i = 1; i <= A[0] || i <= B[0] || t; ++i, t /= 10) {
        if (i <= A[0]) t += A[i];
        if (i <= B[0]) t += B[i];
        A[i] = t % 10;
    }
    A[0] = i - 1;
}

int main() {
    int i, j, r;

    in >> N >> D >> K;
    r = N - D * K;

    if (N - D * K < 0) {
        out << "0\n";
        return 0;
    }

    for (i = 0; i <= r; ++i)
        DP[0][i][0] = DP[0][i][1] = 1;

    for (i = 1; i < D; ++i) {
        Sum[0] = 0;
        for (j = 0; j <= r; ++j) {
            Add(Sum, DP[!(i & 1)][j]);
            memcpy(DP[i & 1][j], Sum, sizeof(DP[i & 1][j]));
        }
        for (j = 0; j <= r; ++j) DP[!(i & 1)][j][0] = 0;
    }

    for (i = DP[!(D & 1)][r][0]; i >= 1; --i) out << DP[!(D & 1)][r][i];
    out << '\n';

    in.close(), out.close();
}
