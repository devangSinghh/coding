#include "allheaders.h"

using namespace std;

//if a string is palindrome
bool checkPalindrome(string s) {
	return equal(begin(s), end(s), rbegin(s));
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