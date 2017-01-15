#include <bits/stdc++.h>

using namespace std;

typedef long long int64;

const int NMAX = 500010;

int N, Values[NMAX], Heap[NMAX];

template<class comparator>
void DownHeap(int pos, comparator cmp) {
    while (pos * 2 <= Heap[0]) {
        int son = pos * 2;
        if (son + 1 <= Heap[0] && cmp(Heap[son + 1], Heap[son]))
            ++son;
        if (cmp(Heap[son], Heap[pos])) {
            swap(Heap[son], Heap[pos]);
            pos = son;
        } else
            break;
    }
}

template<class comparator>
void BuildHeap(int left, int right, comparator cmp) {
    for ( ; left <= right; ++left)
        Heap[++Heap[0]] = Values[left];

    for (int i = Heap[0] / 2; i >= 1; --i)
        DownHeap(i, cmp);
}

template<class comparator>
void HeapSort(int left, int right, comparator cmp) {
    BuildHeap(left, right, cmp);

    for ( ; left <= right; ++left) {
        Values[left] = Heap[1];
        swap(Heap[1], Heap[Heap[0]--]);
        DownHeap(1, cmp);
    }
}

template<class comparator>
int Partition(int left, int right, comparator cmp) {
    int index = left + rand() % (right - left + 1);

    swap(Values[index], Values[right]);
    for (int i = left; i < right; ++i) {
        if (cmp(Values[i], Values[right]))
            swap(Values[i], Values[left++]);
    }
    swap(Values[right], Values[left]);

    return left;
}

template<class comparator>
void IntroSort(int left, int right, int depth, comparator cmp) {
    if (left > right)
        return;

    if (depth == 0) {
        HeapSort(left, right, cmp);
    } else {
        int index = Partition(left, right, cmp);
        IntroSort(left, index - 1, depth - 1, cmp);
        IntroSort(index + 1, right, depth - 1, cmp);
    }
}

inline int lg2(int value) {
    int res = -1;
    while (value) {
        ++res;
        value >>= 1;
    }
    return res;
}

const int BUFFER_SIZE = 1 << 21;
class InputReader {
    public:
        InputReader() {}
        InputReader(const char* filename) {
            file = fopen(filename, "r");
            cursor = 0;
            fread(buffer, BUFFER_SIZE, 1, file);
        }
        inline InputReader & operator >> (int &n) {
            n = 0;
            sign = 1;
            while(!isdigit(buffer[cursor])) {
                if (buffer[cursor] == '-') sign = -1;
                advance();
            }
            while(isdigit(buffer[cursor])) {
                n = n * 10 + buffer[cursor] - '0';
                advance();
            }
            n *= sign;
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

int main() {
	InputReader in("algsort.in");
	ofstream out("algsort.out");

	srand(time(NULL));

	in >> N;
	for (int i = 0; i < N; ++i)
        in >> Values[i];

    int MaxDepth = lg2(N);
    IntroSort(0, N - 1, MaxDepth, less<int>());

    for (int i = 0; i < N; ++i)
        out << Values[i] << ' ';
    out << '\n';

    in.close(), out.close();
    return 0;
}
