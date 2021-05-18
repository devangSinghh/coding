#include "allheaders.h"
using namespace std;

//print a vector
void print(vector<int>A) {
	for (auto x : A) cout << x << " ";
}

//print a 2D vector
void print2DVector(vector<vector<int>>mat) {
	for (auto &i : mat) {
		for (auto x : i) cout << x << " ";
		cout << "\n";
	}
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

//rotate array anit-clockwise by k elements
void rotateArrayAntiClockwise(vector<int>v, int k) {
	int n = v.size();
	reverse(begin(v), begin(v) + k%n);
	reverse(begin(v) + k%n, end(v));
	reverse(begin(v), end(v));
	print(v);
}

void rotateArrayClockwise(vector<int>v, int k) {
	int n = v.size();
	reverse(begin(v), end(v));
	reverse(begin(v), begin(v) + k % n);
	reverse(begin(v) + k % n, end(v));
	print(v);
}

void rotateArrayOneLiner(vector<int> v, int k) {
	rotate(v.rbegin(), v.rbegin() + k % v.size(), v.rend());
}

namespace ARR {
	int main() {

		return 0;
	}
}