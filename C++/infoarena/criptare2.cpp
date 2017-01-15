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

ifstream in("criptare2.in");
ofstream out("criptare2.out");

const int ALPHABET_SIZE = 26, NMAX = 20010, MOD = 666013, MULT = ALPHABET_SIZE + 10;

struct HASH {
    char word[ALPHABET_SIZE];
} H;

int N, M, _hash;
char coresp[ALPHABET_SIZE];
vector<HASH> HT[MOD];

bool doesnt_exist() {
    for(vector<HASH>::iterator it = HT[_hash].begin(); it != HT[_hash].end(); ++it)
        if(memcmp(it->word, H.word, ALPHABET_SIZE) == 0)
            return false;
    return true;
}

void insert_hash() {
    HT[_hash].push_back(H);
}

int main() {
    int i, current;

    for(in >> N; N; --N) {
        in >> H.word;
        current = 1;

        for(i = 0; H.word[i]; ++i) {
            if(coresp[H.word[i] - 'a'] == 0) {
                coresp[H.word[i] - 'a'] = current;
                H.word[i] = current++;
            }
            else H.word[i] = coresp[H.word[i] - 'a'];
        }
        H.word[i] = -1;

        _hash = 0;
        for(i = 0; H.word[i] != -1; ++i)
            _hash = (_hash * MULT + H.word[i]) % MOD;

        if(doesnt_exist()) insert_hash();

        memset(H.word, 0, ALPHABET_SIZE);
        memset(coresp, 0, ALPHABET_SIZE);
    }

    for(in >> M; M; --M) {
        in >> H.word;
        current = 1;

        for(i = 0; H.word[i]; ++i) {
            if(coresp[H.word[i] - 'a'] == 0) {
                coresp[H.word[i] - 'a'] = current;
                H.word[i] = current++;
            }
            else H.word[i] = coresp[H.word[i] - 'a'];
        }
        H.word[i] = -1;

        _hash = 0;
        for(i = 0; H.word[i] != -1; ++i)
            _hash = (_hash * MULT + H.word[i]) % MOD;

        if(doesnt_exist()) out << "0\n";
        else out << "1\n";

        memset(H.word, 0, ALPHABET_SIZE);
        memset(coresp, 0, ALPHABET_SIZE);
    }

    in.close(), out.close();
    return 0;
}
