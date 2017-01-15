#include <bits/stdc++.h>

using namespace std;

const uint_fast32_t szUint64 = sizeof(uint_fast64_t);
const uint_fast32_t szUint8 = sizeof(uint_fast8_t);

void MemCpy(void *dest, const void *source, uint_fast32_t bytes) {
    uint_fast64_t *d = (uint_fast64_t *)dest;
    uint_fast64_t *s = (uint_fast64_t *)source;

    uint_fast32_t current = 0;
    while (current + szUint64 <= bytes) {
        current += szUint64;
        *d++ = *s++;
    }

    uint_fast8_t *d8 = (uint_fast8_t *)d;
    uint_fast8_t *s8 = (uint_fast8_t *)s;
    while (current + szUint8 <= bytes) {
        current += szUint8;
        *d8++ = *s8++;
    }
}


int64_t A[int(1e8) + 10], B[int(1e8) + 10];

char AA[300], BB[300];

int main() {
    int i, j;

    srand(time(0));
    for (i = 0; i < 1e8; ++i)
        A[i] = (((((rand() << 16) ^ rand()) << 16) ^ rand()) << 16) ^ rand();

    for (i = 0; i < (1 << 8) - 1; ++i)
        AA[i] = i;

    MemCpy(BB, AA, sizeof(char) * 255);

    cerr << strcmp(AA, BB) << '\n';

    double StartTime = clock();
    memcpy(B, A, 1e8 * sizeof(int64_t));
    //for (i = 0; i < 1e8; ++i)
    //    B[i] = A[i];
    double StopTime = clock();

    cerr << (StopTime - StartTime) / CLOCKS_PER_SEC << '\n';

    //memset(B, 0, sizeof B);

    StartTime = clock();
    //MemCpy(B, A, 1e8 * sizeof(int64_t));
    StopTime = clock();

    cerr << (StopTime - StartTime) / CLOCKS_PER_SEC << '\n';

    return 0;
}
