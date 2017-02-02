//package ahocorasick;

import java.io.*;
import java.util.*;

public class Main {
	public static void main(String[] args) throws FileNotFoundException {
		InputReader in = new InputReader(new FileInputStream("ahocorasick.in"));
		PrintWriter out = new PrintWriter(new FileOutputStream("ahocorasick.out"));

		new Main().solve(in, out);
	}
	
	private void solve(InputReader in, PrintWriter out) {
		String text = in.nextString();
		AhoCorasickAutomaton AC = new AhoCorasickAutomaton(26);
		
		int dict_size = in.nextInt();
		for (int i = 0; i < dict_size; ++i) {
			String Word = in.nextString();
			AC.addWord(Word, i);
		}
		
		int[] answer = AC.process(text, dict_size);
		for (int i = 0; i < dict_size; ++i)
			out.println(answer[i]);
		
		out.close();
	}
	
	private class AhoCorasickAutomaton {
		private final int ALPHABET_SIZE;
		private class Node {
			int num;
			ArrayList<Integer> Final;
			Node[] sons;
			Node fail;
			
			public Node() {
				num = 0;
				Final = new ArrayList<>();
				sons = new Node[ALPHABET_SIZE];
				for (int i = 0; i < ALPHABET_SIZE; ++i)
					sons[i] = null;
				fail = null;
			}
		}
		
		private Node root;
		private ArrayList<Node> Queue;
		
		public AhoCorasickAutomaton(final int ALPHABET_SIZE) {
			this.ALPHABET_SIZE = ALPHABET_SIZE;
			root = new Node();
			Queue = new ArrayList<>();
		}
		
		public void addWord(String Word, int word_num) {
			addWord(root, Word, 0, word_num);
		}
		
		public int[] process(String Text, int size) {
			int[] ret = new int[size];
			
			BFS();
			
			Node curr = root;
			for (int i = 0; i < Text.length(); ++i) {
				while (curr.sons[Text.charAt(i) - 'a'] == null && curr != root)
					curr = curr.fail;
				if (curr.sons[Text.charAt(i) - 'a'] != null) {
					curr = curr.sons[Text.charAt(i) - 'a'];
					++curr.num;
				}
			}
			
			counterBFS();
		
			for (int i = right; i >= 0; --i) {
				for (int pos: Queue.get(i).Final) {
					ret[pos] = Queue.get(i).num;
				}
			}
			
			return ret;
		}
		
		private void addWord(Node curr, String Word, int pos, int word_num) {
			if (pos >= Word.length()) {
				curr.Final.add(word_num);
				return;
			}
			if (curr.sons[Word.charAt(pos) - 'a'] == null)
				curr.sons[Word.charAt(pos) - 'a'] = new Node();
			addWord(curr.sons[Word.charAt(pos) - 'a'], Word, pos + 1, word_num);
		}
		
		private int left, right;
		private void BFS() {
			left = right = 0;
			root.fail = root;
			Queue.add(root);
			
			while (left <= right) {
				Node curr = Queue.get(left++);
				
				for (int i = 0; i < ALPHABET_SIZE; ++i) {
					if (curr.sons[i] != null) {
						Node fail = curr.fail;
						while (fail != root && fail.sons[i] == null)
							fail = fail.fail;
						
						if (fail.sons[i] != null && curr.sons[i] != fail.sons[i]) {
							curr.sons[i].fail = fail.sons[i];
						} else {
							curr.sons[i].fail = root;
						}
						Queue.add(curr.sons[i]);
						++right;
					}
				}
			}
		}
		
		private void counterBFS() {
			for (int i = right; i >= 0; --i) {
				Queue.get(i).fail.num += Queue.get(i).num;
			}
		}
	}

    private static class InputReader {
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
