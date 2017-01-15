#include <bits/stdc++.h>

using namespace std;

typedef long long int64;

const int NMAX = 10000010, RADIX_SIZE = 8, BITS = 32, RADIX = 0xff;

int N, A, B, C;
int values[NMAX], radix[1 << RADIX_SIZE], current[NMAX];
int *source = values, *destination = current;

int main() {
	ifstream in("radixsort.in");
	ofstream out("radixsort.out");

    int i, j;

	in >> N >> A >> B >> C;

    values[1] = B;
    for (i = 2; i <= N; ++i)
        values[i] = (1LL * A * values[i - 1] + B) % C;

    for (i = 0; i < BITS; i += RADIX_SIZE) {
        for (j = 1; j <= N; ++j)
           ++radix[(source[j] >> i) & RADIX];

        for (j = 1; j < (1 << RADIX_SIZE); ++j)
            radix[j] += radix[j - 1];

        for (j = N; j >= 1; --j)
            destination[radix[(source[j] >> i) & RADIX]--] = source[j];

        memset(radix, 0, sizeof(radix));
        swap(source, destination);
    }

    for (i = 1; i <= N; i += 10) out << values[i] << ' ';
    out << '\n';

    in.close(), out.close();
    return 0;
}
