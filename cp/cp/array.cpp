#include "allheaders.h"
using namespace std;

/*
useful vector STL functions ::
	v.find(begin(v), end(v), x);
	v.erase(begin(v) + start, begin(s) + end); erase between (start, end)
	unique(begin(v), end(v)); remove duplicates in vector
	sort(begin(v), end(v)); //sorts in ascending order
	sort(begin(v), end(v), greater<>()); //sorts in descending order
	is_sorted_until(begin(v), end(v)); //returns the first **number(not index)** which is not sorted;
	is_sorted_until(begin(v), end(v), greater<>()); //returns the first **number(not index)** which is not sorted in descending order;
	is_sorted(begin(v), end(v)); checks if vector is sorted or not
	upper_bound(begin(v), end(v))
	lower_bound(begin(v), end(v))
	iota(begin(v), end(v), 0) => {0, 1, 2, 3, 4, 5, 6, 7, ...}; used to fill array in increasing fashion
	accumulate(begin(v), end(v), 0); gives sum of elements of array from begin to end . 3rd parameter is the sum starting value
	distance(begin(v), it) gives distance between any 2 iterators of a vector/string

*/

/*
https://leetcode.com/problems/sum-of-floored-pairs/discuss/1210025/Prefix-Sum-Fenwick-Tree-Sort-and-Sieve
*/

/*
_builtin_popcount(n) => used to count the number of 1’s(set bits) in an integer
_builtin_parity(n) => used to check the parity of a number.
__builtin_clz(n) => This function is used to count the leading zeros of the integer
__builtin_ctz(n) => This function is used to count the trailing zeros of the given integer

 f[n] = f[n / 2] + i % 2 , count number of 1s in bit of a number
*/

//range queries using segment tree
class NumArray {
private:
	//time : O(n), space : O(n)
	void buildTree(vector<int>nums) {
		for (int i = n, j = 0; i < 2 * n; i++, j++)
			tree[i] = nums[j];
		for (int i = n - 1; i > 0; i--)
			tree[i] = tree[i * 2] + tree[i * 2 + 1];
	}

public:
	vector<int>tree;
	int n;
	NumArray(vector<int>& nums) {
		if (nums.size() > 0) {
			n = nums.size();
			tree.resize(2 * n);
			buildTree(nums);
		}
	}

	//time : O(logn), there are logn levels, space : O(1)
	void update(int pos, int val) {
		pos += n;
		tree[pos] = val;
		while (pos > 0) {
			int left = pos, right = pos;
			if (pos % 2 == 0) right = pos + 1;
			else left = pos - 1;
			tree[pos / 2] = tree[left] + tree[right];
			pos /= 2;
		}
	}
	//time : O(logn) => on each iteration we move 1 level up, soace : O(1) 
	int sumRange(int l, int r) {
		l += n, r += n;
		int sum = 0;
		while (l <= r) {
			if (l % 2 == 1) sum += tree[l], l++;
			if (r % 2 == 0) sum += tree[r], r--;
			l /= 2, r /= 2;
		}
		return sum;
	}
};

//print a vector
void print(vector<int>A) {
	for (auto x : A) cout << x << " ";
	cout << "\n";
}

//print a 2D vector
void print2DVector(vector<vector<int>>mat) {
	for (auto i : mat) {
		for (auto x : i) cout << x << " ";
		cout << "\n";
	}
}

void printPair(vector<pair<int, int>>v) {
	for (auto pair : v)
		cout << pair.first << " " << pair.second << "\n";
}

void printMap(unordered_map<int, int>u) {
	for (auto c : u)
		cout << "key : " << c.first << " " << "value : " << c.second;
}

auto changesign = [](int n) { n = (~n + 1); };

//get parity of number 
// Parity of a number refers to whether it contains an odd or even number of 1-bits. 
//The number has “odd parity”, if it contains odd number of 1-bits and is “even parity” if it contains even number of 1-bits. 
bool getParity(unsigned int n, bool parity = 0) {
	while (n) parity = !parity, n &= (n - 1);
	return parity;
}


