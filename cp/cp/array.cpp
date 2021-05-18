#include<iostream>
#include<algorithm>
#include<vector>
#include<math.h>
#include<array>
#include "matrix.h"
#include "array.h"
using namespace std;

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


namespace ARR {
	int main() {

		return 0;
	}
}