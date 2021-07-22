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

int minSumOfLengthsGeneral(vector<int>& arr, int tar) {
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

//https://leetcode.com/problems/reverse-pairs/
int reversePairs(vector<int>& nums) {
	function<int(int, int)> merge_sort = [&](int l, int r) {
		if (l >= r) return 0;
		int m = l + (r - l) / 2;
		int count = merge_sort(l, m) + merge_sort(m + 1, r);
		for (int j = m + 1; j <= r; j++) {
			auto it = upper_bound(begin(nums) + l, begin(nums) + m + 1, 2L * nums[j]);
			int d = distance(begin(nums) + l, it);
			if (d > m) break;
			count += m - l + 1 - d;
		}
		inplace_merge(begin(nums) + l, begin(nums) + m + 1, begin(nums) + r + 1);
		return count;
	};
	return merge_sort(0, nums.size() - 1);
}

//https://leetcode.com/problems/nth-magical-number/
//int nthMagicalNumber(int n, int a, int b) {
//	long lcm = a * b / __gcd(a, b), l = 2, r = 1e14, mod = 1e9 + 7;
//	while (l < r) {
//		long m = (l + r) / 2;
//		if (m / a + m / b - m / lcm < n) l = m + 1;
//		else r = m;
//	}
//	return l % mod;
//}

//https://leetcode.com/problems/median-of-two-sorted-arrays/
double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
	int n1 = nums1.size(), n2 = nums2.size(), l = 0, r = 2 * n2;
	if (n1 < n2) return findMedianSortedArrays(nums2, nums1);
	while (l <= r) {
		int m2 = (l + r) / 2, m1 = n1 + n2 - m2;
		double l1 = m1 == 0 ? INT_MIN : nums1[(m1 - 1) / 2];
		double l2 = m2 == 0 ? INT_MIN : nums2[(m2 - 1) / 2];
		double r1 = m1 == 2 * n1 ? INT_MAX : nums1[m1 / 2];
		double r2 = m2 == 2 * n2 ? INT_MAX : nums2[m2 / 2];
		if (l1 > r2) l = m2 + 1;
		else if (l2 > r1) r = m2 - 1;
		else return (max(l1, l2) + min(r1, r2)) / 2;
	}
	return -1;
}

//https://leetcode.com/problems/count-of-range-sum/
//int countRangeSum(vector<int>& nums, int lower, int upper) {
//
//}

//https://leetcode.com/problems/fair-candy-swap/
vector<int> fairCandySwap(vector<int>& A, vector<int>& B) {
	unordered_set<int>set(begin(A), end(A));
	int diff = (accumulate(begin(A), end(A), 0) - accumulate(begin(B), end(B), 0)) / 2;
	for (auto n : B) if (set.count(n + diff)) return { n + diff, n };
	return { 0, 0 };
}

//https://leetcode.com/problems/kth-missing-positive-number/
int findKthPositive(vector<int>& nums, int k) {
	int l = 0, r = nums.size();
	while (l < r) {
		int m = (l + r) / 2;
		if (nums[m] - 1 - m < k) l = m + 1;
		else r = m;
	}
	return l + k;
}

//https://leetcode.com/problems/intersection-of-two-arrays-ii/
vector<int> setIntersectionII(vector<int>& nums1, vector<int>& nums2) {
	unordered_map<int, int> u;
	vector<int>res;
	for (auto n : nums1) u[n]++;
	for (auto n : nums2)
		if (u.count(n) and u[n])
			u[n]--, res.push_back(n);
	return res;
}

//https://leetcode.com/problems/find-a-peak-element-ii/
vector<int> findPeakGrid(vector<vector<int>>& mat) {
	int row_size = mat.size(), n = mat[0].size(), l = 0, r = n - 1;
	while (l <= r) {
		int m = l + (r - l) / 2, max_row = 0;
		for (int i = 0; i < row_size; i++)
			max_row = mat[max_row][m] < mat[i][m] ? i : max_row;
		int curr = mat[max_row][m], left = -1, right = -1;
		if (m > 0) left = mat[max_row][m - 1];
		if (m < n - 1) right = mat[max_row][m + 1];
		if (curr > left and curr > right) return { max_row, m };
		else if (curr < right) l = m + 1;
		else r = m - 1;
	}
	return {};
}

//https://leetcode.com/problems/maximum-distance-between-a-pair-of-values/
int maxDistance(vector<int>& A, vector<int>& B) {
	int m = A.size(), n = B.size(), i = 0, j = 0, mx = 0;
	while (i < m and j < n)
		if (A[i] > B[j]) i++;
		else mx = max(mx, j++ - i);
	return mx;
}

//https://leetcode.com/problems/most-profit-assigning-work/
int maxProfitAssignment(vector<int>& diff, vector<int>& profit, vector<int>& worker) {
	int n = diff.size(), p = 0, i = 0, mx_profit = 0;
	vector<pair<int, int>>v;
	for (int i = 0; i < n; i++) v.push_back({ diff[i], profit[i] });
	sort(begin(v), end(v)), sort(begin(worker), end(worker));
	for (auto w : worker) {
		while (i < n and w >= v[i].first)
			mx_profit = max(mx_profit, v[i++].second);
		p += mx_profit;
	}
	return p;
}

