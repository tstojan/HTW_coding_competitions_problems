import java.io.*;
import java.util.*;

public class sherlocked {
	public static int N, M;
	public static int[][] grid, visited;
	public static int[] dx = {1, -1, 0, 0}, dy = {0, 0, 1, -1};
	public static int ret = 1;
	public static void main(String[] args) throws IOException{
		FastScanner kb = new FastScanner(new File("input.txt"));
		//Scanner kb = new Scanner(System.in);
		PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("output.txt")));
		N = kb.nextInt(); M = kb.nextInt(); grid = new int[N][M]; visited = new int[N][M];
		for(int i = 0; i < N; i++)
			for(int j = 0; j < M; j++)
				grid[i][j] = kb.nextInt();
		for(int i = 0; i < N; i++)
			for(int j = 0; j < M; j++){
				if(visited[i][j] > 0) continue;
				recurse(i, j);
			}
		out.println(ret);
		out.close();
	}
	public static int recurse(int r, int c){
		if(visited[r][c] > 0) return visited[r][c];
		int res = 1;
		for(int a = 0; a < 4; a++){
			int nr = dx[a]+r; int nc = dy[a]+c;
			if(inBounds(nr, nc) && grid[nr][nc] == grid[r][c]-1)
				res = Math.max(res, recurse(nr, nc)+1);
		}
		ret = Math.max(ret, res);
		return visited[r][c] = res;
	}
	public static boolean inBounds(int x, int y){ return x > -1 && y > -1 && x < N && y < M; }
	static class FastScanner{
		BufferedReader br;
		StringTokenizer st;
		public FastScanner(File i) throws IOException{
			br = new BufferedReader(new FileReader(i));
			st = new StringTokenizer("");
		}
		public String next() throws IOException {
			if(st.hasMoreTokens())
				return st.nextToken();
			else
				st = new StringTokenizer(br.readLine());
			return next();
		}
		public int nextInt() throws IOException {
			return Integer.parseInt(next());
		}
		public String nextLine() throws IOException {
	        if(!st.hasMoreTokens())
	            return br.readLine();
	        String ret = st.nextToken();
	        while(st.hasMoreTokens())
	            ret += " " + st.nextToken();
	        return ret;
	    }
	}
}