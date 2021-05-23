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

	accumulate(begin(v), end(v), 0); gives sum of elements of array from begin to end . 3rd parameter is the sum starting value
	distance(begin(v), it) gives distance between any 2 iterators of a vector/string

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
}

int gcd(int a, int b) {
	return b == 0 ? a : gcd(b, a%b);
}

//print a 2D vector
void print2DVector(vector<vector<int>>mat) {
	for (auto &i : mat) {
		for (auto x : i) cout << x << " ";
		cout << "\n";
	}
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
		if (!isPrime[i]) continue;
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

	for (int sum = 1; sum <= target; sum++) {
		for (auto x : v) {
			if (sum - x >= 0) dp[sum] += dp[sum - x];
		}
	}

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
		a = a*(k - i + 1)/ i;
	}
	print(v);
	return v;
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


//number of paths from (0,0) to end of matrix
int numberOfPathsInMatrix(int m, int n) {
	int path = 1;
	for (int i = n; i < (m + n - 1); i++) {
		path *= i;
		path /= (i - n + 1);
	}
	return path;
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

//Given a string s and an array of strings words, return the number of words[i] that is a subsequence of s
int numMatchingSubseq(string s, vector<string> words) {
	vector<const char* >waiting[128];

	for (auto &w : words)
		waiting[w[0]].push_back(w.c_str());

	for (auto &c : s) {
		auto advance = waiting[c];
		waiting[c].clear();

		for (auto it : advance) {
			waiting[*++it].push_back(it);
		}
	}

	return waiting[0].size();
}

//golden ratio method to calculate fibonacci 
int fib(int n) {
	double phi = (1 + sqrt(n)) / 2;
	return round(pow(phi, n) / sqrt(5));
}

namespace ARR {
	int main() {

		return 0;
	}
}