//all numbers of array are occuring even number of times except 1 number. Find that number for eg. [12, 12, 4, 4, 23, 4, 4] ans => 23
int findOddOccuringNumber(vector<int>v) {
	int n = v.size(), res = 0;
	for (auto x : v) res ^= x;
	return res;
}

int dp_pascal[2001][2001] = {};
long long comb(int n, int m) {
	return n == 0 or m == 0 ? 1 :
		dp_pascal[n][m] ? dp_pascal[n][m] : 
			dp_pascal[n][m] = (comb(n - 1, m) + comb(n, m - 1)) % 1000000007;
}

//given day, month, year find weekday 
int sakamoto(int y, int month, int day) {
	static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
	y -= month < 3;
	return (y - y / 4 - y / 100 + y / 400 + t[month - 1] + day) % 7;
}

//kadane algorithm on array
int kadane(vector<int>v) {
	int sum = 0, msum = INT_MIN;
	for (auto n : v)
		sum = max(sum + n, n), msum = max(msum, sum);
	return msum;
}


//number of primes before a number n
vector<int> primesBeforeN(int n) {
	bool* isPrime = new bool[n];
	int number_of_primes = 0;
	for (int i = 2; i < n; i++) 
		isPrime[i] = true;

	for (int i = 0; i*i < n; i++) {
		if (!isPrime[i]) continue; //for every prime number i we're making every instances of its multiple composite ... therefore if number is not prime then continue else proceed forward
		for (int j = i * i; j < n; j+=i) {
			isPrime[j] = false;
		}
	}

	vector<int> res;
	for (int i = 2; i < n; i++) {
		if (isPrime[i]) {
			cout << i << " ";
			number_of_primes++;
			res.push_back(i);
		}
	}
	cout << "\n" << "number of primes before " << n << " : " << number_of_primes;
	return res;
}

vector<int>subarrayBitWiseOr(vector<int>A) {
	int n = A.size(), left = 0, right;
	vector<int>v;
	for (auto x : A) {
		right = v.size();
		v.push_back(x);
		for (int j = left; j < right; j++)
			if (v.back() != (v[j]|x)) v.push_back(v[j]|x); //this line filters out duplicates (to get duplicates just push_back)
		left = right;
	}
	return v;
}

void tower_of_hanoi(int n, char a, char b, char c) {
	if (n == 1) {
		cout << a << " " << c << endl;
		return;
	}
	tower_of_hanoi(n - 1, a, c, b);
	cout << a << " " << c << endl;
	tower_of_hanoi(n - 1, b, a, c);
	return;
}


//given a target, find 2 numbers in array(not equal) whoose sum is equal to target, assuming that solution exists.
pair<int, int> twoSum(vector<int>v, int target) {
	unordered_map<int, int>u; pair<int, int> index;
	for (int i = 0; i < v.size(); i++) u[v[i]] = i; //store all element occurance in map
	for (int i = 0; i < v.size(); i++) {
		auto it = u.find(target - v[i]);
		if (it != u.end()) {						// (target - x) element found in map
			index.first = u[v[i]], index.second = it->second;
		}
	}
	return index;
}

//find all 3 numbers a, b, c a in vector such that a + b + c = target, duplicates pair not allowed
vector<vector<int>>threeSum(vector<int>v, int target) {
	int n = v.size(); vector<vector<int>> pairs;
	sort(begin(v), end(v));
	for (int i = 0; i < n-2; i++) {
		if (i > 0 && v[i] == v[i - 1]) continue;
		int l = i+1, r = n - 1;
		while (l < r) {
			int sum = v[l] + v[r] + v[i];
			if (sum < target) l++;
			else if (sum > target) r--;
			else {
				pairs.push_back(vector<int>{v[l], v[r], v[i]});
				while (l < r - 1 && v[l] == v[l + 1]) l++;
				while (l < r - 1 && v[r] == v[r - 1])r--;
				l++, r--;
			}
		}
	}
	return pairs;
}

//calculate the sum of 3 numbers from vector v, whoose sum is closest to target
int threeSumClosest(vector<int>v, int target) {
	int res = 1e9 + 7, n = v.size();
	sort(begin(v), end(v));

	for (int i = 0; i < n; i++) {
		int l = i + 1, r = n - 1;
		while (l < r) {
			int sum = v[l] + v[r] + v[i];
			if (abs(sum - target) < abs(res - target)) res = sum;
			if (sum < target) l++;
			else r--;
		}
	}
	return res;
}

