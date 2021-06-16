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

void printMap(unordered_map<int, int>u) {
	for (auto it = begin(u); it != end(u); it++) cout << it->first << " " << it->second << "\n";
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