#include "allheaders.h"
#ifdef _MSC_VER
#  include <intrin.h>
#  define __builtin_popcount __popcnt
#endif
using namespace std;
static const int mod = 1e9 + 7;
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

vector<int> countBits(int n) {//dp implementation to count number of 1's in a biary repesentation of a number
	vector<int> res;
	res.push_back(0);
	if (n == 0) {
		return res;
	}
	res.push_back(1);
	for (int k = 2; k <= n; k++) {
		if (k % 2 == 0) {
			res.push_back(res[k / 2]);
		}
		else {
			res.push_back(res[k / 2] + 1);
		}
	}
	return res;
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
				dp[i][j] = max(dp[i][j], dp[index][i] + 1); //new dp will be either sum of previous one which was (index, i) => because these 2 sum upto A[j], or current one...max of 2
				maxLen = max(maxLen, dp[i][j]);
			}
		}
	}

	return maxLen == 0 ? 0 : maxLen + 2;
}


//Given an integer n, return the least number of perfect square numbers that sum to n
//https://en.wikipedia.org/wiki/Lagrange%27s_four-square_theorem
//https://en.wikipedia.org/wiki/Legendre%27s_three-square_theorem
int numSquares(int n) {
	while (n % 4 == 0)
		n /= 4;
	if (n % 8 == 7)
		return 4;
	int a = -1, b = sqrt(n);
	n -= b * b;
	b += b + 1; //making b an odd number (of type 2n + 1)

	while (a <= b) {
		if (n < 0)
			n += b -= 2;
		else if (n > 0)
			n -= a += 2;
		else
			return a < 0 ? 1 : 2;
	}

	return 3;
}

//Given a rectangle of size n x m, find the minimum number of integer - sided squares that tile the rectangle.
int rec(int n, int m) {
	if ((n == 13 and m == 11) || (n == 11 and m == 13)) return 6; //special case
	int mx = 500;
	static vector<vector<int>>dp(15, vector<int>(15, 0));
	if (n == m)
		return 1;
	if (n <= 0 || m <= 0)
		return 0;
	if (dp[n][m] != 0) return dp[n][m];
	int mn = mx;
	for (int i = 1; i <= min(n, m); i++) {
		int r2 = 1 + rec(n - i, m) + rec(i, m - i);
		int r3 = 1 + rec(n, m - i) + rec(n - i, i);
		mn = min(mn, min(r2, r3));
	}
	return dp[n][m] = mn;;
}


//knapsack problems
//time complexity O(2 ^ n), because we have 2 choices at any point of time... either we put the weight or discard it
int knapsackRecursive(vector<int>profit, vector<int>weights, int capacity, int index = 0) {
	if (capacity <= 0 or index >= profit.size())
		return 0;
	int p1 = 0, p2 = 0;
	if (weights[index] <= capacity)
		p1 = profit[index] + knapsackRecursive(profit, weights, capacity - weights[index], index + 1); //we put the weight
	p2 = knapsackRecursive(profit, weights, capacity, index + 1); //we discard the weight
	return max(p1, p2);
}

//weights on row and capacity on column
int knapsackBottomUp(vector<int>profit, vector<int>weights, int capacity) {
	if (capacity <= 0 or profit.empty() or weights.size() != profit.size())
		return 0;
	int n = profit.size();
	vector<vector<int>>dp(n, vector<int>(capacity + 1));

	for (int i = 0; i < n; i++)
		dp[i][0] = 0; //for 0 capacity no weights need to be put, therefore profit 0
	for (int i = 0; i <= capacity; i++) {
		if (weights[0] <= i)
			dp[0][i] = profit[0];
	}

	for (int i = 1; i < n; i++) {
		for (int j = 1; j <= capacity; j++) {
			int p1 = 0, p2 = 0;
			if (weights[i] <= j)
				p1 = profit[i] + dp[i - 1][j - weights[i]]; //we put the weight
			p2 = dp[i - 1][j]; //we discard the weight
			dp[i][j] = max(p1, p2); //taking maximum of 2 conditions
		}
	}

	return dp[n - 1][capacity];
}

//since we only need (i - 1)th while computing therefore spce can be reduced
int knapsackTopDown(vector<int>profit, vector<int>weights, int capacity) {
	if (capacity <= 0 or profit.empty() or weights.size() != profit.size()) //sanity check
		return 0;
	int n = profit.size();
	vector<int>curr(capacity+1, 0);

	for (int i = 0; i < n; i++) {
		for (int c = weights[i]; c <= capacity; c++) {
			curr[c] = max(curr[c-1], profit[i] + curr[c - weights[i]]); //max of (discard the weight, put the weight)
		}
	}
	return curr[capacity];
}

