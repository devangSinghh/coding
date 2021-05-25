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

void solve() {
	int a;
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

	return 0;
}