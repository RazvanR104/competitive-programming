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

const int LMAX = 16, ASIZE = 26;

int P, N;
int num[ASIZE];
vector<int> Words;
char ALPHABET[LMAX], word[LMAX], rev[ASIZE];

int main() {
    freopen("zimeria.in", "r", stdin);
    freopen("zimeria.out", "w", stdout);

    int i, j;
    int wordnum;

    scanf("%d %d\n", &P, &N);
    gets(ALPHABET + 1);

    for (i = 1; ALPHABET[i]; ++i) {
        num[ALPHABET[i] - 'a'] = i;
        rev[i] = ALPHABET[i];
    }

    for (i = 1; i <= N; ++i) {
        gets(word + 1);

        wordnum = 0;
        for (j = 1; j <= 5; ++j) {
            if (num[word[j] - 'a'] / 10)
                wordnum = (wordnum * 10 + num[word[j] - 'a'] / 10) * 10 + num[word[j] - 'a'] % 10;
            else wordnum = wordnum * 100 + num[word[j] - 'a'];
        }

        Words.push_back(wordnum);
    }

    sort(Words.begin(), Words.end());
    if (P == 1) {
        int res = 1;
        for (i = 1; i < (int)Words.size(); ++i)
            if (Words[i] != Words[i - 1])
                ++res;
        printf("%d\n", res);
    } else {
        for (i = 0; i < (int)Words.size(); ++i) {
            int pos = 5, nr = Words[i];
            while (pos) {
                word[pos--] = rev[nr / 10 % 10 * 10 + nr % 10];
                nr /= 100;
            }
            puts(word + 1);
        }
    }

    return 0;
}