//given a vector v, return the number just greater than it
//for eg. input => [1, 3, 2] , output => [2, 1, 3] number 213 is just greater than 132
void nextPermutation(vector<int>v) {
	int n = v.size();
	auto it = is_sorted_until(rbegin(v), rend(v));
	if (it != rend(v)) swap(*it, *upper_bound(rbegin(v), it, *it));
	reverse(rbegin(v), it);
	print(v);
}

//given an array of distinct numbers and an integer target, return the number of possible combinations that add up to target
// 1, 2, 1 and 1, 1, 2 are different combinations
int combinationsInArrayAddingToTarget(vector<int>v, int target) {
	vector<unsigned int>dp(target + 1);
	dp[0] = 1;
	for (int sum = 1; sum <= target; sum++)
		for (auto x : v)
			if (sum - x >= 0) dp[sum] += dp[sum - x];
	return dp[target];
}

//rotate array anit-clockwise by k elements
void rotateArrayAntiClockwise(vector<int>v, int k) {
	int n = v.size();
	reverse(begin(v), begin(v) + k%n);
	reverse(begin(v) + k%n, end(v));
	reverse(begin(v), end(v));
	print(v);
}

//rotate array clockwise by k elements
void rotateArrayClockwise(vector<int>v, int k) {
	int n = v.size();
	reverse(begin(v), end(v));
	reverse(begin(v), begin(v) + k % n);
	reverse(begin(v) + k % n, end(v));
	print(v);
}

void rotateArrayOneLiner(vector<int> v, int k) {    //clockwise rotation
	rotate(v.rbegin(), v.rbegin() + k % v.size(), v.rend()), print(v);
}

vector<int>kthRowOfPascalTraingle(int k) {
	int a = 1; vector<int>v;
	for (int i = 1; i <= k + 1; i++) {
		v.push_back(a);
		a = a * (k + 1 - i)/ i;
	}
	print(v);
	return v;
}

//number of paths from (0,0) to end of matrix
int numberOfPathsInMatrix(int m, int n) {
	int path = 1;
	for (int i = n; i < (m + n - 1); i++) {
		path *= i;
		path /= (i - n + 1);
	}
	return path;
}

int numberOfPathsToCellMN(int m, int n) {
	vector<vector<int>>dp(m, vector<int>(n, 0));
	for (int i = 0; i < m; i++)
		dp[i][0] = 1;
	for (int i = 0; i < n; i++)
		dp[0][i] = 1;
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			dp[i][j] = dp[i - 1][j] + dp[i][j - 1]; // + dp[i-1][j-1] if diagonal movement is allowed
	return dp[m - 1][n - 1];
}

int combinationSum4(vector<int>& A, int target) {
	int n = A.size(), cnt = 0;
	vector<int>ways(1000, target + 1);
	ways[0] = 1;
	for (auto &num : A) {
		for (int a = num; a <= target; a++) {
			ways[a] = min(ways[a], ways[a - num] + 1);
			cout << ways[a] << " ";
		}
		cout << "\n";
	}
	return cnt;
}

//Given an integer n, return the count of all numbers with unique digits, x, where 0 <= x < pow(10, n)
//for n =2  ans = 9*9 + 10 , since 10 numbers are unique by default 0..9
//for n = 3 ans = 9*9*8 +  prev. ans.(9*9 + 10) + 10 ...
int countNumbersWithUniqueDigits(int n) {
	int res = 10, available = 9, uniqueDigitCount = 9;
	if (n == 0) return 1;
	for (int i = 0; i < n - 1 && available > 0; i++) {
		uniqueDigitCount *= available;
		res += uniqueDigitCount;
		available--;
	}
	return res;
}

void backTracking(vector<int>&res, vector<int>&temp, vector<int>&A, int target, int s) {
	if (target < 0) return;
	else if (target == 0) {
		res.push_back(temp.size());
	}
	else {
		for (int i = s; i < A.size(); i++) {
			//if (i > s && A[i] == A[i - 1]) continue;
			temp.push_back(A[i]);
			backTracking(res, temp, A, target - A[i], i + 1);
			temp.pop_back();
		}
	}
}

