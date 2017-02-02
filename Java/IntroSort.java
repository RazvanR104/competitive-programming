//package introsort;

import java.io.*;
import java.util.*;

public class Main {
	private static int max_depth;
	
	public static void main(String[] args) throws IOException {
		InputReader in = new InputReader(new FileInputStream("algsort.in"));
		PrintWriter out = new PrintWriter(new FileOutputStream("algsort.out"));
		new Main().solve(in, out);
		out.close();
	}
	
	private int MSB(int value) {
		int answer = 0;
		for (int bit = 16; bit > 0; bit /= 2)
			if ((value >> (bit + answer)) != 0)
				answer += bit;
		return answer;
	}
	
	private void solve(InputReader in, PrintWriter out) {
		int N = in.nextInt();
		max_depth = MSB(N);
		
		int[] arr = new int[N];
		for (int i = 0; i < N; ++i)
			arr[i] = in.nextInt();
		
		//Arrays.sort(arr);
		IntroSort(arr, 0, N - 1, 0);
		
		for (int i = 0; i < N; ++i)
			out.print(arr[i] + " ");
		out.println();
	}
	
	private void IntroSort(int arr[], int left, int right, int depth) {
		if (left >= right)
			return;
		if (depth >= max_depth) {
			Heap H = new Heap(right - left + 1);
			for (int i = left; i <= right; ++i)
				H.Insert(arr[i]);
			H.Build();
			
			int[] sorted = H.GetSortedValues();
			for (int i = left; i <= right; ++i)
				arr[i] = sorted[i - left];
			
			return;
		}
		
		/*Random generator = new Random();
		int random = generator.nextInt();
		if (random < 0)
			random = -random;
		int index = left + random % (right - left + 1);*/
		int index = (left + right) / 2;
		
		int temp = arr[right];
		arr[right] = arr[index];
		arr[index] = temp;
		
		int pos = left;
		for (int i = left; i < right; ++i) {
			if (arr[i] < arr[right]) {
				temp = arr[i];
				arr[i] = arr[pos];
				arr[pos++] = temp;
			}
		}
		temp = arr[right];
		arr[right] = arr[pos];
		arr[pos] = temp;
		
		IntroSort(arr, left, pos - 1, depth + 1);
		IntroSort(arr, pos + 1, right, depth + 1);
	}

	class Heap<T> {
		private List<T> tree = new ArrayList<>();
	
		private int current;
		
		Heap(final int size) {
			this.size = size;
			tree.size()
			current = 0;
			
			tree.sort((x,y)->x - y));
		}
		
		public void Insert(int value) {
			tree[current++] = value;
		}
		
		public void Build() {
			for (int i = size / 2; i >= 0; --i)
				DownHeap(i);
		}
		
		public int[] GetSortedValues() {
			int[] ret = new int[size];
			
			int pos = 0;
			int _size = size;
			while (pos < _size) {
				ret[pos++] = tree[0];
				tree[0] = tree[size - 1];
				--size;
				DownHeap(0);
			}
			
			return ret;
		}
		
		private void DownHeap(int node) {
			while (node * 2 + 1 < size) {
				int next = node;
				if (tree[next] > tree[node * 2 + 1])
					next = node * 2 + 1;
				if (node * 2 + 2 < size && tree[next] > tree[node * 2 + 2])
					next = node * 2 + 2;
				if (next == node)
					break;
				int temp = tree[node];
				tree[node] = tree[next];
				tree[next] = temp;
				node = next;
			}
		}
	}
	
    static class InputReader {
        private InputStream stream;
        private byte[] buf = new byte[1024];
        private int curChar;
        private int numChars;
 
        public InputReader(InputStream stream) {
            this.stream = stream;
        }
 
        public int read() {
            if (numChars == -1)
                throw new UnknownError();
            if (curChar >= numChars) {
                curChar = 0;
                try {
                    numChars = stream.read(buf);
                } catch (IOException e) {
                    throw new UnknownError();
                }
                if (numChars <= 0)
                    return -1;
            }
            return buf[curChar++];
        }
 
        public int peek() {
            if (numChars == -1)
                return -1;
            if (curChar >= numChars) {
                curChar = 0;
                try {
                    numChars = stream.read(buf);
                } catch (IOException e) {
                    return -1;
                }
                if (numChars <= 0)
                    return -1;
            }
            return buf[curChar];
        }
 
        public void skip(int x) {
            while (x-- > 0)
                read();
        }
 
        public int nextInt() {
            return Integer.parseInt(next());
        }
 
        public long nextLong() {
            return Long.parseLong(next());
        }
 
        public String nextString() {
            return next();
        }
 
        public String next() {
            int c = read();
            while (isSpaceChar(c))
                c = read();
            StringBuffer res = new StringBuffer();
            do {
                res.appendCodePoint(c);
                c = read();
            } while (!isSpaceChar(c));
 
            return res.toString();
        }
 
        public String nextLine() {
            StringBuffer buf = new StringBuffer();
            int c = read();
            while (c != '\n' && c != -1) {
                if (c != '\r')
                    buf.appendCodePoint(c);
                c = read();
            }
            return buf.toString();
        }
 
        public double nextDouble() {
            int c = read();
            while (isSpaceChar(c))
                c = read();
            int sgn = 1;
            if (c == '-') {
                sgn = -1;
                c = read();
            }
            double res = 0;
            while (!isSpaceChar(c) && c != '.') {
                if (c == 'e' || c == 'E')
                    return res * Math.pow(10, nextInt());
                if (c < '0' || c > '9')
                    throw new InputMismatchException();
                res *= 10;
                res += c - '0';
                c = read();
            }
            if (c == '.') {
                c = read();
                double m = 1;
                while (!isSpaceChar(c)) {
                    if (c == 'e' || c == 'E')
                        return res * Math.pow(10, nextInt());
                    if (c < '0' || c > '9')
                        throw new InputMismatchException();
                    m /= 10;
                    res += (c - '0') * m;
                    c = read();
                }
            }
            return res * sgn;
        }
 
        public boolean hasNext() {
            int value;
            while (isSpaceChar(value = peek()) && value != -1)
                read();
            return value != -1;
        }
 
        private boolean isSpaceChar(int c) {
            return c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == -1;
        }
    }
}