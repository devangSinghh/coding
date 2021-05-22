#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<math.h>
#include "matrix.h"
#include "array.h"
#include "strings.h"
#include <bitset>
#include <unordered_map>
#include <map>

//define linked lists
struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}
};



//merge 2 sorted link lists (8ms runtime)
//ListNode* mergeTwoLists(ListNode* a, ListNode* b) {
//	if (!a || (b && a->val > b->val)) swap(a, b);
//	while (a) a->next = (a->next, b);
//	return a;
//}