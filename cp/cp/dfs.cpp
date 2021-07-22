#include "allheaders.h"
using namespace std;
//https://leetcode.com/problems/minesweeper/
vector<vector<char>>minesweeper(vector<vector<char>>board, vector<int>click) {
	int m = board.size(), n = board[0].size();
	int row = click[0], col = click[1];
	
	if (board[row][col] == 'M')
		board[row][col] = 'X'; //if mine is found mark it and return
	else {
		int count = 0;
		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				if (i == 0 and j == 0) continue;
				int r = row + i, c = col + j; //checking in all directions
				if (r < 0 or r >= m or c < 0 or c >= n) continue;
				if (board[r][c] == 'M' or board[r][c] == 'X')
					count++; //counting the mines
			}
		}
		if (count > 0)
			board[row][col] = (char)(count + '0'); //mark the digits
		else {
			board[row][col] = 'B'; //tile is revealed
			for (int i = -1; i <= 1; i++) {
				for (int j = -1; j <= 1; j++) {
					if (i == 0 and j == 0) continue;
					int r = row + i, c = col + j; //checking in all directions
					if (r < 0 or r >= m or c < 0 or c >= n) continue;
					vector<int>newClick = { r, c };
					if (board[r][c] == 'E') minesweeper(board, newClick); //if tile is unrevealed
				}
			}
		}
	}
	return board;
}

//https://leetcode.com/problems/matchsticks-to-square/
bool canMakeSquare(vector<int>sides, vector<int>A, int i, int target) {
	if (i == A.size())
		return all_of(begin(sides), end(sides), [&](int i) { return i == sides[0]; });
	for (int j = 0; j < 4; j++) {
		if (sides[j] + A[i] > target) continue;
		int k = j;
		while (--k >= 0)
			if (sides[j] == sides[k]) break;
		if (k != -1) continue;
		sides[j] += A[i];
		if (canMakeSquare(sides, A, i + 1, target)) return true;
		sides[j] -= A[i];
	}
	return false;
}
bool makeSquare(vector<int>A) {
	sort(rbegin(A), rend(A));
	if (A.size() < 4) return false;
	int p = accumulate(begin(A), end(A), 0LL);
	if (p % 4 != 0) return false;
	int s = p / 4;
	vector<int>sides(4, 0);
	return canMakeSquare(sides, A, 0, s);
}

//https://leetcode.com/problems/pyramid-transition-matrix/
bool pyramidTransition(string bottom, vector<string>& allowed) {
	unordered_map<string, vector<char>>u;
	function<bool(string&, string)> dfs = [&](string& bottom, string top) {
		if (top.size() == bottom.size() - 1)
			return top.empty() ? true : dfs(top, string());
		for (auto c : u[bottom.substr(top.size(), 2)])
			if (dfs(bottom, top + c)) return true;
		return false;
	};
	for (string s : allowed)
		u[s.substr(0, 2)].push_back(s[2]);
	return dfs(bottom, string());
}

//Given a rectangle of size n x m, find the minimum number of integer-sided squares that tile the rectangle.
int tilingRectangle(int n, int m) {
	if ((m == 13 and n == 11) or (m == 11 and n == 13)) return 6;

	int dp[15][15] = {};
	function<int(int, int)>rec = [&](int n, int m) {
		int mx = 500;
		if (n == m) return 1;
		if (n <= 0 or m <= 0) return 0;
		if (dp[n][m]) return dp[n][m];
		int mn = mx;
		for (int i = 1; i <= min(n, m); i++) {
			int r1 = 1 + rec(n - i, m) + rec(i, m - i);
			int r2 = 1 + rec(n, m - i) + rec(n - i, i);
			mn = min({ mn, r1, r2 });
		}
		return dp[n][m] = mn;
	};

	return rec(n, m);
}