#include <x86intrin.h>
#include <string>
#include <fstream>
#include <memory>
#include <cstring>
#include <ctime>

using namespace std;

const int NMAX = 2010;

int N, M;
int X[NMAX] __attribute__((aligned(256))), Y[NMAX] __attribute__((aligned(256)));

class Reader {
public:
	Reader(const string& filename):
		m_stream(filename),
		m_pos(kBufferSize - 1),
		m_buffer(new char[kBufferSize]) {
		next();
	}
	Reader& operator>>(int& value) {
		value = 0;
		while (current() < '0' || current() > '9')
			next();
		while (current() >= '0' && current() <= '9') {
			value = value * 10 + current() - '0';
			next();
		}
		return *this;
	}
private:
	const int kBufferSize = 32768;
	char current() {
		return m_buffer[m_pos];
	}
	void next() {
		if (!(++m_pos != kBufferSize)) {
			m_stream.read(m_buffer.get(), kBufferSize);
			m_pos = 0;
		}
	}
	ifstream m_stream;
	int m_pos;
	unique_ptr<char[]> m_buffer;
};
class Writer {
public:
	Writer(const char *name):
		m_stream(name) {
		memset(m_buffer, 0, sizeof(m_buffer));
		m_pos = 0;
	}
	Writer& operator<<(int a) {
		int many = 0;
		do {
			digit_buffer[many++] = a % 10 + '0';
			a /= 10;
		} while (a > 0);
		for (int i = many - 1; i >= 0; --i)
			putchar(digit_buffer[i]);
		return *this;
	}
	Writer& operator<<(const char *s) {
		for (; *s; ++s)
			putchar(*s);
		return *this;
	}
	~Writer() {
		m_stream.write(m_buffer, m_pos);
	}
private:
	void putchar(char c) {
		m_buffer[m_pos++] = c;
		if (m_pos == kBufferSize) {
			m_stream.write(m_buffer, m_pos);
			m_pos = 0;
		}
	}
	static const int kBufferSize = 32768;
	ofstream m_stream;
	char m_buffer[kBufferSize];
	char digit_buffer[30];
	int m_pos;
};

void generateTest() {
	Writer cout("dsip.in");
	int N = 2000, M = 200000, MOD = 5001;
	srand(time(0));
	cout << N << " " << M << "\n";
	for (int i = 0; i < N; ++i)
		cout << rand() % MOD << " " << rand() % MOD << "\n";
	for (int i = 0; i < M; ++i)
		cout << rand() % MOD << " " << rand() % MOD << " " << rand() % MOD << " " << rand() % MOD << "\n";
}

int main() {
//	generateTest();

	Reader cin("dsip.in");
	Writer cout("dsip.out");
	int i;
	cin >> N >> M;
	for (i = 0; i < N; ++i)
		cin >> X[i] >> Y[i];

	while (M--) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		int eqTo = -((x1 - x2) * y1 + (y2 - y1) * x1);
		const __m256i eq = _mm256_set1_epi32(eqTo);
		__m256i ans1 = _mm256_set1_epi32(0), ans2 = _mm256_set1_epi32(0);
		const __m256i a = _mm256_set1_epi32(y1 - y2);
		const __m256i b = _mm256_set1_epi32(x2 - x1);
		const __m256i _and = _mm256_set1_epi32(1);
		for (i = 0; i + 8 <= N; i += 8) {
			__m256i nowX = _mm256_load_si256((__m256i *)(X + i));
			__m256i nowY = _mm256_load_si256((__m256i *)(Y + i));
			nowX = _mm256_mullo_epi32(nowX, a);
			nowY = _mm256_mullo_epi32(nowY, b);
			nowX = _mm256_add_epi32(nowX, nowY);
			__m256i _eq = _mm256_cmpeq_epi32(nowX, eq);
			_eq = _mm256_and_si256(_eq, _and);
			__m256i _gr = _mm256_cmpgt_epi32(nowX, eq);
			_gr = _mm256_and_si256(_gr, _and);
			ans1 = _mm256_add_epi32(ans1, _eq);
			ans2 = _mm256_add_epi32(ans2, _gr);
		}
//		int _ans1[8] __attribute__((aligned(256))), _ans2[8] __attribute__((aligned(256)));
//		_mm256_store_si256((__m256i *)_ans1, ans1);
//		_mm256_store_si256((__m256i *)_ans2, ans2);
//		int __ans1 = _ans1[0] + _ans1[1] + _ans1[2] + _ans1[3] + _ans1[4] + _ans1[5] + _ans1[6] + _ans1[7];
//		int __ans2 = _ans2[0] + _ans2[1] + _ans2[2] + _ans2[3] + _ans2[4] + _ans2[5] + _ans2[6] + _ans2[7];

		int __ans1 = 0, __ans2 = 0;
		__m256i temp1 = _mm256_permute2x128_si256(ans1, ans1, 1);
		__m256i temp2 = _mm256_add_epi32(ans1, temp1);
		temp2 = _mm256_hadd_epi32(temp2, temp2);
		temp2 = _mm256_hadd_epi32(temp2, temp2);
		__ans1 = _mm_cvtsi128_si32(_mm256_extracti128_si256(temp2, 0));
		temp1 = _mm256_permute2x128_si256(ans2, ans2, 1);
		temp2 = _mm256_add_epi32(ans2, temp1);
		temp2 = _mm256_hadd_epi32(temp2, temp2);
		temp2 = _mm256_hadd_epi32(temp2, temp2);
		__ans2 = _mm_cvtsi128_si32(_mm256_extracti128_si256(temp2, 0));

		while (i < N) {
			int value = X[i] * (y1 - y2) + Y[i] * (x2 - x1);
			if (value > eqTo)
				++__ans2;
			else if (value == eqTo)
				++__ans1;
			++i;
		}

		//brute-force
		/*	int __ans1 = 0, __ans2 = 0;
				for (i = 0; i < N; ++i) {
					int value = X[i] * (y1 - y2) + Y[i] * (x2 - x1);
					if (value > eqTo)
						++__ans2;
					else if (value == eqTo)
						++__ans1;
				}
		*/
		cout << min(__ans2, N - __ans2 - __ans1) << " " << max(__ans2, N - __ans2 - __ans1) << "\n";
	}

	return 0;
}
