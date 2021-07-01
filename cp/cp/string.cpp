#include "allheaders.h"
#ifdef _MSC_VER
#  include <intrin.h>
#  define __builtin_popcount __popcnt
#endif
using namespace std;
const int inf = INT_MAX;

void printVectorString(vector<string>s) {
	for (auto c : s) cout << c << " ";
	cout << "\n";
}

//if a string is palindrome
bool checkPalindrome(string s) {
	return equal(begin(s), end(s), rbegin(s));
}

//whether a string 's' ends with string 't'
//bool ends_with(string value, string ending) {
//	if (ending.size() > value.size()) return false;
//	return equal(ending.rbegin(), ending.rend(), value.rbegin());
//}

bool ends_with(string s, string t) {
	if (t.size() > s.size())
		return false;
	return equal(rbegin(t), rend(t), rbegin(s));
}

//check if string s1 is subsequence of s2 (the function is effective even if s1 is of order 1e9)
bool checkSubSequence(string s1, string s2) {
	char *s = &s1[0], *t = &s2[0];
	for (; *t; s += *s == *t++);
	return !*s;
}


//count number of n-length strings made out of only vowels('a', 'e', 'i', 'o', 'u') O(Nk) time, O(k) space
//k = 5 since vowels are only 5
int countVowelStrings(int n) {
	vector<int> dp = { 0, 1, 1, 1, 1, 1 };
	for (int i = 1; i <= n; i++)
		for (int k = 1; k <= 5; k++)
			dp[k] += dp[k - 1], cout << dp[k] << " ";
	return dp[5];
}

int countVowelStringsByCombinations(int n) {
	return (n + 1)*(n + 2)*(n + 3)*(n + 4) / 24;  //n+4C4 pick up 4 places from (n+4) places
}

//adding 2 binary strings
string addTwoBinaryStrings(string a, string b) {
	string s = "";
	int carry = 0, i = a.size() - 1, j = b.size() - 1;
	while (i >= 0 || j >= 0 || carry == 1) {
		carry += i >= 0 ? a[i--] - '0' : 0;
		carry += j >= 0 ? b[j--] - '0' : 0;
		s += char(carry%2 + '0'), carry /= 2;
	}
	reverse(begin(s), end(s));
	return s;
}

//Given a string s, return the longest palindromic substring in s
// for eg : s = "babad" output => "bab"
// for eg : s = "ac" output => "a"
// for eg : s = "a" output => "a"
string longestPalindrome(string s) {
	if (s.size() < 2) return s;
	int len = 0, start = 0;

	for (int i = 0; i < s.size();) {
		if (s.size() - i <= len / 2) break;
		int l = i, r = i;
		while (r < s.size() - 1 && s[r] == s[r + 1]) r++;
		i = r + 1;

		while (r < s.size() - 1 && l > 0 && s[l - 1] == s[r + 1])
			l--, r++;

		if (r - l + 1 > len)
			start = l, len = r - l + 1;
	}
	return s.substr(start, len);
}

//Given a string s, find the length of the longest substring without repeating characters.
// s = "pwwkew" answer => "wke", answer will not be "pwke" because it is a subsequence not a substring
int lengthOfLongestSubstring(string s) {
	vector<int>dict(256, -1);
	int start = -1, maxLen = 0;
	for (int i = 0; i < s.size(); i++) {
		if (dict[s[i]] > start)
			start = dict[s[i]];

		dict[s[i]] = i;
		maxLen = max(maxLen, i - start);
	}
	return maxLen;
}

void grayCode(int n) {
	for (int i = 0; i < (1 << n); i++) {
		cout << "number : " << (i ^ (i >> 1)) << " ";
		string k = bitset<16>(i ^ (i >> 1)).to_string();
		k.erase(begin(k), begin(k) + 16 - n);
		cout << "gray code : " << k << "\n";
	}
}

vector<vector<bool>>visitedWord;
 bool searchForThisWord(vector<vector<char>>board, string word, int i, int j, int index) {
	if (index == word.length()) return true;
	if (i < 0 || j < 0 || i >= board.size() || j >= board[i].size() || board[i][j] != word[index] || visitedWord[i][j])
		return false;
	visitedWord[i][j] = true;
	if (searchForThisWord(board, word, i - 1, j, index + 1) || (board, word, i + 1, j, index + 1) || (board, word, i, j - 1, index + 1)
		|| (board, word, i, j + 1, index + 1))
		return true;
	visitedWord[i][j] = false;
	return false;
}