//https://leetcode.com/problems/number-of-subsequences-that-satisfy-the-given-sum-condition/
int numSubseq(vector<int>& nums, int target) {
	long n = nums.size(), mod = 1e9 + 7, ans = 0, l = 0, r = n - 1;
	vector<int>pre(n, 1);
	for (int i = 1; i < n; i++)
		pre[i] = (pre[i - 1] * 2) % mod; //precomputing to avoid overflow
	sort(begin(nums), end(nums));
	while (l <= r) {
		if (nums[l] + nums[r] <= target) ans = (ans + pre[r - l++]) % mod;
		else r--;
	}
	return ans % mod;
}


//https://leetcode.com/problems/shortest-subarray-to-be-removed-to-make-array-sorted/
//Given an integer array arr, remove a subarray (can be empty) from arr such that the remaining elements in arr are non-decreasing.
//Return the length of the shortest subarray to remove
int findLengthOfShortestSubarray(vector<int>& nums) {
	int n = nums.size(), i = 0, j = n - 1, minlen = INT_MAX;
	for (j = n - 1; j > 0; j--)
		if (nums[j - 1] > nums[j]) break;
	if (j == 0) return 0;
	minlen = j;
	for (int i = 0; i < n; i++) {
		if (i > 0 and nums[i - 1] > nums[i]) break;
		while (j < n and nums[i] > nums[j]) j++;
		minlen = min(minlen, j - i - 1);
	}
	return minlen;
}

//https://leetcode.com/problems/search-in-rotated-sorted-array-ii/
//search in array (array contains duplicates)
bool searchRotatedSortedArray(vector<int>& nums, int t) {
	int n = nums.size(), l = 0, r = n - 1;
	while (l < r) {
		int m = l + (r - l) / 2;
		if (nums[m] == t) return true;
		if (nums[l] < nums[m])
			if (t >= nums[l] and t < nums[m]) r = m - 1;
			else l = m + 1;
		else if (nums[m] < nums[r])
			if (t > nums[m] and t <= nums[r]) l = m + 1;
			else r = m - 1;
		else
			if (nums[l] == nums[m]) l++;
			else if (nums[r] == nums[m]) r--;
	}
	return nums[l] == t ? true : false;
}

//https://leetcode.com/problems/frequency-of-the-most-frequent-element/
int maxFrequency(vector<int>A, long k) {
	int n = A.size(), i = 0, j = 0;
	sort(begin(A), end(A));
	for (i = 0; i < n; i++) {
		k += A[i];
		if (k < (long)(i - j + 1) * A[i])
			k -= A[j++];
	}
	return i - j;
}

//https://leetcode.com/problems/maximum-number-of-removable-characters/
int maximumRemovals(string s, string p, vector<int>& re) {
	int n = re.size(), l = 0, r = n;
	auto isSubsequence = [](string s1, string s2) {
		char* s = &s1[0], * t = &s2[0];
		for (; *t; s += *s == *t++);
		return !*s;
	};
	while (l <= r) {
		int m = (l + r) / 2;
		string letters = s;
		for (int i = 0; i < m; i++) letters[re[i]] = '/';
		if (isSubsequence(p, letters)) l = m + 1;
		else {
			for (int i = 0; i < m; i++) letters[re[i]] = s[re[i]];
			r = m - 1;
		}
	}
	return r;
}

//https://leetcode.com/problems/ways-to-split-array-into-three-subarrays/
int waysToSplit(vector<int>& nums) {
	int n = nums.size(), ans = 0, mod = 1e9+7;
	partial_sum(begin(nums), end(nums), begin(nums));
	for (int i = 0, j = 0, k = 0; i < n - 2; i++) {
		j = max(i + 1, j);
		while (j < n - 1 and nums[j] < nums[i] * 2) j++;
		k = max(j, k);
		while (k < n - 1 and nums[k] - nums[i] <= nums[n - 1] - nums[k]) k++;
		ans = (ans + j - i) % mod;
	}
	return ans;
}


int kth_matrix_bound(vector<vector<int>>mat, int k) {
	int m = mat.size(), n = mat.size();
	int l = mat[0][0], r = mat[m - 1][n - 1];
	while (l < r) {
		int m = l + (r - l) / 2, j = n - 1, cnt = 0;

		for (int i = 0; i < m; i++) {
			while (j >= 0 and mat[i][j] > m)
				j--;
			cnt += (j + 1);
		}
		if (cnt < k)
			l = m + 1;
		else
			r = m;
	}
	return l;
}

vector<int> kthSmallestPrimeFraction(vector<int>& arr, int k) {
	int n = arr.size();
	double l = 0.0, r = 1.0;

	while (l < r) {
		double m = (l + r) / 2;
		double max_f = 0.0;
		int total = 0, p = 0, q = 0, j = 1;
		for (int i = 0; i < n - 1; i++) {
			while (j < n and arr[i] > m * arr[j])
				j++;
			total += (n - j);
			if (j == n)
				break;

			double f = static_cast<double>(arr[i]) / arr[j];
			if (f > max_f) {
				p = i, q = j, max_f = f;
			}
		}

		if (total == k)
			return { arr[p], arr[q] };
		else if (total < k)
			l = m;
		else
			r = m;
	}
	return {};
}