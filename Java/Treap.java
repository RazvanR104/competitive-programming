//package set;

import java.io.*;
import java.util.*;

public class Main {
	public static void main(String[] args) throws IOException {
		InputReader in = new InputReader(new FileInputStream("hashuri.in"));
		PrintWriter out = new PrintWriter(new FileOutputStream("hashuri.out"));
		
		new Main().solve(in, out);
	}
	
	public void solve(InputReader in, PrintWriter out) {
		//Set<Integer> S = new Set<>();
		TreeSet<Integer> S = new TreeSet<>();
		int N = in.nextInt();
		
		while (N-- > 0) {
			int op, value;
			op = in.nextInt();
			value = in.nextInt();
			
			if (op == 1)
				S.add(value);
			else if (op == 2)
				S.remove(value);
			else {
				out.println(S.contains(value) ? '1' : '0');
			}
		}

		out.close();
	}
	
	class Set<T extends Comparable<T>> {
		private class Node {
			Node(int priority, int size, T value, Node left, Node right) {
				this.priority = priority;
				this.size = size;
				this.value = value;
				this.left = left;
				this.right = right;
			}
			
			int priority, size;
			T value;
			Node left, right;
		}
		
		private int size;
		private Node nil, root;
		private Random rand;
		
		Set() {
			size = 0;
			root = nil = new Node(-1, 0, null, null, null);
			nil.left = nil.right = nil;
			rand = new Random();
		}
		
		public int size() {
			return size;
		}
		
		public void add(T value) {
			root = Insert(root, value);
		}
		
		public void remove(T value) {
			root = Erase(root, value);
		}
		
		public T get(int pos) {
			return kth(root, pos + 1);
		}
		
		public boolean contains(T value) {
			return Exists(root, value);
		}
		
		private void Update(Node curr) {
			if (curr == nil)
				return;
			curr.size = curr.left.size + curr.right.size + 1;
		}
		
		private Node RotateLeft(Node curr) {
			if (curr == nil)
				return nil;
			
			Node A, B, C, D, E;
			A = curr;
			B = curr.left;
			C = curr.right;
			D = curr.left.left;
			E = curr.left.right;
			
			A.left = E;
			B.right = A;
			
			return B;
		}
		
		private Node RotateRight(Node curr) {
			if (curr == nil)
				return nil;
			
			Node A, B, C, D, E;
			A = curr;
			B = curr.left;
			C = curr.right;
			D = curr.right.left;
			E = curr.right.right;
			
			A.right = D;
			C.left = A;
			
			return C;
		}
		
		private Node Balance(Node curr) {
			if (curr == nil)
				return nil;
			
			if (curr.left.priority > curr.priority && curr.left.priority >= curr.right.priority) {
				curr = RotateLeft(curr);
				Update(curr.right);
				Update(curr);
			} else if (curr.right.priority > curr.priority && curr.right.priority >= curr.left.priority) {
				curr = RotateRight(curr);
				Update(curr.left);
				Update(curr);
			}
			
			return curr;
		}
		
		private Node Insert(Node curr, T value) {
			if (curr == nil) {
				++size;
				return new Node(rand.nextInt() & ((1 << 32) - 1), 1, value, nil, nil);
			}
			if (value.compareTo(curr.value) == 0)
				return curr;
			
			Node ret = nil;
			if (value.compareTo(curr.value) < 0) {
				ret = Insert(curr.left, value);
				curr.left = ret;
			} else {
				ret = Insert(curr.right, value);
				curr.right = ret;
			}
			
			Update(curr);
			ret = Balance(curr);

			return ret;
		}
		
		private Node Erase(Node curr, T value) {
			if (curr == nil)
				return nil;
			
			if (value.compareTo(curr.value) != 0) {
				Node ret = nil;
				if (value.compareTo(curr.value) < 0) {
					ret = Erase(curr.left, value);
					curr.left = ret;
				} else {
					ret = Erase(curr.right, value);
					curr.right = ret;
				}
				
				Update(curr);
				return curr;
			}
			
			if (curr.left == nil && curr.right == nil)
				return nil;
			
			Node ret = nil, _ret = nil;
			if (curr.left.priority >= curr.right.priority) {
				ret = RotateLeft(curr);
				Update(ret.right);
				_ret = Erase(ret.right, value);
				ret.right = _ret;
				Update(ret);
			} else {
				ret = RotateRight(curr);
				Update(ret.left);
				_ret = Erase(ret.left, value);
				ret.left = _ret;
				Update(ret);
			}
			
			return ret;
		}
		
		private T kth(Node curr, int pos) {
			if (curr == nil)
				return null;
			
			if (pos <= curr.left.size)
				return kth(curr.left, pos);
			if (pos == curr.left.size + 1)
				return curr.value;
			return kth(curr.right, pos - 1 - curr.left.size);
		}
		
		private boolean Exists(Node curr, T value) {
			if (curr == nil)
				return false;
			
			if (value.compareTo(curr.value) == 0)
				return true;
			if (value.compareTo(curr.value) < 0)
				return Exists(curr.left, value);
			return Exists(curr.right, value);
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