//search a word in a 2D board , return whether it exists or not
bool searchWord(vector<vector<char>>board, string word) {
	visitedWord.resize(board.size(), vector<bool>(board[0].size()));

	for(int i = 0; i < board.size(); i++)
		for (int j = 0; j < board[0].size(); j++)
			if (board[i][j] == word[0] && searchForThisWord(board, word, i, j, 0)) return true;
	cout << "searching";
		return false;
}


int titleToNumber(string A) {
	int n = A.size(), sum = 0;
	for (int i = 0; i < n; i++)
		sum += pow(26, n - 1 - i)*(A[i] - 'A' + 1);
	return sum;
}

vector<int>failureFunction(string w) {
	int i = 0, j = 1, m = w.size();
	vector<int>v(m);
	v[0] = 0;
	while (j < m)
		if (w[i] == w[j])
			i++, v[j++] = i;
		else if (i == 0)
			v[j++] = 0;
		else
			i = v[i - 1]; //mismatch --> backtrack
	return v;
}

//KMP algorithm for searching substring w, in string s in O(m + n) time
bool kmpSearch(string w, string s) {
	int i = 0, j = 0, m = w.size(), n = s.size();
	vector<int>arr = failureFunction(w);
	while (i < m and j < n) {
		if (w[i] == s[j] and i == m - 1) //substring found
			return true;
		else if (w[i] == s[j])
			i++, j++;
		else
			if (i != 0)
				i = arr[i - 1];
			else
				j++;
	}
	return false;
}

//Given a string s, return the number of palindromic substrings in it.
int countPalinDromeSubstrings(string s) {
	int n = s.size();
	if (n == 0) return 0;

}


//O(n)
//https://www.educative.io/edpresso/longest-palindromic-substring-in-on-with-manachers-algorithm
void lengthOfLongestPalindromeSubString(string s) {
	for (int i = 0; i < s.size(); i++)
		s.insert(i++, "#");
	s += '#';
	int n = s.size(), C = 0, R = 0;
	vector<int>lps(n, 0);

	for (int i = 0; i < n; i++) {
		int mirror = 2 * C - i;
		if (R > i)
			lps[i] = min(R - i, lps[mirror]);
		else
			lps[i] = 0;
		try {
				while (i + 1 + lps[i] < n and i - 1 - lps[i] >= 0 and i - 1 - lps[i] < n and i + 1 + lps[i] >= 0 and s[i + 1 + lps[i]] == s[i - 1 - lps[i]]) {
					lps[i] += 1;
				}
		}
		catch (int i) {
			cout << "exception" << "\n";
		}
		if (i + lps[i] > R)
			C = i, R = i + lps[i];
	}
	auto it = max_element(begin(lps), end(lps));
	int r = *it, c = it - begin(lps);
	for (int i = c - r; i < c + r; i++)
		if (s[i] == '#') s[i] = (char)0;
	cout << r << " " << c << "\n";
	cout << s << "\n"; 
}

//https://leetcode.com/problems/longest-valid-parentheses/
//Given a string containing just the characters '(' and ')', 
//find the length of the longest valid (well-formed) parentheses substring.
//eg. s = "(()" ans => 2, s = ")()())" ans => 4
int longestValidParentheses(string s) {
	stack<int>stk;
	int maxLen = 0;
	stk.push(-1);
	for (int i = 0; i < s.size(); i++) {
		int top = stk.top();
		if (top != -1 and s[i] == ')' and s[top] == '(')
			stk.pop(), maxLen = max(maxLen, i - stk.top());
		else
			stk.push(i);
	}
	return maxLen;
}

//https://leetcode.com/problems/ambiguous-coordinates/
vector<string>ambiguousCoordinatesCases(string &&s) {
	vector<string>res{ s };
	if (s.size() == 1) return {};
	if (s.front() == '0') { //0xxxx
		if (s.back() == '0') return {};//0xxxx0
		return { "0." + s.substr(1) };
	}
	if (s.back() == '0') return { s }; //xxxx0
	for (int i = 1; i < s.size(); i++)
		res.emplace_back(s.substr(0, i) + '.' + s.substr(i)); //all possible combinations where decimal can be placed
	return res;
}
vector<string>ambiguousCoordinates(string s) {
	vector<string>res;
	for (int i = 2; i < s.size() - 1; i++)
	for(auto &a : ambiguousCoordinatesCases(s.substr(1, i - 1)))
	for(auto &b : ambiguousCoordinatesCases(s.substr(i, s.size() - i - 1)))
		res.push_back("(" + a + ", " + b + ")");
	return res;
}

