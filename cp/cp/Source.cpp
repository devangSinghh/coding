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



void solve() {
	int a;
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

int EachcountBits(int n) {// count number of 1's in a biary repesentation of a number
    int count = 0;
    while (n) {
        n = n & (n - 1);
        count++;
    }
    return count;
}

int Unboundedknapsack(vector<int>& weights, vector<int>& values, int capacity) {
    int n= weights.size();
    int dp[capacity+1];
    memset(dp,0,sizeof(dp));
    for(int i=0;i<=capacity;i++){
        for(int j=0;j<n;j++){
            if(weights[j]<=i){
               dp[i]=max(dp[i],values[j]+dp[i-weights[j]]);
            }
            
        }
    }
    return dp[capacity];
}

void tower_of_hanoi(int n,char a,char b, char c){
    if(n==1){
        cout<<a<<" "<<c<<endl;
        return;
    }
    tower_of_hanoi(n-1,a,c,b);
    cout<<a<<" "<<c<<endl;
    tower_of_hanoi(n-1,b,a,c);
    return;
    
}

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