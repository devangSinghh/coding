#include "allheaders.h"
using namespace std;

//https://leetcode.com/problems/unique-paths-iii/
int dfsUniquePathsIII(vector<vector<int>>A, int i, int j, int m, int n, int cs, int steps) {
	if (i < 0 or j < 0 or i >= m or j >= n or A[i][j] == -1) return 0;
	if (A[i][j] == 2) return steps == cs ? 1 : 0; //if we reach the target and the steps taken by us is equal to the number of 0s + initial point...
	//return 1 i.e. 1 path exists else return 0, i.e. no path
	A[i][j] = -1;
	int path = dfsUniquePathsIII(A, i + 1, j, m, n, cs + 1, steps) + dfsUniquePathsIII(A, i, j + 1, m, n, cs + 1, steps)
		+ dfsUniquePathsIII(A, i - 1, j, m, n, cs + 1, steps) + dfsUniquePathsIII(A, i, j - 1, m, n, cs + 1, steps);
	A[i][j] = 0; //backtrack the point
	return path;
}
int uniquePathsIII(vector<vector<int>> A) {
	int m = A.size(), n = A[0].size(), steps = 0, i1 = 0, j1 = 0;
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			if (A[i][j] == 1) i1 = i, j1 = j; //store starting point
			else if (A[i][j] != -1) steps++;  //store all steps that we can take in the grid...it will include all except '-1' cells

	return dfsUniquePathsIII(A, i1, j1, m, n, 0, steps);
}