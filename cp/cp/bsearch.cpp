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