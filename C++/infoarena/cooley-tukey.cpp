#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1 << 22;
typedef long double ld;

const ld PI = acos(-1.0L);
const ld eps = 1e-12;

int N;
int rev[NMAX];
char _A[NMAX], _B[NMAX], answer[NMAX];
complex<ld> root[NMAX];
complex<ld> A[NMAX], rA[NMAX];
complex<ld> B[NMAX], rB[NMAX];
complex<ld> C[NMAX], rC[NMAX];

int castToInt(double value) {
	if (value > eps)
		return int(value + 0.5L);
	if (value < -eps)
		return int(value - 0.5L);
	return 0;
}

void precomputeRoot() {
	for (int i = 0; i < N; ++i)
		root[i] = complex<ld>(cos(2.0L * PI * ld(i) / ld(N)), sin(2.0L * PI * ld(i) / ld(N)));
}

int floorLg2(int value) {
	int answer = 0;
	for (int bit = 1 << 4; bit; bit >>= 1)
		if (value >> (answer + bit))
			answer += bit;
	return answer;
}

void precomputeRev() {
	int flLg2 = floorLg2(N - 1);
	int msb = -1;
	for (int i = 1; i < N; ++i) {
		if ((i & (i - 1)) == 0)
			++msb;
		rev[i] = rev[i ^ (1 << msb)];
		rev[i] |= (1 << (flLg2 - msb));
	}
}

void BitReverseCopy(complex<ld> *S, complex<ld> *D) {
	for (int i = 0; i < N; ++i)
		D[rev[i]] = S[i];
}

void FFT(complex<ld> *V, int left, int right) {
	int length = right - left + 1;
	if (length == 1)
		return;

	int mid = (left + right) / 2;
	FFT(V, left, mid);
	FFT(V, mid + 1, right);

	for (int i = 0; i < length / 2; ++i) {
		complex<ld> x = V[left + i], y = root[N / length * i] * V[left + i + length / 2];
		V[left + i] = x + y;
		V[left + i + length / 2] = x - y;
	}
}

void invFFT(complex<ld> *V, int length) {
	FFT(V, 0, length - 1);
	for (int i = 0; i < length; ++i)
		V[i] /= length;
	reverse(V + 1, V + length);
}

void generateTest() {
	ofstream fout("fft.in");
	default_random_engine generator;
	uniform_int_distribution<int> distribution1(0, 9), distribution2(1, 9);
	int N = 1000000, M = 1000000;
	fout << distribution2(generator);
	for (int i = 1; i < N; ++i)
		fout << distribution1(generator);
	fout << '\n';
	fout << distribution2(generator);
	for (int i = 1; i < M; ++i)
		fout << distribution1(generator);
	fout << '\n';
	fout.close();
}

int main() {
//	generateTest();

	assert(freopen("fft.in", "r", stdin));
	assert(freopen("fft.out", "w", stdout));

	int i, j, value;

	cin.getline(_A, NMAX);
	cin.getline(_B, NMAX);

	int lenA = strlen(_A);
	int lenB = strlen(_B);

	for (i = lenA - 1; i >= 0; --i)
		A[lenA - i - 1] = complex<ld>(_A[i] - '0', 0);
	for (i = lenB - 1; i >= 0; --i)
		B[lenB - i - 1] = complex<ld>(_B[i] - '0', 0);

	int flLg2A = floorLg2(lenA);
	int flLg2B = floorLg2(lenB);
	if ((1 << flLg2A) != lenA)
		++flLg2A;
	if ((1 << flLg2B) != lenB)
		++flLg2B;
	N = 1 << (1 + max(flLg2A, flLg2B));

	precomputeRoot();
	precomputeRev();

	BitReverseCopy(A, rA);
	BitReverseCopy(B, rB);
	FFT(rA, 0, N - 1);
	FFT(rB, 0, N - 1);

	for (i = 0; i < N; ++i)
		C[i] = rA[i] * rB[i];

	BitReverseCopy(C, rC);
	invFFT(rC, N);

	int carry = 0;
	for (i = 0; i < lenA + lenB; ++i) {
		int current = castToInt(rC[i].real()) + carry;
		answer[i] = current % 10 + '0';
		carry = current / 10;
	}
	reverse(answer, answer + lenA + lenB);
	if (answer[0] == '0')
		cout << answer + 1 << '\n';
	else
		cout << answer << '\n';

	return 0;
}