//https://leetcode.com/problems/concatenated-words/
//Given an array of strings words (without duplicates), return all the concatenated words in the given list of words
bool wordIsForming(string s, unordered_set<string>& Set) {
	if (Set.empty()) return false;
	vector<bool>dp(s.size() + 1);
	dp[0] = 1;
	for (int i = 1; i <= s.size(); i++) {
		for (int j = i - 1; j >= 0; j--) {
			if (dp[j]) {
				string word = s.substr(j, i - j);
				if (Set.find(word) != end(Set)) {
					dp[i] = true;
					break;
				}
			}
		}
	}
	return dp[s.size()];
}
vector<string>findAllConcatenatedWordsInADict(vector<string>words) {
	sort(begin(words), end(words), [](auto a, auto b) { return a.size() < b.size(); });
	unordered_set<string>Set;
	vector<string>res;
	for (auto word : words) {
		if (wordIsForming(word, Set))
			res.push_back(word);
		Set.insert(word);
	}
	return res;
}

//wildcard matching
bool wildcardMatching(string s, string p) {
	int m = s.length(), n = p.length();
	int i = 0, j = 0, asterisk = -1, match;
	while (i < m) {
		if (j < n and p[j] == '*')
			match = i, asterisk = j++;
		else if (j < n and (s[i] == p[j] or p[j] == '?'))
			i++, j++;
		else if (asterisk >= 0)
			i = ++match, j = asterisk + 1;
		else return false;
	}
	while (j < n and p[j] == '*') j++;
	return j == n;
}

//regular expression matching
bool regexMatch(string s, string p) {
	int m = s.size(), n = p.size();
	vector<vector<bool>>dp(m + 1, vector<bool>(n + 1));
	dp[0][0] = true;
	for (int i = 0; i < n; i++)
		if (p[i] == '*' and dp[0][i - 1])
			dp[0][i + 1] = true;
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			if (p[j - 1] == s[i - 1] or p[j - 1] == '.')
				dp[i][j] = dp[i - 1][j - 1];
			else if (p[j - 1] == '*') {
				if (s[i - 1] == p[j - 2] or p[j - 2] == '.')
					dp[i][j] = dp[i - 1][j] or dp[i][j - 1] or dp[i][j - 2];
				else
					dp[i][j] = dp[i][j - 2];
			}
			else dp[i][j] = false;
		}
	}
	return dp[m][n];
}


//https://leetcode.com/problems/longest-duplicate-substring/submissions/
//Rabin-karp and binary search
string longestDupSubstring(string s) {
	const int p = INT_MAX / 26 / 26 * 26 - 1; // = 82595499
	int l = 0, r = s.size(), idx = 0;
	while (r - l > 1) {
		int m = l + (r - l) / 2, pow = 1, h = 0;
		for (int i = m - 1; i >= 0; i--) {
			h += (s[i] - 'a') * pow, h %= p;
			pow *= 26, pow %= p;
		}
		unordered_multimap<int, int>h2i = { {h, 0} };
		auto i = 0;
		for (; i + m < s.size(); i++) {
			h *= 26, h %= p;
			h += (s[i + m] - 'a') - (s[i] - 'a') * pow, h %= p;
			h += p, h %= p;
			auto its = h2i.equal_range(h);
			auto it = its.first;
			for (; it != its.second; ++it) {
				auto j = i + 1, k = it->second;
				for (; j < i + m; ++j, ++k)
					if (s[j] != s[k]) break;
				if (j == i + m) break;
			}
			if (it != its.second) break;
			h2i.insert({ h, i + 1 });
		}
		if (i + m < s.size())
			l = m, idx = i + 1;
		else r = m;
	}
	return s.substr(idx, l);
}
//https://leetcode.com/problems/remove-all-occurrences-of-a-substring/
//remove occurances of substrings from string
string removeOccurrencesRecursive(string& s, string part) {
	//string t;
	//for (int i = 0; i < s.size(); i++) {
	//	t += s[i];
	//	if (t.size() >= 3 and t.substr(t.length() - 3, 3) == "abc")
	//		t = t.substr(0, t.length() - 3);
	//}
	//return t;
	return s.find(part) != string::npos ? removeOccurrencesRecursive(s = regex_replace(s, regex(part), ""), part) : s;
}

