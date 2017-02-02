package maxflowmincost;

import java.io.*;
import java.util.*;

public class Main {
	public static void main(String[] args) throws FileNotFoundException {
		InputReader in = new InputReader(new FileInputStream("fmcm.in"));
		PrintWriter out = new PrintWriter(new FileOutputStream("fmcm.out"));
		
		new Main().solve(in, out);
		out.close();
	}
	
	private void solve(InputReader in, PrintWriter out) {		
		int N, M, So, Si;
		N = in.nextInt();
		M = in.nextInt();
		So = in.nextInt();
		Si = in.nextInt();
		
		FlowNetwork Network = new FlowNetwork(N, So - 1, Si - 1);
		
		while (M-- > 0) {
			int from, to, capacity, cost;
			from = in.nextInt();
			to = in.nextInt();
			capacity = in.nextInt();
			cost = in.nextInt();
			
			Network.addEdge(from - 1, to - 1, capacity, cost);
		}
		
		out.println(Network.getMaxFlowMinCost());
	}
	
	private class FlowNetwork {
        private class Edge {
            protected int from, to, flow, capacity, cost;
            protected Edge rev;
             
            public Edge(int from, int to, int flow, int capacity, int cost) {
                this.from = from;
                this.to = to;
                this.flow = flow;
                this.capacity = capacity;
                this.cost = cost;
                rev = null;
            }
        }
         
        private ArrayList<ArrayList<Edge>> Graph;
        private final int MAX_NODES, source, sink;
        private Edge father[];
        private int dist[], dist2[], rdist[];
         
        public FlowNetwork(int MAX_NODES, int source, int sink) {
            this.MAX_NODES = MAX_NODES;
            this.source = source;
            this.sink = sink;
             
            father = new Edge[MAX_NODES];
            dist = new int[MAX_NODES];
            dist2 = new int[MAX_NODES];
            rdist = new int[MAX_NODES];
            Graph = new ArrayList<>();
             
            for (int i = 0; i < MAX_NODES; ++i)
                Graph.add(new ArrayList<Edge>());
        }
         
        public void addEdge(int from, int to, int capacity, int cost) {
            Edge dir = new Edge(from, to, 0, capacity, cost);
            Edge rev = new Edge(to, from, 0, 0, -cost);
             
            dir.rev = rev;
            rev.rev = dir;
             
            Graph.get(from).add(dir);
            Graph.get(to).add(rev);
        }
        
        private boolean doBellmanFord() {
        	boolean inqueue[] = new boolean[MAX_NODES];
        	
        	for (int i = 0; i < MAX_NODES; ++i) {
        		dist[i] = Integer.MAX_VALUE;
        		inqueue[i] = false;
        	}
        	
        	Queue<Integer> Q = new LinkedList<>();
        	Q.add(source);
        	inqueue[source] = true;
        	dist[source] = 0;
        	
        	while (!Q.isEmpty()) {
        		int now = Q.poll();
        		inqueue[now] = false;

        		for (Edge it: Graph.get(now)) {
        			if (it.capacity - it.flow <= 0)
        				continue;
        			if (dist[it.to] > dist[it.from] + it.cost) {
        				dist[it.to] = dist[it.from] + it.cost;
        				
        				if (!inqueue[it.to]) {
        					Q.add(it.to);
        					inqueue[it.to] = true;
        				}
        			}
        		}
        	}
        	
        	return dist[sink] != Integer.MAX_VALUE;
        }
        
        private boolean doDijkstra() {
        	for (int i = 0; i < MAX_NODES; ++i) {
        		dist2[i] = Integer.MAX_VALUE;
        		father[i] = null;
        	}
        	
        	PriorityQueue<Pair> PQ = new PriorityQueue<>();
        	PQ.add(new Pair(0, source));
        	rdist[source] = dist2[source] = 0;
        	
        	while (!PQ.isEmpty()) {
        		Pair now = PQ.poll();
        		
        		if (dist2[now.Y] != now.X)
        			continue;
        		
        		for (Edge it: Graph.get(now.Y)) {
        			if (it.capacity - it.flow <= 0)
        				continue;
        			if (dist2[it.to] > dist2[it.from] + dist[it.from] - dist[it.to] + it.cost) {
        				dist2[it.to] = dist2[it.from] + dist[it.from] - dist[it.to] + it.cost;
        				rdist[it.to] = rdist[it.from] + it.cost;
        				father[it.to] = it;
        				
        				PQ.add(new Pair(dist2[it.to], it.to));
        			}
        		}
        	}
        	
        	for (int i = 0; i < MAX_NODES; ++i)
        		dist[i] = rdist[i];
        	
        	return dist2[sink] != Integer.MAX_VALUE;
        }
         
        public int getMaxFlowMinCost() {
            int flow_cost = 0;
            
            doBellmanFord();
            while (doDijkstra()) {
            	int augument = Integer.MAX_VALUE;
            	
            	Edge curr = father[sink];
            	while (curr != null) {
            		augument = Math.min(augument, curr.capacity - curr.flow);
            		curr = father[curr.from];
            	}
            	
            	if (augument > 0) {
            		flow_cost += augument * rdist[sink];
            		
            		curr = father[sink];
            		while (curr != null) {
            			curr.flow += augument;
            			curr.rev.flow -= augument;
            			curr = father[curr.from];
            		}
            	}
            }
            
            return flow_cost;
        }
    }
	
	public class Pair implements Comparable<Pair> {
		public int X, Y;
		
		public Pair(int X, int Y) {
			this.X = X;
			this.Y = Y;
		}
		
		@Override
		public int compareTo(Pair arg0) {
			if (X != arg0.X)
				return X - arg0.X;
			return Y - arg0.Y;
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
