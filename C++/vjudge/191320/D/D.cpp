#include <bits/stdc++.h>

using namespace std;

const int NMAX = 2e5 + 10;

int TESTS, N, Q;
int V[NMAX];
vector<int> uV;
unordered_map<int, int> where;

class ConsoleReader {
public:
	ConsoleReader():
		m_pos(kBufferSize - 1),
		m_buffer(new char[kBufferSize]) {
		next();
	}
	ConsoleReader& operator>>(int& value) {
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
			cin.read(m_buffer.get(), kBufferSize);
			m_pos = 0;
		}
	}
	int m_pos;
	unique_ptr<char[]> m_buffer;
};

class ConsoleWriter {
public:
	ConsoleWriter() {
		memset(m_buffer, 0, sizeof(m_buffer));
		m_pos = 0;
	}
	ConsoleWriter& operator<<(int a) {
		int many = 0;
		do {
			digit_buffer[many++] = a % 10 + '0';
			a /= 10;
		} while (a > 0);
		for (int i = many - 1; i >= 0; --i)
			putchar(digit_buffer[i]);
		return *this;
	}
	ConsoleWriter& operator<<(const char *s) {
		for (; *s; ++s)
			putchar(*s);
		return *this;
	}
	~ConsoleWriter() {
		cout.write(m_buffer, m_pos);
	}
private:
	void putchar(char c) {
		m_buffer[m_pos++] = c;
		if (m_pos == kBufferSize) {
			cout.write(m_buffer, m_pos);
			m_pos = 0;
		}
	}
	static const int kBufferSize = 32768;
	char m_buffer[kBufferSize];
	char digit_buffer[30];
	int m_pos;
};

struct Node {
	int sum, l, r;
	Node(int sum = 0, int l = 0, int r = 0):
		sum(sum),
		l(l),
		r(r) {
	}
} T[1 << 24];
int root[NMAX];
int lastNode;

int updateSegmentTree(int currNode, int left, int right, int pos) {
	if (left == right) {
		T[++lastNode] = {T[currNode].sum + 1, 0, 0};
		return lastNode;
	}
	int mid = (left + right) / 2;
	if (pos <= mid) {
		int nextNode = ++lastNode;
		T[nextNode] = {T[currNode].sum + 1, updateSegmentTree(T[currNode].l, left, mid, pos), T[currNode].r};
		return nextNode;
	}
	int nextNode = ++lastNode;
	T[nextNode] = {T[currNode].sum + 1, T[currNode].l, updateSegmentTree(T[currNode].r, mid + 1, right, pos)};
	return nextNode;
}

int kthSegmentTree(int leftTree, int rightTree, int left, int right, int value) {
	if (left == right)
		return uV[left];
	int mid = (left + right) / 2;
	if (value <= T[T[rightTree].l].sum - T[T[leftTree].l].sum)
		return kthSegmentTree(T[leftTree].l, T[rightTree].l, left, mid, value);
	return kthSegmentTree(T[leftTree].r, T[rightTree].r, mid + 1, right, value - T[T[rightTree].l].sum + T[T[leftTree].l].sum);
}

int sumSegmentTree(int leftTree, int rightTree, int left, int right, int pos) {
	if (right <= pos)
		return T[rightTree].sum - T[leftTree].sum;
	if (left >= right)
		return 0;
	int mid = (left + right) / 2;
	int answer = 0;
	if (pos <= mid)
		answer += sumSegmentTree(T[leftTree].l, T[rightTree].l, left, mid, pos);
	else if (pos > mid) {
		answer += T[T[rightTree].l].sum - T[T[leftTree].l].sum;
		answer += sumSegmentTree(T[leftTree].r, T[rightTree].r, mid + 1, right, pos);
	}
	return answer;
}

int main() {
	cin.sync_with_stdio(0);
	cout.sync_with_stdio(0);
	ConsoleReader input;
	ConsoleWriter output;

	input >> TESTS;
	int i, t;
	for (t = 1; t <= TESTS; ++t) {
		uV.clear();
		where.clear();

		input >> N >> Q;
		uV.push_back(0);
		for (i = 1; i <= N; ++i) {
			input >> V[i];
			uV.push_back(V[i]);
		}
		sort(uV.begin() + 1, uV.end());
		uV.erase(unique(uV.begin() + 1, uV.end()), uV.end());
		for (i = 1; i < int(uV.size()); ++i)
			where[uV[i]] = i;

		lastNode = 0;
		for (i = 1; i <= N; ++i)
			root[i] = updateSegmentTree(root[i - 1], 1, uV.size() - 1, where[V[i]]);

		output << "Case #" << t << ":\n";
		while (Q--) {
			int l, r, k;
			input >> l >> r >> k;
			int pos = lower_bound(uV.begin() + 1, uV.end(), k) - uV.begin();
			int kPos = sumSegmentTree(root[l - 1], root[r], 1, uV.size() - 1, pos - 1);
			int answer = numeric_limits<int>::max();
			if (kPos > 0)
				answer = min(answer, abs(k - kthSegmentTree(root[l - 1], root[r], 1, uV.size() - 1, kPos)));
			if (kPos + 1 <= T[root[r]].sum - T[root[l - 1]].sum)
				answer = min(answer, abs(k - kthSegmentTree(root[l - 1], root[r], 1, uV.size() - 1, kPos + 1)));
			output << answer << "\n";
		}
	}

	return 0;
}
