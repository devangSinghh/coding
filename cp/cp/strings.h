#pragma once
#include <vector>
#include<algorithm>
#include<string>
typedef std::vector<int> vi;

#ifndef _STRINGS_
#define _STRINGS_
extern void printVectorString(std::vector<std::string>s);
extern bool checkPalindrome(std::string s);
extern bool checkSubSequence(std::string s1, std::string s2);
extern int  countVowelStrings(int n);
extern int  countVowelStringsByCombinations(int n);
extern std::string addTwoBinaryStrings(std::string a, std::string b);
extern void grayCode(int n);
extern std::string longestPalindrome(std::string);
extern int lengthOfLongestSubstring(std::string s);
extern bool searchWord(std::vector<std::vector<char>>board, std::string word);
extern vi failureFunction(vi v);
extern vi failureFunction(string w);
extern bool kmpSearch(string s, string w);
extern void lengthOfLongestPalindromeSubString(std::string s);
extern bool ends_with(std::string s, std::string t);
extern int longestValidParentheses(std::string s);
extern std::string binary(int n);
#endif
