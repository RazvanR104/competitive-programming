#include <fstream>
#include <cstring>

using namespace std;

typedef long long int64;

ifstream in("subsecvente.in");
ofstream out("subsecvente.out");

const int LMAX = 1000010, MULT = 127;

unsigned int hashN[LMAX], hashM[LMAX], pw[LMAX];
char N[LMAX], M[LMAX];

inline int max(const int &value, const int &_value) { return ((value > _value) ? (value) : (_value)); }
inline int min(const int &value, const int &_value) { return ((value < _value) ? (value) : (_value)); }

int main() {
    in.getline(N + 1, LMAX);
    in.getline(M + 1, LMAX);

    int i, j, Nlen = strlen(N + 1), Mlen = strlen(M + 1);

    for (i = 1; i <= Nlen || i <= Mlen; ++i) {
        hashN[i] = (hashN[i - 1] * MULT + N[i]);
        hashM[i] = (hashM[i - 1] * MULT + M[i]);
    }

    pw[0] = 1;
    for (j = 1; j < i; ++j)
        pw[j] = (pw[j - 1] * MULT);

    int start, finish, mid, _hashN, _hashM, last_mid;
    int64 res = 0;
    for (i = 1; i <= Nlen; ++i) {
        if (N[i] == '0') continue;
        start = i, finish = min(i + Mlen - 1, Nlen), last_mid = 0;

        for (mid = (start + finish) >> 1; start <= finish; mid = (start + finish) >> 1) {
            _hashN = (hashN[mid] - pw[mid - i + 1] * hashN[i - 1]);
            _hashM = hashM[mid - i + 1];

            if (_hashN == _hashM) {
                last_mid = mid;
                start = mid + 1;
            } else {
                finish = mid - 1;
            }
        }

        if (last_mid) {
            if (last_mid - i + 1 == Mlen) res += Mlen;
            else if (last_mid + 1 > Nlen || N[last_mid + 1] > M[last_mid - i + 2]) res += max(last_mid - i + 1, min(Nlen - i + 1, Mlen - 1));
            else if (N[last_mid + 1] < M[last_mid - i + 2]) res += min(Nlen - i + 1, Mlen);
        }
        else if (N[i] < M[1]) res += min(Nlen - i + 1, Mlen);
        else if (N[i] > M[1]) res += min(Nlen - i + 1, Mlen - 1);
    }

    out << res << '\n';

    in.close(), out.close();
    return 0;
}
