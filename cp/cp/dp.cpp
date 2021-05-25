#include "allheaders.h"
using namespace std;

int Unboundedknapsack(vector<int> weights, vector<int> values, int capacity) {
	int n = weights.size();
	vector<int>dp(capacity + 1, 0);
	for (int i = 0; i <= capacity; i++) {
		for (int j = 0; j < n; j++) {
			if (weights[j] <= i) {
				dp[i] = max(dp[i], values[j] + dp[i - weights[j]]);
			}

		}
	}
	return dp[capacity];
}

/*
Given an array nums of integers, return the length of the longest arithmetic subsequence in nums.
subsequence of an array nums is a list nums[i1], nums[i2], ..., nums[ik] with 0 <= i1 < i2 < ... < ik <= nums.length - 1,
and that a sequence 'seq' is arithmetic if seq[i+1] - seq[i] are all the same value (for 0 <= i < seq.length - 1)
for eg . [20, 1, 15, 3, 10, 5, 8] => [20, 15, 10, 5] (ans)
for eg . [9, 4, 7, 2, 10] => [4, 7, 10]
for eg . [3, 6, 9, 12] => [3, 6, 9, 12]
*/
int longestArithSeqLength(vector<int>& A) {
	int n = A.size(), ans = 0;
	vector<vector<int>>dp(n, vector<int>(2000, 0));
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			int d = A[j] - A[i] + 1000;
			dp[j][d] = max(dp[i][d] + 1, 2);
			ans = max(ans, dp[j][d]);
		}
	}
	return ans;
}

int coinChange(vector<int>& coins, int amount) {
	vector<int> need(amount + 1, amount + 1);
	need[0] = 0;
	for (int c : coins) {
		for (int a = c; a <= amount; a++) {
			need[a] = min(need[a], need[a - c] + 1);
			cout << need[a] << " ";
		}
		cout << "\n";
	}
	return need.back() > amount ? -1 : need.back();
}

//longest fibonacci type subsequence
int lenLongestFibSubseq(vector<int> A) {
	int n = A.size(), index = 0, maxLen = 0;

	if (n < 3) return 0;

	vector<vector<int>>dp(n + 1, vector<int>(n + 1, 0));
	unordered_map<int, int>u;

	for (int i = 0; i < n; i++) u[A[i]] = i; //populate the map 

	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			int k = A[j] - A[i]; //find a number k such that k + A[i] = A[j]  ...and index of k should be smaller than i

			auto it = u.find(k); // find for k in map
			if (it != u.end()) index = u[k]; //if k exists store it's index in 'index'
			else index = -1; //if k is not found then index = -1

			if (index != -1 && index < i) { //check if k is present and its index is less than i
				dp[i][j] = max(dp[i][j], dp[index][i] + 1); //new dp will be either sum of previous one which was (index, i) => because these 2 sum upto A[j, or current one..max of 2
				maxLen = max(maxLen, dp[i][j]);
			}
		}
	}

	return maxLen == 0 ? 0 : maxLen + 2;
}