//https://leetcode.com/problems/shuffle-string/
//cyclic sort
string restoreString(string s, vector<int>& indices) {
	for (int i = 0; i < indices.size(); i++)
		while (indices[i] != i)
			swap(s[i], s[indices[i]]), swap(indices[i], indices[indices[i]]);
	return s;
}
//https://leetcode.com/problems/fraction-to-recurring-decimal/
string fractionToDecimal(int num, int den) {
	if (!num) return "0";
	string s;
	if (num > 0 ^ den > 0) s += "-";
	long n = labs(num), d = labs(den), r = n % d;
	s += to_string(n / d);
	if (!r) return s;
	s += ".";
	unordered_map<int, int>u;
	while (r) {
		if (u.count(r) > 0) {
			s.insert(u[r], "(");
			s += ")";
			break;
		}
		u[r] = s.size();
		r *= 10;
		s += to_string(r / d);
		r %= d;
	}
	return s;
}

//https://leetcode.com/problems/decoded-string-at-index/
string decodeAtIndex(string s, int k) {
	long n = s.size(), sz = 0;
	for (int i = 0; i < n; i++) {
		if (isdigit(s[i])) sz *= s[i] - '0';
		else sz++;
	}
	for (int i = n - 1; i >= 0; i--) {
		k %= sz;
		if (k == 0 and isalpha(s[i])) return string(1, s[i]);
		if (isdigit(s[i])) sz /= s[i] - '0';
		else sz--;
	}
	return s.substr(k, 1);
}

//https://leetcode.com/problems/split-two-strings-to-make-palindrome/
bool checkPalindromeFormation(string a, string b) {
	auto isPalindrome = [](string s, int i, int j) {
		while (i < j and s[i] == s[j])
			i++, j--;
		return i >= j;
	};
	auto check = [&](string a, string b) {
		int l = 0, r = a.size() - 1;
		while (l < r and a[l] == b[r]) l++, r--;
		return isPalindrome(a, l, r) or isPalindrome(b, l, r);
	};
	return check(a, b) or check(b, a);
}

//https://leetcode.com/problems/largest-number/
string largestNumber(vector<int>& nums) {
	sort(begin(nums), end(nums), [](auto m, auto n) {
		long a(m), b(n);
		int i(10), j(10);
		while (m /= 10) i *= 10;
		while (n /= 10) j *= 10;
		return a * j + b > b * i + a;
		});
	if (!nums[0]) return "0";
	string s;
	for (auto n : nums) s += to_string(n);
	return s;
}

//https://leetcode.com/problems/number-of-wonderful-substrings/
int get_hash(char& c) {
	return 1 << (c - 'a');
}
long long wonderfulSubstrings(string word) {
	int count[1 << 10] = { 1 };
	int running = 0;
	long long res = 0;
	for (auto& c : word) {
		running ^= get_hash(c);
		for (char ch = 'a'; ch <= 'j'; ch++)
			res += count[running ^ get_hash(ch)];
		res += count[running];
		count[running] ++;
	}
	return res;
}

//https://leetcode.com/problems/can-make-palindrome-from-substring/
vector<bool> canMakePaliQueries(string s, vector<vector<int>>& queries) {
	int mask = 0;
	vector<int>ps(1);
	for (auto c : s)
		ps.push_back(mask ^= 1 << (c - 'a'));
	vector<bool>ans;
	for (auto q : queries) {
		int l = q[0], r = q[1], k = q[2];
		int odds = __builtin_popcount(ps[r + 1] ^ ps[l]);
		ans.push_back(odds / 2 <= k);
	}
	return ans;
}

//https://leetcode.com/problems/minimum-number-of-swaps-to-make-the-binary-string-alternating/
//Given a binary string s, return the minimum number of character swaps to make it alternating, or -1 if it is impossible.
int minSwaps(string s) {
	int ones = 0, zeros = 0;
	for (auto c : s)
		if (c == '1') ones++;
		else zeros++;
	if (abs(ones - zeros) > 1) return -1;
	auto swaps = [&](string s, char c) {
		int cnt = 0;
		for (auto ch : s) {
			if (ch != c) cnt++;
			c ^= 1;
		}
		return cnt / 2;
	};

	if (ones > zeros)
		return swaps(s, '1');
	else if (zeros > ones)
		return swaps(s, '0');
	return min(swaps(s, '0'), swaps(s, '1'));
}