//https://leetcode.com/problems/sliding-window-maximum/submissions/
vector<int>maximumSlidingWindow(vector<int>&A, int k) {
	int n = A.size();
	vector<int>res;
	deque<int>dq;
	for (int i = 0; i < n; i++) {
		while (!dq.empty() and dq.back() < A[i])
			dq.pop_back();
		dq.push_back(A[i]);
		if (i >= k - 1) {
			res.push_back(dq.front());
			if (A[i - k + 1] == dq.front())
				dq.pop_front();
		}
	}
	return res;
}

//Given a string s and an array of strings words, return the number of words[i] that is a subsequence of s
int numMatchingSubseq(string s, vector<string> words) {
	vector<const char* >waiting[128];
	for (auto &w : words)
		waiting[w[0]].push_back(w.c_str());
	for (auto &c : s) {
		auto advance = waiting[c];
		waiting[c].clear();
		for (auto it : advance)
			waiting[*++it].push_back(it);
	}
	return waiting[0].size();
}

//golden ratio method to calculate fibonacci 
int fib(int n) {
	double phi = (1 + sqrt(n)) / 2;
	return round(pow(phi, n) / sqrt(5));
}

//the number of sub-arrays with odd sum
int oddSumSubArrays(vector<int>A) {
	int n = A.size(), odd = 0, even = 0, ans = 0, mod = 1e9+7;
	for (auto n : A) {
		if (n % 2 == 0)
			even++;
		else
			swap(odd, even), odd++;
		ans = (ans + odd) % mod;
	}
	return ans;
}

//https://leetcode.com/problems/arithmetic-slices/
//An integer array is called arithmetic if it consists of at least three elements 
//and the difference between any two consecutive elements is the same.
//find number of arithmatic subarrays of any array for eg. [1, 2, 3, 4] => 3 arithmatic aubarrays which are => [1, 2, 3], [2, 3, 4], [1, 2, 3, 4]
int arithmaticSlices(vector<int> A) {
	int n = A.size(), curr = 0, sum = 0;
	for (int i = 2; i < n; i++) {
		if (long(A[i]) - A[i - 1] == (long)(A[i - 1]) - A[i - 2])
			curr++, sum += curr;
		else
			curr = 0;
	}
	return sum;
}

//An integer array is called arithmetic if it consists of at least three elements 
//and the difference between any two consecutive elements is the same.
//find number of arithmatic **subsequences** of any array 
//int arithmaticSlices2(vector<int> A) {
//	int ans = 0;
//	static int n = A.size();
//	unordered_map<long long, int>u;
//	u.reserve[n];
//
//	for (int i = 0; i < n; i++) {
//		for (int j = 0; j < i; j++) {
//			long long diff = (long)A[i] - A[j];
//			if (u[i].find(diff) != u[i].end()) {
//				ans += u[j][diff];
//				u[i][diff] += u[j][diff];
//			}
//			u[i][diff]++;
//		}
//	}
//	return ans;
//}


//longest strictly increasing subsequence
int longestIncreasingSubsequence(vector<int>A) {
	auto m = begin(A);
	for (auto n : A) {
		auto it = lower_bound(begin(A), m, n);
		*it = n;
		if (it == m)
			m++;
	}
	return m - begin(A);
}


//increasing subsequence of length k such that ... i1 < i2 < i3 < i4 ... < ik and A[i1] < A[i2] < A[i3] ... A[ik]
//https://leetcode.com/problems/increasing-triplet-subsequence/

