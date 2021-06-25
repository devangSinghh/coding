#include "allheaders.h"
using namespace std;
//https://leetcode.com/problems/range-sum-of-sorted-subarray-sums/
int rangeSum(vector<int>& nums, int n, int left, int right) {
	vector<int>v;
	for (int i = 0; i < n; i++) {
		int sum = 0;
		for (int j = i; j < n; j++)
			sum += nums[j], v.push_back(sum);
	}
	nth_element(begin(v), begin(v) + left - 1, end(v));
	nth_element(begin(v) + left, begin(v) + right, end(v));
	return accumulate(begin(v) + left - 1, begin(v) + right, 0, [](int a, int b) {
		return (a + b) % 1000000007;
	});
}

//https://leetcode.com/problems/minimum-limit-of-balls-in-a-bag/
int minimumSize(vector<int>& nums, int k) {
	int l = 1, r = 1e9;
	while (l < r) {
		int m = l + (r - l) / 2, count = 0;
		for (auto a : nums) count += (a - 1) / m;
		if (count > k) l = m + 1;
		else r = m;
	}
	return r;
}

//https://leetcode.com/problems/maximum-side-length-of-a-square-with-sum-less-than-or-equal-to-threshold/
int maxSideLength(vector<vector<int>>& mat, int t) {
	int m = mat.size(), n = mat[0].size(), l = 0, r = min(m, n), len = 1, ans = 0;
	vector<vector<int>>pre(m + 1, vector<int>(n + 1));
	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= n; j++) {
			pre[i][j] = pre[i - 1][j] + pre[i][j - 1] - pre[i - 1][j - 1] + mat[i - 1][j - 1];
			if (i >= len and j >= len and pre[i][j] - pre[i - len][j] - pre[i][j - len] + pre[i - len][j - len] <= t)
				ans = len++;
		}
	return ans;
}

//https://leetcode.com/problems/maximum-length-of-repeated-subarray/
//Given two integer arrays nums1 and nums2, return the maximum length of a subarray that appears in both arrays.
int findLength(vector<int>& A, vector<int>& B) {
	int m = A.size(), n = B.size(), ans = 0;
	vector<int>pre(m + 1), curr(n + 1);
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			if (A[i - 1] == B[j - 1])
				curr[j] = pre[j - 1] + 1, ans = max(ans, curr[j]);
		}
		fill(begin(pre), end(pre), 0);
		swap(pre, curr);
	}
	return ans;
}

//https://leetcode.com/problems/search-a-2d-matrix-ii/submissions/
bool searchMatrix(vector<vector<int>>& mat, int target) {
	int i = 0, j = mat[0].size() - 1;
	while (i < mat.size() and j >= 0)
		if (mat[i][j] == target) return true;
		else if (mat[i][j] < target) i++;
		else j--;

	return false;
}

//https://leetcode.com/problems/find-k-closest-elements/
vector<int> findClosestElements(vector<int>& arr, int k, int x) {
	int n = arr.size(), l = 0, r = n - k;
	while (l < r) {
		int m = l + (r - l) / 2;
		if (x - arr[m] > arr[m + k] - x) l = m + 1;
		else r = m;
	}
	vector<int>res;
	copy(begin(arr) + l, begin(arr) + l + k, back_inserter(res));
	return res;
}

//https://leetcode.com/problems/reach-a-number/
int reachNumber(int target) {
	target = abs(target);
	int steps = 0, sum = 0;
	while (sum < target) sum += ++steps;
	while (abs(sum - target) % 2 != 0) sum += ++steps;
	return steps;
}

//https://leetcode.com/problems/k-diff-pairs-in-an-array/
int findPairs(vector<int>& nums, int k) {
	unordered_map<int, int>u;
	int ans = 0;
	for (auto n : nums) u[n]++;
	for (auto c : u)
		if ((!k and c.second > 1) or (k and u.count(c.first + k))) ++ans;
	return ans;
}

int minSumOfLengths(vector<int>& arr, int tar) {
	int n = arr.size(), cursum = 0;
	int dp[100005][3];  //if asking for n subarrays, change 3 to n+1
	unordered_map<int, int> sm;  // keep track of (prefixsum : index)
	sm[0] = 0;
	memset(dp, 127, sizeof(dp));  //initialize to INF
	for (int i = 0; i < 100005; i++) dp[i][0] = 0;  //if we doesn't find a subarray, len = 0

	for (int i = 1; i <= n; i++) {
		int d = -1;  //initialize to -1
		cursum += arr[i - 1];
		sm[cursum] = i;
		if (sm.count(cursum - tar)) d = sm[cursum - tar];

		for (int j = 1; j <= 2; j++) {  // if asking for n subarrays, change 2 to n
			dp[i][j] = min(dp[i][j], dp[i - 1][j]);  //dp[i][j] must <= dp[i-1][j]
			if (d != -1) dp[i][j] = min(dp[i][j], dp[d][j - 1] + i - d);
		}
	}
	if (dp[n][2] > 1e9) return -1;   // if asking for n subarrays, change 2 to n
	return dp[n][2];   // if asking for n subarrays, change 2 to n
}

//https://leetcode.com/problems/find-two-non-overlapping-sub-arrays-each-with-target-sum/
int minSumOfLengths(vector<int>& nums, int target) {
	int n = nums.size(), j = 0, sum = 0, INF = 1e9 + 7, ans = INF, minLen = INF;
	vector<int>dp(n, INF);
	for (int i = 0; i < n; i++) {
		sum += nums[i];
		while (j < i and sum > target)
			sum -= nums[j++];
		if (sum == target) {
			if (j > 0 and dp[j - 1] != INF)
				ans = min(ans, dp[j - 1] + i - j + 1);
			minLen = min(minLen, i - j + 1);
		}
		dp[i] = minLen;
	}
	return ans == INF ? -1 : ans;
}