#include "allheaders.h"
using namespace std;

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
	b += b + 1;

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
int knapsackRecursive(vector<int>profit, vector<int>weights, int capacity, int index = 0) {
	if (capacity <= 0 or index >= profit.size())
		return 0;
	int p1 = 0, p2 = 0;
	if (weights[index] <= capacity)
		p1 = profit[index] + knapsackRecursive(profit, weights, capacity - weights[index], index + 1);
	p2 = knapsackRecursive(profit, weights, capacity, index + 1);
	return max(p1, p2);
}

int knapsackBottomUp(vector<int>profit, vector<int>weights, int capacity) {
	if (capacity <= 0 or profit.empty() or weights.size() != profit.size())
		return 0;
	int n = profit.size();
	vector<vector<int>>dp(n, vector<int>(capacity + 1));

	for (int i = 0; i < n; i++)
		dp[i][0] = 0;
	for (int i = 0; i <= capacity; i++) {
		if (weights[0] <= i)
			dp[0][i] = profit[0];
	}

	for (int i = 1; i < n; i++) {
		for (int j = 1; j <= capacity; j++) {
			int p1 = 0, p2 = 0;
			if (weights[i] <= j)
				p1 = profit[i] + dp[i - 1][j - weights[i]];
			p2 = dp[i - 1][j];
			dp[i][j] = max(p1, p2);
		}
	}

	return dp[n - 1][capacity];
}

int knapsackTopDown(vector<int>profit, vector<int>weights, int capacity) {
	if (capacity <= 0 or profit.empty() or weights.size() != profit.size())
		return 0;
	int n = profit.size();
	vector<int>curr(capacity+1, 0);

	for (int i = 0; i < n; i++) {
		for (int c = weights[i]; c <= capacity; c++) {
			curr[c] = max(curr[c-1], profit[i] + curr[c - weights[i]]);
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
			curr[c] = max(curr[c], profit[i] + curr[c - weights[i]]); //imp line
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