bool isIncreasingSubSequence(vector<int>A, int k) {
	vector<int>cand(k-1, INT_MAX);
	for (int i = 0; i < A.size(); i++) {
		for (int j = 0; j < k-1; j++) {
			if (A[i] <= cand[j]) {
				cand[j] = A[i];
				break;
			}
			else if (j == k - 2)
				return true;
		}
	}
	return false;
}
//https://leetcode.com/problems/perfect-rectangle/
bool isRectangleCover(vector<vector<int>>A) {
	auto key = [](int x, int y) { return to_string(x) + " " + to_string(y); };
	set<string>s;
	int x1 = INT_MAX, y1 = INT_MAX, x2 = INT_MIN, y2 = INT_MIN, area = 0;
	for (auto c : A) {
		x1 = min(x1, c[0]), y1 = min(y1, c[1]);
		x2 = max(x2, c[2]), y2 = max(y2, c[3]);
		area += (c[2] - c[0]) * (c[3] - c[1]);
		string s1 = key(c[0], c[1]), s2 = key(c[2], c[1]), s3 = key(c[2], c[3]), s4 = key(c[0], c[3]);
		if (!s.erase(s1)) s.insert(s1);
		if (!s.erase(s2)) s.insert(s2);
		if (!s.erase(s3)) s.insert(s3);
		if (!s.erase(s4)) s.insert(s4);

	}
	return s.count(key(x1, y1)) and s.count(key(x2, y1)) and
		s.count(key(x2, y2)) and s.count(key(x1, y2)) and
		s.size() == 4 and area == (x2 - x1) * (y2 - y1);
}

//https://leetcode.com/problems/minimum-number-of-removals-to-make-mountain-array/
//minimum number of removals to make an array a mountain array.
// arr[0] < arr[1] < ... < arr[i - 1] < arr[i] and arr[i] > arr[i + 1] > ... > arr[arr.length - 1] 
int minRemovalsToMakeMountainArray(vector<int>A) {
	int n = A.size(), res = INT_MAX;
	vector<int>l, r, dp(n);
	for (int i = 0; i < n; i++) {
		auto it = lower_bound(begin(l), end(l), A[i]);
		if (it == end(l)) l.push_back(A[i]);
		else *it = A[i];
		dp[i] = l.size();
	}
	for (int i = n - 1; i > 0; i--) {
		auto it = lower_bound(begin(r), end(r), A[i]);
		if (it == end(r)) r.push_back(A[i]);
		else *it = A[i];
		if (dp[i] > 1 and r.size() > 1)
			res = min(res, n - dp[i] - (int)r.size() + 1);
	}
	return res;
}

//https://leetcode.com/problems/subarrays-with-k-different-integers/
//concept : exactly(k) = atMost(k) - atMost(k - 1)
int atMost(vector<int>A, int k) {
	int n = A.size(), j = 0, res = 0;
	unordered_map<int, int>u;
	for (int i = 0; i < n; i++) {
		if (!u[A[i]]++) k--;
		while (k < 0) {
			j++;
			if (!--u[A[j]]) k++;
		}
		res += i - j + 1;
	}
	return res;
}
int subarraysWithKDistinct(vector<int>A, int k) {
	return atMost(A, k) - atMost(A, k - 1);
}

//https://leetcode.com/problems/prison-cells-after-n-days/
vector<int>prisonAfterNDays(vector<int>c, int n) {
	vector<int>fc, next_c(c.size());
	for (int cycle = 0; n-- > 0; c = next_c, cycle++) {
		for (int i = 1; i < c.size() - 1; i++) next_c[i] = c[i - 1] == c[i + 1];
		if (cycle == 0) fc = next_c;
		else if (next_c == fc) n %= cycle;
	}
	return c;
}

//https://leetcode.com/problems/subarray-sums-divisible-by-k/
//number of non-empty subarrays whoose sum is divisible by k
int subarraysDivByK(vector<int>A, int k) {
	int n = A.size(), ans = 0, sum = 0;
	vector<int>count(k);
	count[0] = 1;
	for (auto c : A) {
		sum += c;
		int rem = ((sum % k) + k ) % k; //add k because there are negative numbers
		ans += count[rem];
		count[rem]++;
	}
	return ans;
}

//https://leetcode.com/problems/minimum-adjacent-swaps-for-k-consecutive-ones/
int minMoves(vector<int>nums, int k) {
	vector<long>A, B(1);
	for (int i = 0; i < nums.size(); i++)
		if (nums[i]) A.push_back(i); //all indexes of 1's
	long n = A.size(), res = 2e9 + 7;
	for (int i = 0; i < n; i++)
		B.push_back(B[i] + A[i]); //prefix sum of all indices of 1's
	for (int i = 0; i < n - k + 1; i++)
		res = min(res, B[i + k] - B[k / 2 + i] - B[(k + 1) / 2 + i] + B[i]);
	res -= (k/2) * (k + 1) / 2;
	return res;
}

