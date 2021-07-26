#include "allheaders.h"
#ifdef _MSC_VER
#  include <intrin.h>
#  define __builtin_popcount __popcnt
#endif
using namespace std;
static const int mod = 1e9 + 7;
const int MX = 9999999999;

//failure function for kmp search (memorize it!!)
//vector<int>failureFunction(string s) {
//    int m = s.size(), i = 0, j = 1;
//    vector<int>v(m);
//    v[0] = 0;
//    while (j < m) {
//        if (s[i] == s[j])
//            i++, v[j++] = i;
//        else if (i == 0)
//            v[j++] = 0;
//        else
//            i = v[i - 1];
//    }
//    return v;
//}

//https://leetcode.com/problems/repeated-substring-pattern/
//check if a string s can be constructed by taking a substring of it and appending multiple copies of the substring together.
bool repeatedSubstringPattern(string s) {
    int m = s.size(), i = 0, j = 1;
    vector<int>v(m);
    while (j < m)
        if (s[i] == s[j])  i++, v[j++] = i;
        else if (i == 0) v[j++] = 0;
        else i = v[i - 1];

    return v[m - 1] and v[m - 1] % (m - v[m - 1]) == 0;
}


//remove all occurances of string "part" from string "s"
//string removeOccurrences(string s, string part) {
//    int m = s.size(), n = part.size(), i = 0, j = 0, d = 0;
//    vector<int>idx(m);
//    vector<int>v = failureFunction(part);
//    while (i < m) {
//        s[i - d] = s[i];
//        if (s[i - d] == part[j]) {
//            idx[i - d] = ++j;
//            if (j == n) {
//                d += n;
//                j = i >= d ? idx[i - d] : 0;
//            }
//        }
//        else {
//            if (j != 0) {
//                i--;
//                j = v[j - 1];
//            }
//        }
//        i++;
//    }
//    return s.substr(0, s.size() - d);
//}


//minimum number of steps to make a string palindrome
int minInsertions(string s) {
    int n = s.size(), dp[501][501] = {};
    for (int len = 1; len <= n; len++)
        for (int i = 0; i + len <= n; i++)
            if (s[i] == s[i + len - 1])
                dp[i][i + len] = dp[i + 1][i + len - 1] + (len == 1 ? 1 : 2);
            else
                dp[i][i + len] = max(dp[i + 1][i + len], dp[i][i + len - 1]);
    return n - dp[0][n];
}

//https://leetcode.com/problems/strong-password-checker/
int strongPasswordChecker(string s) {
    int n = s.size();
    int missing = 3;
    for (auto c : s)
        if (islower(c)) {
            missing--; break;
        }
    for (auto c : s)
        if (isupper(c)) {
            missing--; break;
        }
    for (auto c : s)
        if (isdigit(c)) {
            missing--; break;
        }
    int changes = 0, one = 0, two = 0, i = 2;
    while (i < n) {
        if (s[i] == s[i - 1] and s[i - 1] == s[i - 2]) {
            int len = 2;
            while (i < n and s[i] == s[i - 1])
                len++, i++;
            changes += len / 3;
            if (len % 3 == 0) one++;
            else if (len % 3 == 1) two += 1;
        }
        else i++;
    }

    if (n < 6) return max(missing, 6 - n);
    else if (n <= 20) return max(missing, changes);
    else {
        int todelete = n - 20;
        changes -= min(todelete, one);
        changes -= min(max(todelete - one, 0), 2 * two) / 2;
        changes -= max(todelete - one - 2 * two, 0) / 3;
        return todelete + max(missing, changes);
    }
    return 0;
}

//decode the string to alphabet string

int splitString(string s) {
    function<bool(long long, int, int)> dfs = [&](long long prev, int idx, int cnt) {
        if (idx == s.size()) return cnt > 1;
        long long num = 0;
        for (int i = idx; i < s.size(); i++) {
            num = num * 10l + s[i] - '0';
            if (num > MX) break;
            if (prev - num == 1 or prev == -1) {
                if (dfs(prev, i + 1, cnt + 1))
                   return true;
            }
            if (num > prev and prev != -1)
                break;
        }
        return false;
    };

    if (s.size() <= 1) return false;
    return dfs(-1, 0, 0);
}

int decodeWays(string s) {
    int n = s.size(), dp[101] = {};
    dp[0] = 1, dp[1] = s[0] == '0' ? 0 : 1;
    for (int i = 2; i <= n; i++) {
        int a = stoi(s.substr(i - 2, 2));
        int b = stoi(s.substr(i - 1, 1));
        if (a <= 26 and a >= 10)
            dp[i] += dp[i - 2];
        if (b < 10 and b > 0)
            dp[i] += dp[i - 1];
    }
    return dp[n];
}

int countPalindromicSubsequences(string s) {
    int n = s.size();
    const int mod = 1e9 + 7;
    vector<vector<long long>>dp(n, vector<long long>(n));

    for (int i = 0; i < n; i++)
        dp[i][i] = 1;

    for (int len = 1; len < n; ++len) {
        for (int i = 0, j = i + len; j < n; ++i, ++j) {
            if (s[i] != s[j]) {
                dp[i][j] = dp[i + 1][j] + dp[i][j - 1] - dp[i + 1][j - 1];
            }
            else {
                dp[i][j] = 2 * dp[i + 1][j - 1];
                int l = i + 1, r = j - 1;

                while (l <= r and s[l] != s[i]) l++;
                while (l <= r and s[r] != s[i]) r--;

                if (l < r)
                    dp[i][j] -= dp[l + 1][r - 1];
                if (l == r) {
                    dp[i][j]++;
                }
                if (l > r)
                    dp[i][j] += 2;
            }

            dp[i][j] = (dp[i][j] + mod) % mod;
        }
    }
    return dp[0][n - 1];
}

//https://leetcode.com/problems/edit-distance/
//edit distance
int editDistance(string s, string t) {
    int m = s.size(), n = t.size();
    vector<vector<int>>dp(m + 1, vector<int>(n + 1));
    for (int i = 1; i <= m; i++)
        dp[i][0] = i;
    for (int j = 1; j <= n; j++)
        dp[0][j] = j;

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s[i - 1] == t[j - 1])
                dp[i][j] = dp[i - 1][j - 1];
            else
                dp[i][j] = min({ dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1] }) + 1;
        }
    }
    return dp[m][n];
}

int editDistanceOptimised(string s, string t) {
    int m = s.size(), n = t.size();
    vector<int>pre(n + 1), curr(n + 1);
    for (int i = 1; i <= n; i++)
        pre[i] = i;

    for (int i = 1; i <= m; i++) {
        curr[0] = i;
        for (int j = 1; j <= n; j++) {
            if (s[i - 1] == t[j - 1])
                curr[j] = pre[j - 1];
            else
                curr[j] = min({ curr[j - 1], pre[j - 1], pre[j] }) + 1;
        }
        fill(begin(pre), end(pre), 0);
        swap(pre, curr);
    }
    return pre[n];
}