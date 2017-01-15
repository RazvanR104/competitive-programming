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

ifstream in("xp.in");
ofstream out("xp.out");

int N, A1, B1, P, Q, res;

inline int Next_A(int A, int B) {
    return (((A + P - 1) ^ (B + 1)) % P);
}

inline int Next_B(int A, int B) {
    return (((A + P - 1) | (B + 1)) % P);
}

inline int Value(int A, int B, int i) {
    return max(1, ((i % P) ^ (((A + 1) & (B + 1)) % P)) % P);
}

void Compute(int left, int right, int A, int B, int product) {
    if (left == right) {
        res ^= product;
        return;
    }

    int mid = (left + right) / 2;
    int _A, _B, i, _product = ((int64)product * Value(A, B, left)) % Q;
    int cA = A, cB = B;

    for (i = left + 1; i <= mid; ++i) {
        _A = Next_A(A, B);
        _B = Next_B(A, B);
        _product = ((int64)_product * Value(_A, _B, i)) % Q;

        A = _A, B = _B;
    }

    _A = Next_A(A, B);
    _B = Next_B(A, B);
    A = _A, B = _B;

    Compute(mid + 1, right, A, B, _product);

    _product = ((int64)product * Value(A, B, mid + 1)) % Q;

    for (i = mid + 2; i <= right; ++i) {
        _A = Next_A(A, B);
        _B = Next_B(A, B);
        _product = ((int64)_product * Value(_A, _B, i)) % Q;

        A = _A, B = _B;
    }

    Compute(left, mid, cA, cB, _product);
}

int main() {
    in >> N >> A1 >> B1 >> P >> Q;

    Compute(1, N, A1, B1, 1);

    out << res << '\n';

    in.close(), out.close();
    return 0;
}