//XOR queries
vector<int> xorQueries(vector<int>nums, vector<vector<int>>q) {
	int n = size(nums);
	vector<int>pre(n), res;
	for (int i = 1; i < n; i++)
		nums[i] ^= nums[i - 1];
	for (auto c : q) {
		int l = c[0], r = c[1];
		res.push_back(l > 0 ? nums[l - 1] ^ nums[r] : nums[r]);
	}
	return res;
}


//https://leetcode.com/problems/single-number-iii/
//vector<int> singleNumber(vector<int> nums) {
//	unsigned int xr = 0;
//	int a = 0, b = 0;
//	for (auto n : nums) xr ^= n;
//	xr &= -xr;
//	for (auto c : nums)
//		if (xr & c) b ^= c;
//		else a ^= c;
//	return { a, b };
//}

//https://leetcode.com/problems/decode-xored-permutation/
//vector<int> decodeXORedPermutation(vector<int>& A) {
//	int n = A.size() + 1, a = 0;
//	for (int i = 0; i <= n; i++) {
//		a ^= i;
//		if (i < n and i % 2 == 1)
//			a ^= A[i];
//	}
//	vector<int>res = { a };
//	for (int a : A)
//		res.push_back(res.back() ^ a);
//	return res;
//}

//every number in array occurs k times except 1 element. find that element
int singleNumberK(vector<int>& nums, int k = 3) {
	int n = nums.size();
	vector<int>t(32);
	for (int i = 0; i < n; i++) {
		int a = nums[i];
		for (int j = 31; j >= 0; j--) {
			t[j] += a & 1, a >>= 1;
			if (!a) break;
		}
	}
	int res = 0;
	for (int j = 31; j >= 0; j--) {
		int a = t[j] % k;
		if (k) res += 1 << (31 - j);
	}
	return res;
}

//reverse bits of unsigned 32 bit integer
uint32_t reverseBits(uint32_t n) {
	long res = 0;
	for (int i = 0; i < 32; i++)
		res = (res << 1) + ((n >> i) & 1);
	return res;
}

//https://leetcode.com/problems/find-the-duplicate-number/
//floyd's tottoise and hare algorithm
int findDuplicate(vector<int>nums) {
	if (nums.size() > 1) {
		int s = nums[0], f = nums[nums[0]];
		while (s != f) s = nums[s], f = nums[nums[f]];
		f = 0;
		while (s != f) s = nums[s], f = nums[f];
		return s;
	}
	return -1;
}
//https://leetcode.com/problems/single-element-in-a-sorted-array/
//You are given a sorted array consisting of only integers where every element appears exactly twice, except for one element which appears exactly once. 
//Find this single element that appears only once.
int singleNonDuplicate(vector<int>& nums) {
	int n = nums.size(), l = 0, r = n - 1;
	while (l < r) {
		int m = l + (r - l) / 2;
		if (m % 2 == 1) m--;
		if (nums[m] != nums[m + 1]) r = m;
		else l = m + 2;
	}
	return nums[r];
}

//https://leetcode.com/problems/delete-columns-to-make-sorted-ii/submissions/
int minDeletionSize(vector<string>& v) {
	int res = 0, m = v.size(), n = v[0].size(), i, j;
	vector<bool>sorted(m - 1);
	for (j = 0; j < n; j++) {
		for (i = 0; i < m - 1; i++) {
			if (!sorted[i] and v[i][j] > v[i + 1][j]) {
				res++;
				break;
			}
		}
		if (i < m - 1) continue;
		for (i = 0; i < m - 1; i++)
			if (!sorted[i] and v[i][j] < v[i + 1][j])
				sorted[i] = true;
	}
	return res;
}

