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
//  a->next = mergeTwoLists(a->next, b);
//	return a;
//}

ListNode* merge2Lists(ListNode* A, ListNode* B) {
    ListNode* a = A, * b = B, * merged = NULL, * tail = NULL;
    while (a and b) {
        ListNode* inserted = NULL;
        if (a->val < b->val) {
            inserted = a;
            a = a->next;
        }
        else {
            inserted = b;
            b = b->next;
        }

        if (merged) {
            tail->next = inserted;
            tail = inserted;
        }
        else merged = tail = inserted;
    }

    while (a) tail->next = a, tail = a, a = a->next;
    while (b) tail->next = b, tail = b, b = b->next;
    if (tail) tail->next = NULL;
    return merged;
}

void mergeSortLists(ListNode*& A) {
    if (!A or !A->next)
        return;
    ListNode* mid = A, * fast = A, * prev = NULL;
    while (fast and fast->next)
        prev = mid, mid = mid->next, fast = fast->next->next;
    if (prev) prev->next = NULL;
    mergeSortLists(A);
    mergeSortLists(mid);
    A = merge2Lists(A, mid);
}