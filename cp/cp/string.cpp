#include "allheaders.h"
using namespace std;

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
	char* s = &s1[0]; char* t = &s2[0];
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

int romanToDecimal(string &str) {
    map<char,int> m;
    m['I']=1;
    m['V']=5;
    m['X']=10;
    m['L']=50;
    m['C']=100;
    m['D']=500;
    m['M']=1000;
    int sum=0;
    for(int i=0;i<str.size();i++){
        if(m[str[i]]<m[str[i+1]]){
            sum+=m[str[i+1]]-m[str[i]];
            i++;
        }
        else sum+=m[str[i]];
    }
    return sum;
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
//remove occurances of substrings from string
string removeOccurrences(string s, string p) {
	int n = s.size(), m = p.size();
	string str;
	stack<char>stk;
	for (int i = 0; i < n; i++) {
		stk.push(s[i]);
		if (stk.size() >= m) {
			str = "";
			for (int j = m - 1; j >= 0; j--) {
				if (p[j] != stk.top()) {
					int k = 0;
					while (k < str.size()) stk.push(str[k]), k++;
					break;
				}
				else {
					str = stk.top() + str, stk.pop();
				}
			}
		}
	}
	str = "";
	while (!stk.empty())
		str += stk.top(), stk.pop();
	reverse(begin(str), end(str));
	return str;
}

//https://leetcode.com/problems/remove-all-occurrences-of-a-substring/
string removeOccurrencesRecursive(string& s, string part) {
	return s.find(part) != string::npos ? removeOccurrencesRecursive(s = regex_replace(s, regex(part), ""), part) : s;
}
