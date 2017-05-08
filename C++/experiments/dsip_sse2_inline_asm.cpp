#include <fstream>
#include <cstring>
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <memory>

using namespace std;

const int NMAX = 2010;

int N, M;
int X[NMAX] __attribute__((aligned(16))), Y[NMAX] __attribute__((aligned(16)));

typedef long long __m128i __attribute__ ((__vector_size__ (16)));

static inline __m128i muly(const __m128i &a, const __m128i &b) {
	__m128i answer;
	asm("movdqa %1, %%xmm0;"
	    "pmuludq %2, %%xmm0;"
	    "movdqa %1, %%xmm1;"
	    "psrldq $4, %%xmm1;"
	    "movdqa %2, %%xmm2;"
	    "psrldq $4, %%xmm2;"
	    "pmuludq %%xmm2, %%xmm1;"
	    "pshufd $8, %%xmm0, %%xmm2;"
	    "pshufd $8, %%xmm1, %%xmm0;"
	    "punpckldq %%xmm0, %%xmm2;"
	    "movdqa %%xmm2, %0"
	    : "=m"(answer)
	    : "m"(a), "m"(b)
	    : /*"xmm0", "xmm1", "xmm2"*/);
	//__m128i tmp2 = _mm_mul_epu32( _mm_srli_si128(a,4), _mm_srli_si128(b,4));
	//return _mm_unpacklo_epi32(_mm_shuffle_epi32(tmp1, _MM_SHUFFLE (0,0,2,0)), _mm_shuffle_epi32(tmp2, _MM_SHUFFLE (0,0,2,0)));
	return answer;
}

void generateTest() {
	assert(freopen("dsip.in", "w", stdout));
	int N = 2000, M = 200000, MOD = 5001;
	srand(time(0));
	cout << N << ' ' << M << '\n';
	for (int i = 0; i < N; ++i)
		cout << rand() % MOD << ' ' << rand() % MOD << '\n';
	for (int i = 0; i < M; ++i)
		cout << rand() % MOD << ' ' << rand() % MOD << ' ' << rand() % MOD << ' ' << rand() % MOD << '\n';
	fclose(stdout);
}

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

