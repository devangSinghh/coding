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

ListNode* merge(ListNode* a, ListNode* b) {
    ListNode* merged = NULL, * tail = NULL;
    while (a and b) {
        ListNode* c = NULL;
        if (a->val < b->val)
            c = a, a = a->next;
        else c = b, b = b->next;
        if (merged)
            tail->next = c, tail = c;
        else merged = tail = c;
    }
    while (a) tail->next = a, tail = a, a = a->next;
    while (b) tail->next = b, tail = b, b = b->next;
    if (tail) tail->next = NULL;
    return merged;
}
ListNode* mergeSort(ListNode* head) {
    if (!head or !head->next) return head;
    ListNode* prev = NULL, * mid = head, * fast = head;
    while (fast and fast->next) {
        prev = mid, mid = mid->next;
        fast = fast->next->next;
    }
    if (prev) prev->next = NULL;
    head = merge(mergeSort(head), mergeSort(mid));
    return head;
}

//remove loop from linked list
void removeLoop(ListNode* head) {
    ListNode* a = head, * b = head;
    while (b->next and b->next->next) {
        a = a->next;
        b = b->next->next;
        if (a == b) {

            //cycle found
            ListNode* u = a, * v = a;
            unsigned int k = 1, i;
            while (u->next != v) u = u->next, k++;
            u = head, v = head;
            for (i = 0; i < k; i++)
                v = v->next;
            while (u != v) {
                u = u->next;
                v = v->next;
            }
            while (v->next != u)
                v = v->next;
            v->next = NULL;
            return;
        }
    }
}

//delete every kth node from linked list
ListNode* deleteK(ListNode* head, int k) {
    if (!head) return NULL;
    if (k == 1) return NULL;
    int count = 0;
    ListNode* prev = NULL, * curr = head;
    while (curr) {
        count++;
        if (count == k) {
            delete(prev->next);
            prev->next = curr->next;
            count = 0;
        }
        if (count != 0)
            prev = curr;
        curr = prev->next;
    }
    return head;
}

//merge 2 sorted lists in descending order
ListNode* mergeResult(ListNode* a, ListNode* b) {
    if (!a and !b) return NULL;
    ListNode* res = NULL;
    while (a and b) {
        if (a->val <= b->val) {
            ListNode* t = a->next;
            a->next = res;
            res = a;
            a = t;
        }
        else {
            ListNode* t = b->next;
            b->next = res;
            res = b;
            b = t;
        }
    }
    while (a) {
        ListNode* t = a->next;
        a->next = res;
        res = a;
        a = t;
    }
    while (b) {
        ListNode* t = b->next;
        b->next = res;
        res = b;
        b = t;
    }
    return res;
}

//intersection of 2 sorted lists
ListNode* findIntersection(ListNode* head1, ListNode* head2) {
    ListNode* a = head1, * b = head2;
    ListNode* res = NULL, * tail = NULL;;
    while (a and b) {
        if (a->val == b->val) {
            ListNode* t = new ListNode(a->val);
            if (res) tail->next = t;
            else res = t;
            tail = t;
            a = a->next;
            b = b->next;
        }
        else if (a->val < b->val)
            a = a->next;
        else b = b->next;
    }
    return res;
}