int unboundedKnapsack(vector<int>profit, vector<int>weights, int capacity) {
	if (capacity <= 0 or profit.empty() or weights.size() != profit.size())
		return 0;
	int n = profit.size();
	vector<int>curr(capacity + 1, 0);

	for (int i = 0; i < n; i++) {
		for (int c = weights[i]; c <= capacity; c++) {
			curr[c] = max(curr[c], profit[i] + curr[c - weights[i]]); //max(putting the prev weight multiple times, putting new weight)
		}
	}
	return curr[capacity];
}

int fractionalKnapSack(vector<int>profit, vector<int>weights, int capacity) {
	if (capacity <= 0 or profit.empty() or weights.size() != profit.size())
		return 0;
	int n = profit.size(), w = 0;
	double val = 0.0;
	vector<pair<double, double>>p(n);
	for (int i = 0; i < n; i++)
		p[i] = { weights[i], profit[i] };
	
	sort(begin(p), end(p), [](pair<double, double> a, pair<double, double>b) { return (double)((double)a.second / (double)a.first) > (double)((double)b.second / (double)b.first); });
	for (auto c : p)
		cout << c.first << " " << c.second << "\n";
	for (int i = 0; i < n; i++) {
		if (w + p[i].first <= capacity)
			w += p[i].first, val += p[i].second;
		else {
			double rem = w - capacity;
			val += (double)p[i].second * (double)rem / (double)p[i].first;
			w += rem;
			break;
		}
	}

	return val;
}

bool canMakeEqualSubSets(vector<int>A, int sum , int index) {
	int n = A.size();
	if (sum & 1) return false; //if sum is odd partition is not possible
	if (sum == 0) return true;
	if (index >= n or A.empty()) return false; //sanity check
	if (A[index] <= sum)
		if (canMakeEqualSubSets(A, sum - A[index], index + 1)) //we take the number
			return true;
	return canMakeEqualSubSets(A, sum, index + 1); //we discard that number
}

bool canMakeEqualSubSetsTopDown(vector<vector<int>>dp, vector<int>A, int sum, int index) {
	if (sum == 0) return true;
	if (A.empty() or index >= A.size()) return false; //sanity check
	if (dp[index][sum] == -1)
		if (A[index] <= sum)
			if (canMakeEqualSubSetsTopDown(dp, A, sum - A[index], index + 1)) {
				dp[index][sum] = 1; //memoize
				return true;
			}
	dp[index][sum] = canMakeEqualSubSetsTopDown(dp, A, sum, index + 1) ? 1 : 0; //memoize
	return dp[index][sum] == 1 ? true : false; 
}

//time : 462ms
bool canPartitionBottomUp(vector<int>A) {
	int n = A.size(), sum = accumulate(begin(A), end(A), 0);
	if (sum & 1) return false;
	sum /= 2;
	vector<vector<bool>>dp(n, vector<bool>(sum + 1));
	for (int i = 0; i < n; i++)
		dp[i][0] = true;
	for (int s = 1; s <= sum; s++) {
		dp[0][s] = A[0] == s ? true : false;
	}
	for (int i = 1; i < n; i++) {
		for (int s = 1; s <= sum; s++) {
			if (dp[i - 1][s])
				dp[i][s] = dp[i - 1][s];
			else if (s >= A[i])
				dp[i][s] = dp[i - 1][s - A[i]];
		}
	}
	return dp[n - 1][sum];
}

//time : 12ms
bool partitionUsingBits(vector<int>A) {	
	bitset<10001>bits(1);
	for (auto n : A) bits |= bits << n; //switch on the bit at position n
	int sum = accumulate(begin(A), end(A), 0);
	return !(sum % 2) and bits[sum >> 1];
}

bool canPartition(vector<int>A) {
	int sum = accumulate(begin(A), end(A), 0);
	if (sum % 2 != 0) return false;
	vector<vector<int>>dp(A.size(), vector<int>(sum / 2 + 1, -1));
	return canMakeEqualSubSetsTopDown(dp, A, sum / 2, 0);
}


