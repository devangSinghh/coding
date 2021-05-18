#include<iostream>
#include<algorithm>
#include<vector>
#include<math.h>
#include "matrix.h"
using namespace std;

/*
useful vector STL functions :: 
	v.find(begin(v), end(v), x);
	v.erase(begin(v) + start, begin(s) + end); erase between (start, end)
	unique(begin(v), end(v)); remove duplicates in vector
	sort(begin(v), end(v));
	is_sorted_until(begin(v), end(v)); //returns the first **number(not index)** which is not sorted;
	is_sorted_until(begin(v), end(v), greater<>()); //returns the first **number(not index)** which is not sorted in descending order;
	is_sorted(begin(v), end(v)); checks if vector is sorted or not

*/

//define linked lists
struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}
};

//check if string s1 is subsequence of s2
bool checkSubSequence(string s1, string s2) {
	char* s = &s1[0];
	char* t = &s2[0];
	for (; *t; s += *s == *t++);
	return !*s;
}

//merge 2 sorted link lists
ListNode* mergeTwoLists(ListNode* a, ListNode* b) {
	if (!a || (b && a->val > b->val))
		swap(a, b);
	while (a) a->next = (a->next, b);
	return a;
}

//if a string is palindrome
bool checkPalindrome(string s) {
	return equal(begin(s), end(s), rbegin(s));
}

	


int main() {
	vector<int>v = { 11, 3, 77, 2, -1 };
	bool  a = checkPalindrome("cabbac");
	//cout << a;
	vector<vector<int>> matrix = { {5, 6, 7}, {3, 4, 2}, {7, 8, 2} };
	rotateClockwise(matrix);
	return 0;
}