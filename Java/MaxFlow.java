//package maxflow;

import java.io.*;
import java.util.*;

public class Main {
	public static void main(String[] args) throws FileNotFoundException {
		InputReader in = new InputReader(new FileInputStream("maxflow.in"));
		PrintWriter out = new PrintWriter(new FileOutputStream("maxflow.out"));
		
		new Main().solve(in, out);
		out.close();
	}
	
	private void solve(InputReader in, PrintWriter out) {
		int N, M;
		N = in.nextInt();
		M = in.nextInt();
		
		FlowNetwork Flow = new FlowNetwork(N, 0, N - 1);
		
		while (M-- > 0) {
			int from, to, capacity;
			from = in.nextInt();
			to = in.nextInt();
			capacity = in.nextInt();
			
			Flow.addEdge(from - 1, to - 1, capacity);
		}
		
		out.println(Flow.getFlow());
	}
	
	private class FlowNetwork {
		private class Edge {
			protected int from, to, flow, capacity;
			protected Edge rev;
			
			public Edge(int from, int to, int flow, int capacity) {
				this.from = from;
				this.to = to;
				this.flow = flow;
				this.capacity = capacity;
				rev = null;
			}
		}
		
		private ArrayList<ArrayList<Edge>> Graph;
		private final int MAX_NODES, source, sink;
		private Edge father[];
		
		public FlowNetwork(int MAX_NODES, int source, int sink) {
			this.MAX_NODES = MAX_NODES;
			this.source = source;
			this.sink = sink;
			
			father = new Edge[MAX_NODES];
			Graph = new ArrayList<>();
			
			for (int i = 0; i < MAX_NODES; ++i)
				Graph.add(new ArrayList<Edge>());
		}
		
		public void addEdge(int from, int to, int capacity) {
			Edge dir = new Edge(from, to, 0, capacity);
			Edge rev = new Edge(to, from, 0, 0);
			
			dir.rev = rev;
			rev.rev = dir;
			
			Graph.get(from).add(dir);
			Graph.get(to).add(rev);
		}
		
		private boolean getAugumentingPaths() {
			boolean visited[] = new boolean[MAX_NODES];
			for (int i = 0; i < MAX_NODES; ++i) {
				father[i] = null;
				visited[i] = false;
			}
			
			Queue<Integer> Q = new LinkedList<>();
			
			Q.add(source);
			visited[source] = true;
			
			while (!Q.isEmpty()) {
				int now = Q.poll();
				
				for (Edge it: Graph.get(now)) {
					if (visited[it.to] || it.capacity - it.flow <= 0)
						continue;
					father[it.to] = it;
					Q.add(it.to);
					visited[it.to] = true;
					
				}
			}
		
			return visited[sink];
		}
		
		public int getFlow() {
			int flow = 0;
			
			while (getAugumentingPaths()) {
				for (Edge it: Graph.get(sink)) {
					if (father[it.to] == null)
						continue;
					
					Edge now = it.rev;
					int augument = Integer.MAX_VALUE;
					
					while (now != null) {
						augument = Math.min(augument, now.capacity - now.flow);
						now = father[now.from];
					}
					
					flow += augument;
					now = it.rev;
					
					while (now != null) {
						now.flow += augument;
						now.rev.flow -= augument;
						now = father[now.from];
					}
				}
			}
			
			return flow;
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