//Given a set of positive numbers, determine if there exists a subset whose sum is equal to a given number ‘S’.
bool canFindSubSetWithSumS(vector<int>A, int sum) {
	int total = accumulate(begin(A), end(A), 0), n = A.size();
	if (A.empty() or (total == 0 and sum != 0)) return false;
	vector<vector<bool>>dp(n, vector<bool>(sum + 1));
	for (int i = 0; i < n; i++)
		dp[i][0] = true;
	for (int j = 1; j <= sum; j++)
		dp[0][j] = A[0] == j ? true : false;
	for (int i = 1; i < n; i++) {
		for (int s = 1; s <= sum; s++) {
			if (dp[i - 1][s])
				dp[i][s] = dp[i - 1][s];
			else if (A[i] <= s)
				dp[i][s] = dp[i - 1][s - A[i]];
		}
	}
	return dp[n - 1][sum];
}

bool findSubsetWithGivenSum(vector<int>nums, int sum) {
	int n = nums.size();
	bitset<100000000>can;
	for(int i = 0; i < n; i++) {
		can |= (can << nums[i]);
	}
	return can[sum];
}


int shortestPathinMatrix(vector<vector<int>>mat) {
	int m(mat.size()), n(mat[0].size());
	vector<vector<int>>dp(m + 1, vector<int>(n + 1, mat[0][0]));
	for (int i = 1; i < m; i++)
		dp[0][i] += mat[0][i];
	for (int j = 1; j < n; j++)
		dp[j][0] += mat[j][0];
	for (int i = 1; i < m; i++) {
		for (int j = 1; j < n; j++) {
			dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + mat[i][j];
		}
	}
	return dp[m-1][n-1];
}

//Given an integer array nums, return the number of longest increasing subsequences(LIS).
int findNumOfLongestIncreasingSubSequence(vector<int>A) {
	int n = A.size(), maxLen = 0, ans = 0;
	vector<pair<int, int>>dp(n, { 1, 1 }); //pair(count, length)
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < i; j++)
			if (A[i] > A[j])
				if (dp[i].second == dp[j].second + 1)
					dp[i].first += dp[j].first; //cumulatively add the result to bigger index ... i.e. i > j ... so store result of j in i
				else if (dp[i].second < dp[j].second + 1)
					dp[i].second = dp[j].second + 1, dp[i].first = dp[j].first;
		maxLen = max(maxLen, dp[i].second);
	}
	for (auto c : dp)
		if (c.second == maxLen) ans += c.first;
	return ans;
}


//https://www.geeksforgeeks.org/bitmasking-and-dynamic-programming-set-1-count-ways-to-assign-unique-cap-to-every-person/
//Count ways to assign unique cap to every person
long long int waysToAssignCap(int mask, int i, unordered_map<int, vector<int>>capList, vector<vector<int>>dp, int allmask) {
	if (mask == allmask) return 1;
	if (i > 100) return 0;
	if (dp[mask][i] != -1) return dp[mask][i]; //if solution already present
	long long int ways = waysToAssignCap(mask, i + 1, capList, dp, allmask); //exculde current cap
	int persons = capList[i].size(); //number of persons wearing cap with id of 'i'
	for (int j = 0; j < persons; j++) {
		if (mask & (1 << capList[i][j])) continue; //if jth person is already wearing cap continue
		else
			ways += waysToAssignCap(mask | (1 << capList[i][j]), i + 1, capList, dp, allmask);
		ways %= (int)(1e9 + 7);
	}
	return dp[mask][i] = ways;
}


//https://leetcode.com/problems/cherry-pickup-ii/
int CherryPickUpdp[70][70][70] = {};
int dfs(vector<vector<int>>&A, int r, int c, int k, int m, int n) {
	if (r == m) return 0; //if we reached at the bottom of matrix
	if (CherryPickUpdp[r][c][k] != -1) return CherryPickUpdp[r][c][k];
	int ans = 0;
	for (int c1 = -1; c1 <= 1; c1++) // j-1, j, j + 1 => for robot 1
		for (int c2 = -1; c2 <= 1; c2++) { // for robot 2
			int nc = c + c1, nk = k + c2;
			if (nc >= 0 and nc < n and nk < n and nk >= 0)
				ans = max(ans, dfs(A, r + 1, nc, nk, m, n));
		}

	ans += c == k ? A[r][c] : A[r][c] + A[r][k];
	return CherryPickUpdp[r][c][k] = ans;
}
int cherryPickup(vector<vector<int>>& A) {
	memset(CherryPickUpdp, -1, sizeof(CherryPickUpdp));
	int m = A.size(), n = A[0].size();
	return dfs(A, 0, 0, n - 1, m, n);
}