//to re arrange a sorted array into eg - 123456 = 615243 alternate max and min without using space
//https://www.geeksforgeeks.org/rearrange-array-maximum-minimum-form-set-2-o1-extra-space/
void rearrange(long long* arr, int n) {
	int l = 0, r = n - 1;
	int m = arr[n - 1] + 1;
	for (int i = 0; i < n; i++) {
		if (i % 2 == 0) {
			arr[i] += (arr[r] % m) * m;//this statement stores the elements as multipliers and remainder
			r--;
		}
		else {
			arr[i] += (arr[l] % m) * m;
			l++;
		}
	}
	for (int i = 0; i < n; i++) arr[i] = arr[i] / m;
}

//merge 2 sorted array without extra space O((n+m)log(n+m))
void merge(long long arr1[], long long arr2[], int n, int m) {
	int i = 0, j = 0, k = n - 1;
	while (i <= k && j < m) {
		if (arr1[i] < arr2[j])
			i++;
		else {
			swap(arr1[k--], arr2[j++]);
		}
	}
	sort(arr1, arr1 + n);
	sort(arr2, arr2 + m);
}

//
auto max_element_less_than_k(vector<int>::reverse_iterator s, vector<int>::reverse_iterator e, int k) {
	auto mx = prev(e);
	for (auto it = s; it != e; it++)
		if (*it > *mx and *it < k) mx = it;
	return mx;
}

//used for counting also it is the number of distinct BST formed with n nodes
int catalan_number(int n) {
	vector<int> dp(n + 1, 0);
	dp[0] = 1, dp[1] = 1;
	for (int i = 2; i <= n; i++)
		for (int j = 0; j < i; j++)
			dp[i] += dp[j] * dp[i - j - 1];
	return dp[n];
}

vector<int> spirallyTraverse(vector<vector<int> > matrix, int r, int c) {
	vector<int> res;
	int l = 0, k = 0;
	while (l < r and k < c) {
		for (int i = l; i < c; ++i) {
			res.push_back(matrix[k][i]);
		}
		k++;
		for (int i = k; i < r; ++i) {
			res.push_back(matrix[i][c - 1]);
		}
		c--;
		if (k < r) {
			for (int i = c - 1; i >= l; --i) {
				res.push_back(matrix[r - 1][i]);
			}
			r--;
		}
		if (l < c) {
			for (int i = r - 1; i >= k; --i) {
				res.push_back(matrix[i][l]);
			}
			l++;
		}
	}
	return res;
}


int longestConsecutive(vector<int>& num) {
	unordered_map<int, int> m;
	int r = 0;
	for (int i : num) {
		if (m[i]) continue;
		r = max(r, m[i] = m[i + m[i + 1]] = m[i - m[i - 1]] = m[i + 1] + m[i - 1] + 1);
	}
	return r;
}


string multiple(int n) {
	if (n == 1) return "1";
	vector<int>p(n, -1);
	vector<int>state(n, -1);
	queue<int>q;
	int steps[2] = { 0, 1 };
	q.push(1);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		if (u == 0) break;
		for (auto step : steps) {
			int curr = (u * 10 + step) % n; //this becomes new state
			if (p[curr] == -1) {
				p[curr] = u;
				state[curr] = step;
				q.push(curr);
			}
		}
	}
	print(state);
	string s = "";
	//for (auto c : state)
	//	s += to_string(c);
	return s;
}

//you're given N <= 1e7 numbers, each between 0 and 1e9, how many differnet values will appear in the sequence ? 
int countDifferentValues(vector<int>nums) {
	int n = nums.size();
	bitset<1000000001>visited;
	for(int i = 0; i< n; i++) {
		visited[nums[i]] = true;
	}
	return visited.count();
}


//maximum sum of elements in two non-overlapping (contiguous) subarrays, which have lengths L and M
//L-length subarray could occur before or after the M-length subarray.
int maxSumTwoNoOverlap(vector<int>& arr, int L, int M) {
	int n = arr.size();
	vector<int>pre(n);
	partial_sum(begin(arr), end(arr), begin(pre));
	int res = pre[L + M - 1], Lmax = pre[L - 1], Mmax = pre[M - 1];

	for (int i = L + M; i < n; i++) {
		Lmax = max(Lmax, pre[i - M] - pre[i - L - M]);
		Mmax = max(Mmax, pre[i - L] - pre[i - L - M]);
		res = max(res, max(Lmax + pre[i] - pre[i - M], Mmax + pre[i] - pre[i - L]));
	}
	return res;
}