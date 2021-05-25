#include "allheaders.h"
using namespace std;

#define all(x) x.begin(), x.end()
using namespace std;
typedef long long ll;
typedef pair<int, int>pii;
typedef vector<int> vi;
typedef vector<vector<int>>vii;

//cf contest 2 q-1
void minSlidingWindow() {
	vi v, res;
	int x, n, a;
	cin >> x; cin >> n;
	deque<int>dq;
	while (n--) {
		cin >> a;
		v.push_back(a);
	}
	n = v.size();
	for (int i = 0; i < n; i++) {
		while (!dq.empty() && dq.back() > v[i]) dq.pop_back();
		dq.push_back(v[i]);
		if (i >= x - 1) {
			res.push_back(dq.front());
			if (v[i - x + 1] == dq.front()) dq.pop_front();
		}
	}

	cout << *max_element(begin(res), end(res));
}

//cf-contest-2 q-2
//each group is sorted and dose'nt have fewer number than previous
void divide_a_NumberN_in_k_groups_every_gorup_in_sorted_order() {
	int n, k, mod = 1e9 + 7;
	cin >> n;
	cin >> k;

	vector<vi>dp(k + 1, vi(n + 1));

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

		cout << dp[k][n] % mod << "\n";
	}
}