//max sum of subsequence in array which is divisible by k
int maxDivK(vector<int>A, int k) {
	if (k == 0) return -1;
	vector<int>dp(k, 0);
	for (auto n : A) {
		vector<int> temp = dp;
		for (int i = 0; i < k; i++) {
			dp[(n + temp[i]) % k] = max(dp[(n + temp[i]) % k], n + temp[i]);
		}
	}
	return dp[0];
}


//https://leetcode.com/problems/minimum-difficulty-of-a-job-schedule/
int dfsMinDifficultyJobSchedule(int d, int len, vector<int>&jobDifficulty, vector<vector<int>>&dp) {
	int n = jobDifficulty.size();
	if (d == 0 and len == n) return 0;
	if (d == 0 or len == n) return INT_MAX;
	if (dp[len][d] != -1) return dp[len][d];
	int curMax = jobDifficulty[len];
	int mn = INT_MAX;
	for (int s = len; s < n; s++) {
		curMax = max(curMax, jobDifficulty[s]);
		int temp = dfsMinDifficultyJobSchedule(d - 1, s + 1, jobDifficulty, dp);
		if (temp != INT_MAX)
			mn = min(mn, temp + curMax);
	}

	return dp[len][d] = mn;
}
int minDifficulty(vector<int>& jobDifficulty, int d) {
	int n = jobDifficulty.size();
	if (n < d) return -1;
	vector<vector<int>>dp(n, vector<int>(d + 1, -1));
	return dfsMinDifficultyJobSchedule(d, 0, jobDifficulty, dp);
}


//https://leetcode.com/contest/biweekly-contest-29/problems/parallel-courses-ii/
int minNumberOfSemesters(int n, vector<vector<int>> relations, int k) {
	vector<int>pre(n);
	for (auto& c : relations) {
		c[0] -= 1, c[1] -= 1;
		pre[c[1]] |= (1 << c[0]);
	}
	vector<int>dp(1 << n, n);
	dp[0] = 0;
	for (int i = 0; i < (1 << n); i++) {
		int ex = 0;
		for (int j = 0; j < n; j++)
			if ((i & pre[j]) == pre[j])
				ex |= (1 << j);
		ex &= ~i;
		for (int s = ex; s; s = (s - 1) & ex)
			if (__builtin_popcount(s) <= k)
				dp[i | s] = max(dp[i | s], dp[i] + 1);
	}
	return dp.back();
}

//https://leetcode.com/problems/minimum-number-of-days-to-eat-n-oranges/
//first eat n % 2 oranges then swallow n/2 ... or n % 3 oranges then swallow n / 3 oranges
unordered_map<int, int>dpForMinDays;
int minDays(int n) {
	if (n <= 1) return n;
	if (dpForMinDays.count(n) == 0)
		dpForMinDays[n] = 1 + min(n % 2 + minDays(n / 2), n % 3 + minDays(n / 3));
	return dpForMinDays[n];
}

//https://leetcode.com/problems/paint-house-iii/
//paint-house-III
int dppH3[101][101][21] = {};
int dfsPaintHouseIII(vector<int>& houses, vector<vector<int>>& cost, int i, int target, int last_clr) {
	if (i >= houses.size() or target < 0)
		return target == 0 ? 0 : 1000001;
	if (houses[i]) return dfsPaintHouseIII(houses, cost, i + 1, target - (last_clr != houses[i]), houses[i]);
	if (dppH3[i][target][last_clr]) return dppH3[i][target][last_clr];
	int res = 1000001;
	for (size_t clr = 1; clr <= cost[i].size(); ++clr)
		res = min(res, cost[i][clr - 1] + dfsPaintHouseIII(houses, cost, i + 1, target - (last_clr != clr), clr));
	return dppH3[i][target][last_clr] = res;
}
int minCostPaintHouseIII(vector<int>& houses, vector<vector<int>>& cost, int m, int n, int target) {
	int res = dfsPaintHouseIII(houses, cost, 0, target, 0);
	return res > 1000000 ? -1 : res;
}

