//#include<iostream>
//#include<algorithm>
//#include<vector>
//#include<string>
//#include<math.h>
//#include "matrix.h"
//#include "array.h"
//#include "strings.h"
//#include <bitset>
//#include <unordered_map>
//#include <map>
//#include <numeric>
//#include <deque>

#include<bits/stdc++.h>

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
	//vi v, res;
	//int x, n, a;
	//cin >> x; cin >> n;
	//deque<int>dq;
	//while (n--) {
	//	cin >> a;
	//	v.push_back(a);
	//}
	//n = v.size();
	//for (int i = 0; i < n; i ++) {
	//	while (!dq.empty() && dq.back() > v[i]) dq.pop_back();
	//	dq.push_back(v[i]);
	//	if (i >= x - 1) {
	//		res.push_back(dq.front());
	//		if (v[i - x + 1] == dq.front()) dq.pop_front();
	//	}
	//}

	//cout << *max_element(begin(res), end(res));

	int n, k, mod = 1e9+7; 
	cin >> n;
	cin >> k;

	vector<vi>dp(k+1, vi(n+1));

	if (n < k) cout << 0 << "\n";
	else {
		for (int i = 1; i <= k; i++) {
			for (int j = i; j <= n; j++) {
				if (i == j)
					dp[i][j] = 1;
				else
					dp[i][j] = (dp[i - 1][j - 1] % mod) + (dp[i][j - i] % mod);
			}
		}

		cout << dp[k][n]%mod << "\n";
	}
	
	return 0;
}