//https://leetcode.com/problems/zigzag-conversion/
string convert(string s, int rows, string res = "") {
	int n = s.size(), j = rows, i = 0;
	vector<string>v(rows, "");
	while (i < n) {
		for (int j = 0; i < n and j < rows; j++)
			v[j].push_back(s[i++]);
		for (int j = rows - 2; j >= 1 and i < n; j--)
			v[j].push_back(s[i++]);
	}
	for (auto s : v) res += s;
	return res;
}

//https://leetcode.com/problems/multiply-strings/
string multiply(string s, string t) {
	int m = s.size(), n = t.size();
	string ans(m + n, '0');
	for (int i = m - 1; i >= 0; i--) {
		for (int j = n - 1; j >= 0; j--) {
			int sum = (s[i] - '0') * (t[i] - '0') + ans[i + j + 1];
			ans[i + j + 1] = sum % 10 + '0';
			ans[i + j] += sum / 10;
		}
	}

	for (int i = 0; i < m + n; i++)
		if (ans[i] != '0') return ans.substr(i);
	return "0";
}

//https://leetcode.com/problems/swap-adjacent-in-lr-string/
bool canTransform(string start, string end) {
	int n = start.size();
	string s, t;
	for (auto c : start) if (c != 'X') s += c;
	for (auto c : end) if (c != 'X') t += c;
	if (s != t) return false;
	for (int i = 0, j = 0; i < n and j < n;)
		if (start[i] == 'X') i++;
		else if (end[j] == 'X') j++;
		else {
			if ((start[i] == 'L' and i < j) or (start[i] == 'R' and i > j)) return false;
			i++, j++;
		}
	return true;
}

//https://leetcode.com/problems/shortest-distance-to-a-character/
vector<int> shortestToChar(string s, char c) {
	int n = s.size();
	vector<int>res(n, n);
	int pos = -n;
	for (int i = 0; i < n; i++) {
		if (s[i] == c) pos = i;
		res[i] = i - pos;
	}
	for (int i = n - 1; i >= 0; i--) {
		if (s[i] == c) pos = i;
		res[i] = min(res[i], abs(pos - i));
	}
	return res;
}

//https://leetcode.com/problems/count-substrings-that-differ-by-one-character/
//find the number of substrings in s that differ from some substring in t by exactly one character.
//For example, the underlined substrings in "computer" and "computation" only differ by the 'e'/'a', so this is a valid way.
int countSubstrings(string s, string t) {
	int res = 0, m = s.length(), n = t.length();
	auto helper = [&](int i, int j) {
		int res = 0, pre = 0, curr = 0;
		while (i < m and j < n) {
			curr++;
			if (s[i++] != t[j++]) pre = curr, curr = 0;
			res += pre;
		}
		return res;
	};
	for (int i = 0; i < s.size(); i++)
		res += helper(i, 0);
	for (int j = 1; j < t.size(); j++)
		res += helper(0, j);
	return res;
}


//https://leetcode.com/problems/sum-of-beauty-of-all-substrings/
//The beauty of a string is the difference in frequencies between the most frequent and least frequent characters.
//For example, the beauty of "abaacc" is 3 - 1 = 2
//Given a string s, return the sum of beauty of all of its substrings.
int beautySum(string s) {
	int n = s.size(), ans = 0;
	auto minmax = [](vector<int>& v) {
		int mn = inf, mx = -inf;
		for (auto n : v) {
			if (mx < n) mx = n;
			if (n and mn > n) mn = n;
		}
		return make_pair(mn, mx);
	};
	for (int l = 2; l <= n; l++) {
		vector<int>count(26);
		for (int i = 0; i < l; i++) ++count[s[i] - 'a'];
		auto p = minmax(count);
		ans += p.second - p.first;

		for (int j = l; j < n; j++) {
			++count[s[j] - 'a'], --count[s[j - l] - 'a'];
			auto p = minmax(count);
			ans += p.second - p.first;
		}
	}
	return ans;
}