//https://leetcode.com/problems/count-all-possible-routes/
//Return the count of all possible routes from start to finish.
int dpCountRoutes[201][101] = {};
int countRoutes(vector<int>A, int s, int e, int fuel) { //A=>locations, s = starting point, e = ending point, fuel =>initial fuel
	int n = A.size();
	if (!dpCountRoutes[s][fuel]) {
		dpCountRoutes[s][fuel] = 1 + (s == e); //when we've reached the destination
		for (int j = 0; j < n; j++) {
			if (s != j and fuel >= abs(A[s] - A[j]))
				dpCountRoutes[s][fuel] = (dpCountRoutes[s][fuel] + countRoutes(A, j, e, fuel - abs(A[s] - A[j]))) % mod;
		}
	}
	return dpCountRoutes[s][fuel] - 1;
}

//add 2 numbers without addition
int getSum(int a, int b) {
	int xr = a ^ b;
	int carry = a & b;
	if (carry == 0) return xr;
	carry = (carry & 0xffffffff) << 1;
	return getSum(xr, carry);
}

//number of sub-strings in "s" and "t" differing by 1 element
int SubstringsdifferbyOne(string s, string t) {
	auto helper = [&](string s, string t, int i, int j) {
		int m = s.size(), n = t.size(), res = 0, pre = 0, curr = 0;
		while (i < m and j < n) {
			curr++;
			if (s[i++] != t[j++])
				pre = curr, curr = 0;
			res += pre;
		}
		return res;
	};

	int ans = 0;
	for (int i = 0; i < s.size(); i++)
		ans += helper(s, t, 0, i);
	for (int j = 1; j < t.size(); j++)
		ans += helper(s, t, j, 0);
	return ans;
}



//https://leetcode.com/problems/super-egg-drop/
//https://leetcode.com/problems/egg-drop-with-2-eggs-and-n-floors/discuss/1248069/Recursive-Iterative-Generic
//super egg drop
int superEggDrop(int k, int n) {
	int m = 0;;
	vector<int>dp(k + 1);
	for (m = 0; dp[k] < n; m++)
		for (int x = k; x > 0; x--)
			dp[x] += dp[x - 1] + 1;
	return m;
}

//optimal strategy game to pick stones from ends
//print the maximum difference of scores
//final dp[0] represents difference in scores. 
int stoneGame(vector<int>nums) {
	int n = nums.size();
	vector<int>dp = nums;
	for (int range = 1; range < n; range++)
		for (int i = 0; i < n - range; i++)
			dp[i] = max(nums[i] - dp[i + 1], nums[i + range] - dp[i]);
	return dp[0];
}

//beautiful arrangement
//arrangement => perm => i % perm[i] == 0 or perm[i] % i == 0 
//perm consists of numbers from [1, n]
int countArrangement(int n) {
	int seen = 0, ans = 0;
	function<void(int)> dfs = [&](int idx) {
		if (idx == 0) {
			ans++;
			return;
		}
		for (int i = n; i >= 1; i--) {
			if ((seen & (1 << i)) == 0 and (i % idx == 0 or idx % i == 0)) {
				seen ^= (1 << i);
				dfs(idx - 1);
				seen ^= (1 << i);
			}
		}
	};
	dfs(n);
	return ans;
}

//https://leetcode.com/problems/k-concatenation-maximum-sum/
int kConcatenationMaxSum(vector<int>& nums, int k) {
	int n = nums.size(), sum = nums[0], msum = nums[0];
	int64_t total = accumulate(begin(nums), end(nums), 0), mod = 1e9 + 7;
	for (long long i = 1; i < n * min(k, 2); i++) {
		sum = max(nums[i % n], sum + nums[i % n]);
		msum = max(msum, sum);
	}
	return max<int64_t>({ 0, msum, total * max(0, k - 2) + msum }) % mod;
}

//https://leetcode.com/problems/largest-divisible-subset/
vector<int> largestDivisibleSubset(vector<int>& nums) {
	sort(begin(nums), end(nums));
	int n = nums.size(), ans = INT_MIN, idx = 0;
	vector<int>dp(n, 1), parent(n, -1), res;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < i; j++)
			if(nums[i] % nums[j] == 0 and dp[i] < dp[j] + 1) {
				dp[i] = dp[j] + 1;
				parent[i] = j;
			}

		if (dp[i] > ans)
			ans = dp[i], idx = i;
	}
	while (idx != -1) {
		res.push_back(nums[idx]); 
		idx = parent[idx];
	}

	return res;
}


