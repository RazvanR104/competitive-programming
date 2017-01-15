#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e6 + 10;

int N;
int lim[NMAX], delta[NMAX];

const int BUFFER_SIZE = 1 << 20;
class Reader {
public:
	Reader() {}
	Reader(const char* filename) {
		file = fopen(filename, "r");
		cursor = 0;
		fread(buffer, BUFFER_SIZE, 1, file);
	}
	inline Reader & operator >> (int &n) {
		n = 0;
		while(!isdigit(buffer[cursor])) {
			advance();
		}
		while(isdigit(buffer[cursor])) {
			n = n * 10 + buffer[cursor] - '0';
			advance();
		}
		return *this;
	}

	inline void close() {
		fclose(file);
	}
private:
	int cursor, sign;
	char buffer[BUFFER_SIZE];
	FILE* file;
	inline void advance() {
		++cursor;
		if(cursor == BUFFER_SIZE) {
			cursor = 0;
			fread(buffer, BUFFER_SIZE, 1, file);
		}
	}
};

class Printer {
private:
	FILE *fout;
	char *buff;
	int sp;

	void write_ch(char ch) {
		if (sp == 50000) {
			fwrite(buff, 1, 50000, fout);
			sp = 0;
			buff[sp++] = ch;
		} else {
			buff[sp++] = ch;
		}
	}


public:
	Printer(const char* name) {
		fout = fopen(name, "w");
		buff = new char[50000]();
		sp = 0;
	}
	~Printer() {
		fwrite(buff, 1, sp, fout);
		fclose(fout);
	}

	Printer& operator << (int vu32) {
		if (vu32 <= 9) {
			write_ch(vu32 + '0');
		} else {
			(*this) << (vu32 / 10);
			write_ch(vu32 % 10 + '0');
		}
		return *this;
	}

	Printer& operator << (long long vu64) {
		if (vu64 <= 9) {
			write_ch(vu64 + '0');
		} else {
			(*this) << (vu64 / 10);
			write_ch(vu64 % 10 + '0');
		}
		return *this;
	}

	Printer& operator << (char ch) {
		write_ch(ch);
		return *this;
	}
	Printer& operator << (const char *ch) {
		while (*ch) {
			write_ch(*ch);
			++ch;
		}
		return *this;
	}
};

int main() {
	Reader cin("viteze.in");
	Printer cout("viteze.out");

	int i;
	cin >> N;
	for (i = 1; i <= N; ++i)
		cin >> lim[i];
	for (i = 1; i <= N; ++i)
		cin >> delta[i];

	lim[1] = min(lim[1], delta[1]);
	for (i = 2; i <= N; ++i)
		lim[i] = min(lim[i], lim[i - 1] + delta[i]);

	for (i = N - 1; i >= 1; --i)
		lim[i] = min(lim[i], lim[i + 1] + delta[i + 1]);

	for (i = 1; i <= N; ++i)
		cout << lim[i] << ' ';
	cout << '\n';

	return 0;
}