int main() {
//	generateTest();

	Reader cin("dsip.in");
	Writer cout("dsip.out");

	int i;
	cin >> N >> M;
	for (i = 0; i < N; ++i)
		cin >> X[i] >> Y[i];
	int _ans1[4] __attribute__((aligned(16))), _ans2[4] __attribute__((aligned(16)));

	while (M--) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		int eqTo = -((x1 - x2) * y1 + (y2 - y1) * x1);
		const int eqArr[] = {eqTo, eqTo, eqTo, eqTo};
		const int ansArr[] = {0, 0, 0, 0};
		const int aArr[] = {y1 - y2, y1 - y2, y1 - y2, y1 - y2};
		const int bArr[] = {x2 - x1, x2 - x1, x2 - x1, x2 - x1};
		const int andArr[] = {1, 1, 1, 1};
		/*__m128i eq = _mm_set1_epi32(eqTo);
		__m128i ans1 = _mm_set1_epi32(0), ans2 = _mm_set1_epi32(0);
		__m128i a = _mm_set1_epi32(y1 - y2);
		__m128i b = _mm_set1_epi32(x2 - x1);
		__m128i _and = _mm_set_epi32(1, 1, 1, 1);*/
		__m128i eq, ans1, ans2, a, b, _and;
		asm("movdqa %6, %%xmm0;"
		    "movdqa %%xmm0, %0;"
		    "movdqa %7, %%xmm0;"
		    "movdqa %%xmm0, %1;"
		    "movdqa %%xmm0, %2;"
		    "movdqa %8, %%xmm0;"
		    "movdqa %%xmm0, %3;"
		    "movdqa %9, %%xmm0;"
		    "movdqa %%xmm0, %4;"
		    "movdqa %10, %%xmm0;"
		    "movdqa %%xmm0, %5"
		    : "=m"(eq), "=m"(ans1), "=m"(ans2), "=m"(a), "=m"(b), "=m"(_and)
		    : "m"(*eqArr), "m"(*ansArr), "m"(*aArr), "m"(*bArr), "m"(*andArr)
		    : /*"xmm0"*/);
		for (i = 0; i + 4 <= N; i += 4) {
			//__m128i nowX = _mm_loadu_si128((__m128i *)(X + i));
			//__m128i nowY = _mm_loadu_si128((__m128i *)(Y + i));
			asm("movdqa %2, %%xmm0;"
			    "movdqa %4, %%xmm1;"
			    "movdqa %%xmm0, %%xmm2;"
			    "movdqa %%xmm1, %%xmm3;"
			    "psrldq $4, %%xmm2;"
			    "psrldq $4, %%xmm3;"
			    "pmuludq %%xmm1, %%xmm0;"
			    "pmuludq %%xmm3, %%xmm2;"
			    "pshufd $8, %%xmm0, %%xmm1;"
			    "pshufd $8, %%xmm2, %%xmm0;"
			    "punpckldq %%xmm0, %%xmm1;"
			    "movdqa %%xmm1, %%xmm4;"
			    "movdqa %3, %%xmm0;"
			    "movdqa %5, %%xmm1;"
			    "movdqa %%xmm0, %%xmm2;"
			    "movdqa %%xmm1, %%xmm3;"
			    "psrldq $4, %%xmm2;"
			    "psrldq $4, %%xmm3;"
			    "pmuludq %%xmm1, %%xmm0;"
			    "pmuludq %%xmm3, %%xmm2;"
			    "pshufd $8, %%xmm0, %%xmm1;"
			    "pshufd $8, %%xmm2, %%xmm0;"
			    "punpckldq %%xmm0, %%xmm1;"
			    "movdqa %%xmm1, %%xmm0;"
			    "paddd %%xmm4, %%xmm0;"
			    "movdqa %%xmm0, %%xmm1;"
			    "pcmpeqd %6, %%xmm0;"
			    "pcmpgtd %6, %%xmm1;"
			    "pand %7, %%xmm0;"
			    "pand %7, %%xmm1;"
			    "paddd %0, %%xmm0;"
			    "paddd %1, %%xmm1;"
			    "movdqa %%xmm0, %0;"
			    "movdqa %%xmm1, %1"
			    : "+m"(ans1), "+m"(ans2)
			    : "m"(*(X + i)), "m"(*(Y + i)), "m"(a), "m"(b), "m"(eq), "m"(_and)
			    : /*"xmm0"*/);
			/*nowX = _mm_add_epi32(nowX, nowY);
			__m128i _eq = _mm_cmpeq_epi32(nowX, eq);
			_eq = _mm_and_si128(_eq, _and);
			__m128i _gr = _mm_cmpgt_epi32(nowX, eq);
			_gr = _mm_and_si128(_gr, _and);
			ans1 = _mm_add_epi32(ans1, _eq);
			ans2 = _mm_add_epi32(ans2, _gr);*/
			//cout << "0\\";
		}
		//_mm_store_si128((__m128i *)_ans1, ans1);
		//_mm_store_si128((__m128i *)_ans2, ans2);
		asm("movdqa %2, %%xmm0;"
		    "movdqa %%xmm0, %0;"
		    "movdqa %3, %%xmm0;"
		    "movdqa %%xmm0, %1;"
		    : "=m"(*_ans1), "=m"(*_ans2)
		    : "m"(ans1), "m"(ans2)
		    : /*"xmm0"*/);
		int __ans1 = _ans1[0] + _ans1[1] + _ans1[2] + _ans1[3], __ans2 = _ans2[0] + _ans2[1] + _ans2[2] + _ans2[3];
		while (i < N) {
			int value = X[i] * (y1 - y2) + Y[i] * (x2 - x1);
			if (value > eqTo)
				++__ans2;
			else if (value == eqTo)
				++__ans1;
			++i;
		}
		/*int __ans1 = 0, __ans2 = 0;
		for (i = 0; i < N; ++i) {
			int value = X[i] * (y1 - y2) + Y[i] * (x2 - x1);
			if (value > eqTo)
				++__ans2;
			else if (value == eqTo)
				++__ans1;
		}*/
		cout << min(__ans2, N - __ans2 - __ans1) << " " << max(__ans2, N - __ans2 - __ans1) << "\n";
	}

	return 0;
}