//longest mountain subarray
int longestMountain(vector<int>& arr) {
	int n = arr.size(), longest = 0, i = 1;
	while (i < n) {
		int up = 0, down = 0;
		while (i < n and arr[i - 1] == arr[i]) i++;
		while (i < n and arr[i - 1] < arr[i]) i++, up++;
		while (i < n and arr[i - 1] > arr[i]) i++, down++;
		if(up > 0 and down > 0)
			longest = max(longest, up + down + 1);
	}
	return longest;
}

//https://leetcode.com/problems/maximum-subarray-sum-with-one-deletion/
int maximumSum(vector<int>& arr) {
	int n = arr.size(), no_delete = arr[0], on_delete = 0, msum = arr[0];
	for (int i = 1; i < n; i++) {
		on_delete = max(on_delete + arr[i], no_delete);
		no_delete = max(no_delete + arr[i], arr[i]);
		msum = max(msum, max(on_delete, no_delete));
	}
	return msum;
}

//https://leetcode.com/problems/guess-number-higher-or-lower-ii/
int getMoneyAmount(int n) {
	int dp[201][201] = {}, maximum = INT_MAX;
	function<int(int, int)> minmax = [&](int lower, int upper) {
		if (lower >= upper) return 0;
		if (dp[lower][upper] != 0)
			return dp[lower][upper];
		for (int i = lower; i <= upper; i++)
			maximum = min(maximum, max(minmax(lower, i - 1), minmax(i + 1, upper)) + i);
		return dp[lower][upper] = maximum;
	};
	return minmax(1, n);
}

//number of submatrices with all 1s in a matrix

//O(m^2N^2)
int numSubmatBruteForce(vector<vector<int>>& mat) {
	int m = mat.size(), n = mat[0].size(), ans = 0;

	auto count = [&](int a, int b) {
		int bound = n, res = 0;
		for (int i = a; i < m; i++) {
			for (int j = b; j < bound; j++) {
				if (mat[i][j]) res++;
				else bound = j;
			}
		}
		return res;
	};

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++)
			ans += count(i, j);
	}
	return ans;
}

//O(mn) using stack
int numSubmatOptimal(vector<vector<int>>& mat) {
	int m = mat.size(), n = mat[0].size(), ans = 0;
	vector<int>h(n);
	auto count = [](vector<int>v) {
		int sz = v.size(), res = 0;
		stack<int>stk;
		vector<int>sum(sz);
		for (int i = 0; i < sz; i++) {
			while (!stk.empty() and v[stk.top()] >= v[i])
				stk.pop();
			if (!stk.empty()) {
				int preindex = stk.top();
				sum[i] = sum[preindex];
				sum[i] += v[i] * (i - preindex);
			}
			else sum[i] = v[i] * (i + 1);
		}
		for (int s : sum) res += s;
		return res;
	};
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++)
			h[j] = mat[i][j] == 0 ? 0 : h[j] + 1;
		ans += count(h);
	}
	return ans;
}

//burst ballons
int maxCoins(vector<int>& A) {
	if (A.empty()) {
		return 0;
	}
	const int n = A.size();
	vector<vector<int>>dp(n, vector<int>(n));

	for (int L = n - 1; L >= 0; L--) {
		for (int R = L; R < n; R++) {
			for (int i = L; i <= R; i++) {
				dp[L][R] = max(dp[L][R],
					A[i] * (L ? A[L - 1] : 1) * (R == n - 1 ? 1 : A[R + 1])
					+ (i - 1 >= L ? dp[L][i - 1] : 0) + (i + 1 <= R ? dp[i + 1][R] : 0));
			}
		}
	}
	return dp[0][n - 1];
}

//https://leetcode.com/problems/minimum-cost-to-merge-stones/
int mergeStones(vector<int>& A, int k) {
	int n = A.size();
	if ((n - 1) % (k - 1)) return -1;
	vector<int>pre(n + 1);
	vector<vector<int>>dp(n, vector<int>(n));
	for (int i = 1; i <= n; i++)
		pre[i] = pre[i - 1] + A[i - 1];

	for (int m = k; m <= n; m++) {
		for (int i = 0; i + m <= n; i++) {
			int j = i + m - 1;
			dp[i][j] = INT_MAX;
			for (int mid = i; mid < j; mid += k - 1)
				dp[i][j] = min(dp[i][j], dp[i][mid] + dp[mid + 1][j]);
			if ((j - i) % (k - 1) == 0)
				dp[i][j] += pre[j + 1] - pre[i];
		}
	}
	return dp[0][n - 1];
}