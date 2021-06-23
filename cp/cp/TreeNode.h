#pragma once
class TreeNode {
public:
	int val;
	TreeNode* left, *right;
	TreeNode();
	TreeNode(int x);
	TreeNode(int x, TreeNode* left, TreeNode* right);
};

//class RangeModule {
//public:
//    map<int, int>m;
//    RangeModule() {}
//    void addRange(int left, int right) {
//        auto it = m.upper_bound(left);
//        if (it != begin(m) and prev(it)->second >= left)
//            left = prev(it)->first;
//        m.insert({ left, removeIntervals(left, right) });
//    }
//    bool queryRange(int left, int right) {
//        auto it = m.upper_bound(left);
//        if (it != begin(m)) it = prev(it);
//        return it->first <= left and it->second >= right; //complete overlapp of range (left, right) within range (it->first, it->second)
//    }
//
//    void removeRange(int left, int right) {
//        int right1 = removeIntervals(left, right);
//        auto it = m.lower_bound(left);
//        if (it != begin(m)) {
//            right1 = max(right1, prev(it)->second);
//            prev(it)->second = min(prev(it)->second, left);
//        }
//        if (right1 > right)
//            m.insert({ right, right1 });
//    }
//    int removeIntervals(int l, int r) {
//        for (auto it = m.lower_bound(l); it != end(m) and it->first <= r; ) {
//            r = max(r, it->second);
//            m.erase(it++);
//        }
//        return r;
//    }
//};