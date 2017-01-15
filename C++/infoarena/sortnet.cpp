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

ifstream in("sortnet.in");
ofstream out("sortnet.out");

const int NMAX = 21, MMAX = 33, LMAX = 1010;

int N, M;
int Comp[MMAX][NMAX], A[MMAX], B[MMAX];
char line[LMAX];

/*int Gray(int pos) {
    return (pos ^ (pos >> 1));
}

int Sorted(int arr) {
    return (arr & (arr + 1)) == 0;
}

int Test_Bit(const int &bin, const int &pos) {
    return (bin & (1 << pos)) > 0;
}*/

#define Test_Bit(bin, pos) ((bin & (1 << pos)) > 0)
#define Gray(pos) (pos ^ (pos >> 1))
#define Sorted(arr)  ((arr & (arr + 1)) == 0)

int lg2(int value) {
    int ret = -1;

    while(value) {
        ++ret;
        value /= 2;
    }

    return ret;
}

int Test(int n) {
    B[0] = n;
    int pos = lg2(A[0] ^ B[0]);

    for (int i = 0; i < M; ++i) {
        if ((Test_Bit(B[i], max(pos, Comp[i][pos])) && !Test_Bit(B[i], min(pos, Comp[i][pos]))) ||
            (Test_Bit(A[i], max(pos, Comp[i][pos])) && !Test_Bit(A[i], min(pos, Comp[i][pos])))) {
            pos = Comp[i][pos];
        }
        B[i + 1] = A[i + 1] ^ (1 << pos);
        A[i] = B[i];
    }
    A[M] = B[M];
    return Sorted(B[M]);
}

int main() {
    int i, j, a, b, pos, res = 1;

    in >> N >> M;
    in.getline(line, LMAX);
    for (i = 0; i < M; ++i) {
        in.getline(line, LMAX);
        pos = 0;
        for (j = 0; j < N / 2; ++j) {
            a = b = 0;
            for (++pos; line[pos] != ','; ++pos) a = a * 10 + line[pos] - '0';
            for (++pos; line[pos] != '>'; ++pos) b = b * 10 + line[pos] - '0';
            --a, --b;
            Comp[i][a] = b, Comp[i][b] = a;
            pos += 2;
        }
    }

    for (i = 1; i < (1 << N); ++i)
        res += Test(Gray(i));

    out << res << '\n';
    in.close(), out.close();
    return 0;
}
