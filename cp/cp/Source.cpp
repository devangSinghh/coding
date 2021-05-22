#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<math.h>
#include "matrix.h"
#include "array.h"
#include "strings.h"
using namespace std;

/*
useful vector STL functions :: 
	v.find(begin(v), end(v), x);
	v.erase(begin(v) + start, begin(s) + end); erase between (start, end)
	unique(begin(v), end(v)); remove duplicates in vector
	sort(begin(v), end(v)); //sorts in ascending order
	sort(begin(v), end(v), greater<>()); //sorts in descending order
	is_sorted_until(begin(v), end(v)); //returns the first **number(not index)** which is not sorted;
	is_sorted_until(begin(v), end(v), greater<>()); //returns the first **number(not index)** which is not sorted in descending order;
	is_sorted(begin(v), end(v)); checks if vector is sorted or not
	upper_bound(begin(v), end(v))
	lower_bound(begin(v), end(v))

	accumulate(begin(v), end(v), 0); gives sum of elements of array from begin to end . 3rd parameter is the sum starting value
	distance(begin(v), it) gives distance between any 2 iterators of a vector/string

*/

//define linked lists
struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}
};



//merge 2 sorted link lists (8ms runtime)
ListNode* mergeTwoLists(ListNode* a, ListNode* b) {
	if (!a || (b && a->val > b->val)) swap(a, b);
	while (a) a->next = (a->next, b);
	return a;
}

int Unboundedknapsack(vector<int>& weights, vector<int>& values, int capacity) {
    int n= weights.size();
    int dp[capacity+1];
    memset(dp,0,sizeof(dp));
    for(int i=0;i<=capacity;i++){
        for(int j=0;j<n;j++){
            if(weights[j]<=i){
               dp[i]=max(dp[i],values[j]+dp[i-weights[j]]);
            }
            
        }
    }
    return dp[capacity];
}

int main() {
	vector<int>v = { 1, 2, 3, 4, 5 };
	rotateArrayAntiClockwise(v, 2);
	return 0;
}