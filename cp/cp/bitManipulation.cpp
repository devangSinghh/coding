#include "allheaders.h"
#ifdef _MSC_VER
#  include <intrin.h>
#  define __builtin_popcount __popcnt
#endif
using namespace std;
const int INF = 1e9;


//time complexity => O(32)
int divideIntegers(int A, int B) {
    if (A == INT_MIN and B == -1) return INT_MAX;
    if (A == INT_MIN and B == 1) return INT_MIN;
    unsigned a = abs(A), b = abs(B);
    int res = 0;
    for (int x = 31; x >= 0; x--) {
        if (a >> x >= b) {
            a = a - (b << x);
            res += (1 << x);
        }
    }
    return (A > 0) == (B > 0) ? res : -res;
}


//number of subsets with XOR value k
int subsetXOR(vector<int> arr, int n, int k) {
    int mx = *max_element(arr.begin(), arr.end());
    int m = (1 << (int)(log2(mx) + 1)) - 1;
    if (k > m) return 0;

    vector<vector<int>>dp(n + 1, vector<int>(m + 1));
    dp[0][0] = 1;

    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= m; j++)
            dp[i][j] = dp[i - 1][j] + dp[i - 1][j ^ arr[i - 1]];

    return dp[n][k];
}

//set the rightmost unset bit
int rightMostUnsetBit(int n) {
    return ((n & (n + 1)) == 0) ? n : (n | (n + 1));
}

//cutting binary string => return minimum number of cuts "c" such that every part is power of 5
int cuts(string s) {
    int n = s.size();

    auto ok = [](unsigned long long int n) {
        long long a = log(n) / log(5);
        return pow(5, a) == n;
    };

    vector<long long int> dp(n + 1);
    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        dp[i] = INT_MAX;
        for (int j = 1; j <= i; j++) {
            if (s[j - 1] == '0') continue;
            string a = s.substr(j - 1, i - j + 1);
            unsigned long long int num = bitset<64>(a).to_ullong();
            if (ok(num))
                dp[i] = min(dp[i], dp[j - 1] + 1);
        }
    }
    return dp[n] == INT_MAX ? -1 : dp[n];
}