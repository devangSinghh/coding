#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<math.h>
#include "matrix.h"
#include "array.h"
#include "strings.h"
#include <bitset>
#include <unordered_map>
#include <map>

#define all(x) x.begin(), x.end()
using namespace std;
typedef long long ll;
typedef pair<int, int>pii;

typedef vector<int> vi;

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
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	//int T; cin >> T;
	//while (T--) solve();


	return 0;
}