//https://leetcode.com/problems/different-ways-to-add-parentheses/
vector<int> diffWaysToCompute(string expr) {
	unordered_map<string, vector<int>>results;
	function<vector<int>(string)>compute = [&](string s) {
		vector<int>result;
		int n = s.size();
		for (int i = 0; i < n; i++) {
			char c = s[i];
			if (ispunct(c)) {
				vector<int>result1, result2;
				string substr = s.substr(0, i);
				if (results.find(substr) != results.end())
					result1 = results[substr];
				else result1 = compute(substr);
				substr = s.substr(i + 1);
				if (results.find(substr) != results.end())
					result2 = results[substr];
				else result2 = compute(substr);
				for (int a : result1)
					for (int b : result2)
						result.push_back(c == '+' ? a + b : c == '-' ? a - b : a * b);
			}
		}
		if (result.empty()) result.push_back(stoi(s));
		results[s] = result;
		return result;
	};
	return compute(expr);
}


//https://leetcode.com/problems/camelcase-matching/
//A query word matches a given pattern if we can insert lowercase letters to the pattern word so that it equals the query
//queries = ["FooBar","FooBarTest","FootBall","FrameBuffer","ForceFeedBack"], pattern = "FB"
//answer => [true,false,true,true,false]
vector<bool> camelMatch(vector<string>& queries, string s) {
	auto string_match = [](string s, string t) {
		int i = 0; 
		for (auto c : s)
			if (i < t.length() and c == t[i]) i++;
			else if (c < 'a') return false;
		return i == t.length();
	};
	vector<bool>ans;
	for (auto q : queries)
		ans.push_back(string_match(q, s));
	return ans;
}

//Integer to Roman conversion
string intToRoman(int n) {
	vector<string> M = { "", "M", "MM", "MMM" };
	vector<string> C = { "", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM" };
	vector<string> X = { "", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC" };
	vector<string> I = { "", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX" };
	return M[n / 1000] + C[(n % 1000) / 100] + X[(n % 100) / 10] + I[n % 10];
}

int romanToDecimal(string& s) {
	map<char, int>m;
	int n = 0;
	m['I'] = 1, m['V'] = 5, m['X'] = 10, m['L'] = 50, m['C'] = 100, m['D'] = 500, m['M'] = 1000;
	for (int i = 0; i < s.size(); i++)
		if (m[s[i + 1]] > m[s[i]])
			n += m[s[i + 1]] - m[s[i]], i++;
		else n += m[s[i]];
	return n;
}

//https://leetcode.com/problems/count-and-say/
string countAndSay(int n) {
	string ans = "1";
	while (--n) {
		string curr = "";
		for (int i = 0; i < ans.size(); i++) {
			int count = 1;
			while (i < ans.size() - 1 and ans[i] == ans[i + 1]) i++, count++;
			curr += to_string(count) + ans[i];
		}
		ans = curr;
	}
	return ans;
}

//You are given a string s and an integer k. You can choose any character of the string and change it to any other uppercase English character. 
//You can perform this operation at most k times.
//Return the length of the longest substring containing the same letter you can get after performing the above operations.
// s = "ABAB", k = 2 => 4, s = "AABABBA", k = 1 => 4 ( Replace the one 'A' in the middle with 'B' and form "AABBBBA".The substring "BBBB" has the longest length)
int characterReplacement(string s, int k) {
	int n = s.length(), j = 0, maxCount = 0, len = INT_MIN, count[26] = {};
	for (int i = 0; i < n; i++) {
		maxCount = max(maxCount, ++count[s[i] - 'A']);
		if (i - j + 1 - maxCount > k)
			--count[s[j++] - 'A'];
		len = max(len, i - j + 1);
	}
	return len == INT_MIN ? 0 : len;
}

//given a string s, and an array of pairs of indices in the string pairs where pairs[i] = [a, b] indicates 2 indices(0-indexed) of the string
//You can swap the characters at any pair of indices in the given pairs any number of times
//Return the lexicographically smallest string that s can be changed to after using the swaps
int find(vector<int>& ds, int i) {
	return ds[i] < 0 ? i : ds[i] = find(ds, ds[i]);
}
string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) {
	vector<int>ds(s.size(), -1);
	vector<vector<int>>m(s.size());
	for (auto& p : pairs) {
		int i = find(ds, p[0]), j = find(ds, p[1]);
		if (i != j) ds[j] = i;
	}
	for (int i = 0; i < s.size(); i++)
		m[find(ds, i)].push_back(i);
	for (auto& ids : m) {
		string ss = "";
		for (auto id : ids)
			ss += s[id];
		sort(begin(ss), end(ss));
		for (int i = 0; i < ids.size(); i++) {
			s[ids[i]] = ss[i];
		}
	}
	return s;
}