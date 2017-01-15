#include <fstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

typedef unsigned int uint;
typedef vector<pair<uint, vector<int> > >::iterator _iterator;
typedef vector<int>::iterator __iterator;

ifstream in("partialmatch.in");
ofstream out("partialmatch.out");

const int NMAX = 100010, MOD = 100003, MULT = 29, MULT2 = 31;

int K, Alen, Blen, len;
uint HA[NMAX], HB[NMAX], pw[NMAX] = { 1 };
uint HAA[NMAX], HBB[NMAX], pww[NMAX] = { 1 };
bool tested[NMAX];
char A[NMAX], B[NMAX];
vector<pair<uint, vector<int> > > HT[MOD];
vector<int> result;

_iterator get_iterator(const uint &hash_key) {
    int pos = hash_key % MOD;

    for (_iterator it = HT[pos].begin(); it != HT[pos].end(); ++it)
        if (it->first == hash_key) return it;

    return HT[pos].end();
}

void insert_hash(const uint &hash_key, const int &pos) {
    _iterator it = get_iterator(hash_key);
    int ht_pos = hash_key % MOD;
    if (it == HT[ht_pos].end()) HT[ht_pos].push_back(make_pair(hash_key, vector<int>(1, pos)));
    else it->second.push_back(pos);
}

int verify(const int &A_pos, const int &B_pos) {
    int lr = A_pos - 1, rr = Alen - A_pos - len + 1;
    if (B_pos - lr < 1 || B_pos + len + rr - 1 > Blen) return -1;

    int mis = 0, i, j, left, right, mid;

    int Bl = B_pos - lr;

    for (i = 1, j = Bl; i <= Alen; ) {
        left = i, right = Alen;
        int pos = -1;
        for (mid = (left + right) >> 1; left <= right; mid = (left + right) >> 1) {
            if (HA[mid] - pw[mid - i + 1] * HA[i - 1] == HB[j + mid - i] - pw[mid - i + 1] * HB[j - 1] &&
                HAA[mid] - pww[mid - i + 1] * HAA[i - 1] == HBB[j + mid - i] - pww[mid - i + 1] * HBB[j - 1]) {
                left = mid + 1;
                pos = mid - i + 1;
            }
            else right = mid - 1;
        }

        if (pos == -1) {
            ++mis;
            ++i, ++j;
            if (mis > K) return -1;
        }
        else i += pos, j += pos;
    }

    return Bl - 1;
}

int main() {
    int i;

    in.getline(A + 1, NMAX);
    in.getline(B + 1, NMAX);
    in >> K;

    Alen = strlen(A + 1), Blen = strlen(B + 1);
    len = Alen / (K + 1);

    for (i = 1; i <= Alen; ++i) {
        HA[i] = HA[i - 1] * MULT + A[i] - 'a';
        HAA[i] = HAA[i - 1] * MULT2 + A[i] - 'a';
    }
    for (i = 1; i <= Blen; ++i) {
        HB[i] = HB[i - 1] * MULT + B[i] - 'a';
        HBB[i] = HBB[i - 1] * MULT2 + B[i] - 'a';
        pw[i] = pw[i - 1] * MULT;
        pww[i] = pww[i - 1] * MULT2;
        if (i >= len) insert_hash(HB[i] - pw[len] * HB[i - len], i - len + 1);
    }

    for (i = len; i <= Alen; i += len) {
        uint _hash = HA[i] - pw[len] * HA[i - len];
        int value;
        _iterator it = get_iterator(_hash);
        if (it != HT[_hash  % MOD].end())
            for (__iterator _it = it->second.begin(); _it != it->second.end(); ++_it)
                if (*_it - i + len - 1 >= 0 && !tested[*_it - i + len - 1]) {
                    tested[*_it - i + len - 1] = true;
                    if ((value = verify(i - len + 1, *_it)) != -1) result.push_back(value);
                }
    }

    sort(result.begin(), result.end());
    out << result.size() << '\n';
    for (i = 0; i < (int)result.size(); ++i) out << result[i] << '\n';

    in.close(), out.close();
    return 0;
}
