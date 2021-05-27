#include<iostream>
#define NOMINMAX
#include<algorithm>
#undef NOMINMAX
#include <stdlib.h>
#include<vector>
#include<string>
#include<math.h>
#include "matrix.h"
#include "array.h"
#include "strings.h"
#include <bitset>
#include <unordered_map>
#include <map>
#include <numeric>
#include <deque>


//#include<bits/stdc++.h>

#define all(x) x.begin(), x.end()
using namespace std;
typedef long long ll;
typedef pair<int, int>pii;
typedef vector<int> vi;
typedef vector<vector<int>>vii;
typedef unordered_map<int, int> umap;

//void solve() {
//	int a;
//}




int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	vi profit, weights;
	profit = { 60, 100, 120 };
	weights = { 10, 20, 30 };
	int maxprofit = fractionalKnapSack(profit, weights, 50);
	cout << maxprofit;
	return 0;
}