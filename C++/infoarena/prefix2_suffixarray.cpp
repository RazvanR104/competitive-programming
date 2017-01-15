#include <bits/stdc++.h>

using namespace std;

typedef long long int64;

const int LMAX = 100010, LG2LMAX = 20, ALPHABET_SIZE = 60, RADIX_SIZE = 12, BITS = 24, RADIX = 0xfff;

int Suffix[LG2LMAX][LMAX], LG2, len, radix[1 << RADIX_SIZE], where[LMAX], current[LMAX];
int64 res[LMAX];
char str[LMAX];
set<int> Positions[ALPHABET_SIZE];

struct Event {
    int pos, pos1, pos2;
} E[LMAX];

inline int pw2(int value) {
    return (1 << value);
}

inline int lg2(int value) {
    int ret = -1;
    while (value) {
        ++ret;
        value >>= 1;
    }
    return ret;
}

inline int GetLCP(int i, int j) {
    int ret = 0;

    for (int k = LG2; k >= 0 && i <= len && j <= len; --k)
        if (Suffix[k][i] == Suffix[k][j]) {
            ret |= pw2(k);
            i += pw2(k);
            j += pw2(k);
        }

    return ret;
}

void RadixSort() {
    int i, j;

    for (i = 1; i <= len; ++i) where[i] = i;

    for (i = 0; i < BITS; i += RADIX_SIZE) {
        for (j = 1; j <= len; ++j)
            ++radix[(E[where[j]].pos2 >> i) & RADIX];

        for (j = 1; j < (1 << RADIX_SIZE); ++j)
            radix[j] += radix[j - 1];

        for (j = len; j >= 1; --j)
            current[radix[(E[where[j]].pos2 >> i) & RADIX]--] = where[j];

        memset(radix, 0, sizeof(radix));
        memcpy(where, current, sizeof(where));
    }

    for (i = 0; i < BITS; i += RADIX_SIZE) {
        for (j = 1; j <= len; ++j)
            ++radix[(E[where[j]].pos1 >> i) & RADIX];

        for (j = 1; j < (1 << RADIX_SIZE); ++j)
            radix[j] += radix[j - 1];

        for (j = len; j >= 1; --j)
            current[radix[(E[where[j]].pos1 >> i) & RADIX]--] = where[j];

        memset(radix, 0, sizeof(radix));
        memcpy(where, current, sizeof(where));
    }
}

int main() {
    ifstream in("prefix2.in");
    ofstream out("prefix2.out");

    int i, j;

    in.getline(str + 1, LMAX);
    len = strlen(str + 1);

    reverse(str + 1, str + len + 1);

    for (i = 1; i <= len; ++i)
        Suffix[0][i] = str[i] - 'A' + 1;

    for (i = 1; pw2(i - 1) <= len; ++i) {
        for (j = 1; j <= len; ++j) {
            E[j].pos1 = Suffix[i - 1][j];
            E[j].pos2 = Suffix[i - 1][j + pw2(i - 1)];
            E[j].pos = j;
        }
        RadixSort();

        for (j = 1; j <= len; ++j) {
            if (j && E[where[j]].pos1 == E[where[j - 1]].pos1 && E[where[j]].pos2 == E[where[j - 1]].pos2) Suffix[i][where[j]] = Suffix[i][where[j - 1]];
            else Suffix[i][where[j]] = j;
        }
    }
    LG2 = i - 1;

    res[len] = 1;
    Positions[str[len] - 'A'].insert(Suffix[LG2][len]);
    for (i = len - 1; i >= 1; --i) {
        res[i] = res[i + 1];
        int pos = Suffix[LG2][i];
        int LCP = 0;
        set<int>::iterator get = Positions[str[i] - 'A'].lower_bound(pos);
        if (get != Positions[str[i] - 'A'].end()) {
            LCP = max(LCP, GetLCP(i, E[*get].pos));
            if (Positions[str[i] - 'A'].size()) {
                --get;
                if (get != Positions[str[i] - 'A'].end())
                    LCP = max(LCP, GetLCP(i, E[*get].pos));
            }
        } else if (Positions[str[i] - 'A'].size()) {
            --get;
            if (get != Positions[str[i] - 'A'].end())
                LCP = max(LCP, GetLCP(i, E[*get].pos));
        }
        res[i] += len - i + 1 - LCP;
        Positions[str[i] - 'A'].insert(Suffix[LG2][i]);
    }

    for (i = len; i >= 1; --i)
        out << res[i] << '\n';

    in.close(), out.close();
    return 0;
}
