#include <fstream>
#include <cmath>

using namespace std;

typedef unsigned long long int64;

ifstream in("xp.in");
ofstream out("xp.out");

const int SQRTNMAX = 100010;

int N, A, B, P, K, Q, res, last_prod = 1, KG;
int val[SQRTNMAX], AA[SQRTNMAX], BB[SQRTNMAX], revprod[SQRTNMAX];

inline int Max(const int &value1, const int &value2) {
    if (value1 > value2) return value1;
    return value2;
}

#define Next_A(A, B) (((A + P - 1) ^ (B + 1)) % P)
#define Next_B(A, B) (((A + P - 1) | (B + 1)) % P)
#define Value(A, B, i) (Max(1, (((i) % P) ^ (((A + 1) & (B + 1)) % P)) % P))

void SolveInterval(int pos, int K) {
    int i;
    int64 values[SQRTNMAX], _revprod[SQRTNMAX];

    int A = AA[pos], B = BB[pos], _A, _B;
    values[0] = val[pos];
    for (i = 1; i < K; ++i) {
        _A = Next_A(A, B);
        _B = Next_B(A, B);
        values[i] = Value(_A, _B, pos * KG + i + 1);
        A = _A, B = _B;
    }

    _revprod[K] = revprod[pos + 1];
    for (i = K - 1; i >= 0; --i)
        _revprod[i] = ((int64)_revprod[i + 1] * values[i]) % Q;

    res ^= ((int64)last_prod * _revprod[1]) % Q;

    A = AA[pos], B = BB[pos];
    last_prod = ((int64)last_prod * Value(A, B, pos * KG + 1)) % Q;
    for (i = 1; i < K; ++i) {
        res ^= ((int64)last_prod * _revprod[i + 1]) % Q;
        _A = Next_A(A, B);
        _B = Next_B(A, B);
        last_prod = ((int64)last_prod * Value(_A, _B, pos * KG + i + 1)) % Q;
        A = _A, B = _B;
    }
}

int main() {
    int i, j, _A, _B, last;

    in >> N >> A >> B >> P >> Q;
    K = KG = N / 10000;
    //K = KG = sqrt(N);

    for (i = 1; i <= N; ++i) {
        if (i % K == 1) {
            val[i / K] = Value(A, B, i);
            AA[i / K] = A;
            BB[i / K] = B;
            last = i / K;
        }

        _A = Next_A(A, B);
        _B = Next_B(A, B);
        A = _A, B = _B;
    }

    revprod[last] = val[last];
    A = AA[last], B = BB[last];
    for (i = last * K + 2; i <= N; ++i) {
        _A = Next_A(A, B);
        _B = Next_B(A, B);
        A = _A, B = _B;
        revprod[last] = ((int64)revprod[last] * Value(A, B, i)) % Q;
    }

    int go = last - 1;

    for (i = go; i >= 0; --i) {
        int A = AA[i], B = BB[i], _A, _B;
        revprod[i] = val[i];
        for (j = i * K + 2; j <= (i + 1) * K; ++j) {
            _A = Next_A(A, B);
            _B = Next_B(A, B);
            A = _A, B = _B;
            revprod[i] = ((int64)revprod[i] * Value(A, B, j)) % Q;
        }
        revprod[i] = ((int64)revprod[i] * revprod[i + 1]) % Q;
    }

    for (i = 0; i < last; ++i)
        SolveInterval(i, K);

    revprod[last + 1] = 1;
    if (N % K == 0) SolveInterval(last, K);
    else SolveInterval(last, N % K);

    out << res << '\n';
    in.close(), out.close();
    return 0;
}
