#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<math.h>
#include "strings.h"

using namespace std;

//if a string is palindrome
bool checkPalindrome(string s) {
	return equal(begin(s), end(s), rbegin(s));
}

//check if string s1 is subsequence of s2 (the function is effective even if s1 is of order 1e9)
bool checkSubSequence(string s1, string s2) {
	char* s = &s1[0];
	char* t = &s2[0];
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