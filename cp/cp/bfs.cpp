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