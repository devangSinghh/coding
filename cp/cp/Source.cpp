#include<iostream>
#define NOMINMAX
#include<algorithm>
#undef NOMINMAX
#include <stdlib.h>
#include<vector>
#include<string>
#include<sstream>
#include<math.h>
#include<regex>
#include "matrix.h"
#include "array.h"
#include "graph.h"
#include "strings.h"
#include <bitset>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <numeric>
#include <deque>
#include <list>
#include <set>
#include <iterator>
#include <queue>
//#include<bits/stdc++.h>
#define all(x) x.begin(), x.end()
using namespace std;
typedef long long ll;
typedef pair<int, int>pii;
typedef vector<int> vi;
typedef vector<pair<int, int>> vpii;
typedef vector<vector<int>>vii;
typedef unordered_map<int, int> umap;
const int inf = INT_MAX;
const int n_inf = INT_MIN;
const int mod = 1e9 + 7;
#pragma GCC optimize("Ofast")
static const auto fast = []() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);
	return 0;
} ();

int stoneGame1(vector<int>nums) {
	int n = nums.size();
	vector<int>dp = nums;
	for (int range = 1; range < n; range++) {
		for (int i = 0; i < n - range; i++)
			dp[i] = max(nums[i] - dp[i + 1], nums[i + range] - dp[i]);
	}
	return dp[0];
}

int dp[2001][2001] = {};
long comb(int n, int k) {
	return n == 0 or k == 0 ? 1 :
		dp[n][k] ? dp[n][k] :
		dp[n][k] = (comb(n - 1, k) + comb(n, k - 1)) % mod;
}

int main() {

	vi a = { 2, 4, 5,1 ,4 ,11, 22, 97, 153, 2 };
	vi pre = { a[0] };
	int xr = 0;
	for (auto c : a)
		xr ^= c;
	cout << xr;

}