#include "allheaders.h"
using namespace std;
int d[5] = { 0, -1, 0, 1, 0 };

int countSubIslands(vector<vector<int>>A, vector<vector<int>>B) {
	int n = A.size(), m = A[0].size(), ans = 0;
	vector<vector<bool>>visited;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (visited[i][j] or !B[i][j]) continue;
			queue<pair<int, int>>q;
			q.push({ i, j });
			visited[i][j] = 1;
			int ok = 1;
			while (!q.empty()) {
				auto p = q.front(); q.pop();
				int x = p.first, y = p.second;
				if (!A[x][y]) ok = 0;
				for (int k = 0; k < 4; k++) {
					int nx = x + d[k], ny = y + d[k + 1];
					if (nx < 0 or nx >= m or ny < 0 or ny >= n or visited[nx][ny] or !B[nx][ny]) continue;
					visited[nx][ny] = 1;
					q.push({ nx, ny });
				}
			}
			ans += ok;
		}
	}
	return ans;
}
//snake and ladder => minimum number of steps to go from 1 to 100 
int snakeLadder(vector<vector<int>> &A, vector<vector<int>> &B) {
	unordered_map<int, int>g;
	for (auto p : A)
		g[p[0]] = p[1];
	for (auto p : B)
		g[p[0]] = p[1];

	vector<int>dist(101, -1);
	queue<int>q;
	q.push(1);
	dist[1] = 0;
	while (!q.empty()) {
		int v = q.front(); q.pop();
		if (v == 100) return dist[100];
		for (int k = 1; k <= 6; k++) {
			int a = v + k;
			if (a > 100) continue;
			if (g.find(a) != g.end()) a = g[a];
			if (dist[a] == -1) {
				dist[a] = dist[v] + 1;
				q.push(a);
			}
		}
	}
	return -1;
}


//min Cost path
int minCostPath(int m, int n, vector<string>& grid) {
	int d[4][2] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };

	auto find = [](char c) {
		return c == 'R' ? 0 : c == 'L' ? 1 : c == 'D' ? 2 : 3;
	};

	vector<vector<int>>dp(m, vector<int>(n, INT_MAX));
	queue<pair<int, int>>q;
	q.push({ 0, 0 });
	dp[0][0] = 0;
	while (!q.empty()) {
		auto p = q.front(); q.pop();
		int i = p.first, j = p.second;

		for (int k = 0; k < 4; k++) {
			int ni = i + d[k][0], nj = j + d[k][1];
			if (ni >= 0 and nj >= 0 and ni < m and nj < n) {
				if (dp[ni][nj] > dp[i][j] + (find(grid[i][j]) != k)) {
					dp[ni][nj] = dp[i][j] + (find(grid[i][j]) != k);
					q.push({ ni, nj });
				}
			}
		}
	}

	return dp[m - 1][n - 1] == INT_MAX ? 0 : dp[m - 1][n - 1];
}