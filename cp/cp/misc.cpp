#include "allheaders.h"
using namespace std;
//https://leetcode.com/problems/maximum-product-of-word-lengths/
int maxProduct(vector<string>words) {
	unordered_map<int, int>u;
	for (auto word : words) {
		int mask = 0;
		for (auto c : word)
			mask |= 1 << (c - 'a');
		u[mask] = max(u[mask], (int)word.size());
	}
	int res = 0;
	for (auto a : u)
		for (auto b : u)
			if (!(a.first & b.first))
				res = max(res, a.second * b.second);
	return res;
}

//
int findMaximumXOR(vector<int>nums) {
	int mx = 0, mask = 0;
	for (int i = 31; i >= 0; i--) {
		mask |= (1 << i);
		unordered_set<int>set;
		for (auto& num : nums)
			set.insert(mask & num);
		int greedyTry = mx | (1 << i);
		for(auto c : set) 
			if (set.count(c ^ greedyTry)) {
				mx = greedyTry;
				break;
			}
	}
	return mx;
}

//euler toteint function
//1 1 2 2 4 2 6 4 ... 
long long int phi(int n) {
	long long int count = 1;
	for (int i = 2; i < n; i++) {
		if (gcd(i, n) == 1)
			count++;
	}
	return count;
}