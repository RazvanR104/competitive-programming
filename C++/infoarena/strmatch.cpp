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

const int LMAX = 2000010, MOD1 = 666013, MOD2 = 666019, M = 123;

int matches;
int hashA1, hashA2, hashB1, hashB2, M1 = 1, M2 = 1;
char A[LMAX], B[LMAX], in_file[2 * LMAX];
bool match[LMAX];

int main() {
    freopen("strmatch.in", "r", stdin);
    freopen("strmatch.out", "w", stdout);

    int i, j;

    fread(in_file, sizeof(char), 2 * LMAX, stdin);
    for(i = 0; in_file[i] != '\n'; ++i)
        A[i] = in_file[i];
    for(j = ++i; in_file[j] != '\n'; ++j)
        B[j - i] = in_file[j];

    //gets(A);
    //gets(B);

    for(i = 0; A[i]; ++i) {
        hashA1 = (hashA1 * M + A[i]) % MOD1;
        hashA2 = (hashA2 * M + A[i]) % MOD2;

        if (i > 0) {
            M1 = (M * M1) % MOD1;
            M2 = (M * M2) % MOD2;
        }
    }

    for(i = 0; A[i]; ++i) {
        if (B[i] == 0) {
            printf("0\n");
            fclose(stdin);
            fclose(stdout);
            return 0;
        }

        hashB1 = (hashB1 * M + B[i]) % MOD1;
        hashB2 = (hashB2 * M + B[i]) % MOD2;
    }

    if (hashA1 == hashB1 && hashA2 == hashB2) {
        match[0] = true;
        ++matches;
    }

    int len_A = i;
    for ( ; B[i]; ++i) {
        hashB1 = ((hashB1 - B[i - len_A] * M1 % MOD1 + MOD1) * M + B[i]) % MOD1;
        hashB2 = ((hashB2 - B[i - len_A] * M2 % MOD2 + MOD2) * M + B[i]) % MOD2;

        if (hashA1 == hashB1 && hashA2 == hashB2) {
            match[i - len_A + 1] = true;
            ++matches;
        }
    }

    printf("%d\n", matches);

    matches = 0;
    for (i = 0; B[i] && matches < 1000; ++i)
        if (match[i]) {
            printf("%d ", i);
            ++matches;
        }
    printf("\n");

    fclose(stdin);
    fclose(stdout);
    return 0;
}
