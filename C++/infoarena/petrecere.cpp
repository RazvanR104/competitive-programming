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

ifstream in("petrecere.in");
ofstream out("petrecere.out");

const int LMAX = 3010;

int N;
int A[LMAX], B[LMAX], C[LMAX], aux[LMAX];

void Add(int *A, int *B, int *C) {
    int i, t = 0;
    for (i = 1; i <= A[0] || i <= B[0] || t; ++i, t /= 10)
        C[i] = (t += (A[i] + B[i])) % 10;
    C[0] = i - 1;
}

void Multiply(int *A, int B, int *C) {
    int i, t = 0;
    for (i = 1; i <= A[0] || t; ++i, t /= 10)
        C[i] = (t += (A[i] * B)) % 10;
    C[0] = i - 1;
}

int main() {
    int i;

    in >> N;
    if (N == 1) {
        out << "1\n";
        return 0;
    } else if (N == 2) {
        out << "2\n";
        return 0;
    }

    A[0] = A[1] = B[0] = 1;
    B[1] = 2;

    for (i = 3; i <= N; ++i) {
        Multiply(A, i - 1, aux);
        Add(B, aux, C);

        memcpy(A, B, sizeof(A));
        memcpy(B, C, sizeof(B));
    }

    for (i = B[0]; i >= 1; --i)
        out << B[i];
    out << '\n';
    in.close(), out.close();
    return 0;
}
