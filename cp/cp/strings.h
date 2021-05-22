#pragma once
#include <vector>
#include<algorithm>
#include<string>

#ifndef _STRINGS_
#define _STRINGS_

extern bool checkPalindrome(std::string s);
extern bool checkSubSequence(std::string s1, std::string s2);
extern int  countVowelStrings(int n);
extern int  countVowelStringsByCombinations(int n);
extern std::string addTwoBinaryStrings(std::string a, std::string b);
extern void grayCode(int n);
extern std::string longestPalindrome(std::string);
extern int lengthOfLongestSubstring(std::string s);
extern bool searchWord(std::vector<std::vector<char>>board, std::string word);

#endif
