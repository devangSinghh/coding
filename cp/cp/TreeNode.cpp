#include "TreeNode.h"
#include "allheaders.h"
using namespace std;
TreeNode::TreeNode() : val(0), left(nullptr), right(nullptr) {};
TreeNode::TreeNode(int x) : val(x), left(nullptr), right(nullptr) {};
TreeNode::TreeNode(int x, TreeNode* left, TreeNode* right) : val(val), left(left), right(right) {};

//https://leetcode.com/problems/binary-tree-cameras/
// 0 => it's leaf, 1 => parent of leaf with camera, 2 => covered without a camera
int resCameraCover = 0;
int dfsCameraCover(TreeNode* root) {
	if (!root) return 2; //if it's covered we return 2
	int l = dfsCameraCover(root->left), r = dfsCameraCover(root->right);
	if (l == 0 or r == 0) { //if it needs camera
		resCameraCover++;   // increase camera count
		return 1;
	}
	return l == 1 or r == 1 ? 2 : 0;  //return 2 it it's covered otherwise 0(i.e. needs camera)
}
int minCameraCover(TreeNode* root) {
	return (dfsCameraCover(root) == 0 ? 1 : 0) + resCameraCover;
}


//merge K binary trees
class BSTIterator {
    std::stack<TreeNode*> s;
    void pushLeft(TreeNode* n) {
        while (n != nullptr) s.push(std::exchange(n, n->left));
    }
public:
    BSTIterator(TreeNode* root) { 
        pushLeft(root); 
    }
    bool hasNext() const { 
        return !s.empty(); 
    }
    int next() {
        auto n = s.top(); s.pop();
        pushLeft(n->right);
        return n->val;
    }
};
class PeekingIterator : public BSTIterator {
    bool peeked = false;
    int last_val = 0;
public:
    PeekingIterator(TreeNode* root) : BSTIterator(root) { }
    int peek() {
        if (peeked) return last_val;
        peeked = true;
        return last_val = BSTIterator::next();
    }
    int next() {
        if (peeked) {
            peeked = false;
            return last_val;
        }
        return BSTIterator::next();
    }
    bool hasNext() const {
        return peeked || BSTIterator::hasNext();
    }
};
std::vector<int> mergeKTrees(std::vector<TreeNode*> trees) {
    std::vector<int> res;
    std::priority_queue <std::pair<int, PeekingIterator*>,
        std::vector<std::pair<int, PeekingIterator*>>, std::greater<std::pair<int, PeekingIterator*>> > q;
    for (auto t : trees) {
        auto it = new PeekingIterator(t);
        if (it->hasNext()) q.push({ it->peek(), it });
    }
    while (!q.empty()) {
        auto p = q.top(); q.pop();
        res.push_back(p.second->next());
        if (p.second->hasNext())
            q.push({ p.second->peek(), p.second });
    }
    return res;
}


//merge 2 binary trees
void pushLeft(stack<TreeNode*>& s, TreeNode* n) {
    while (n != nullptr)
        s.push(exchange(n, n->left));
}
vector<int> getAllElements(TreeNode* root1, TreeNode* root2) {
    vector<int>res;
    stack<TreeNode*> s1, s2;
    pushLeft(s1, root1);
    pushLeft(s2, root2);
    while (!s1.empty() or !s2.empty()) {
        stack<TreeNode*>& s = s1.empty() ? s2 : s2.empty() ? s1 : s1.top()->val < s2.top()->val ? s1 : s2;
        auto n = s.top(); s.pop();
        res.push_back(n->val);
        pushLeft(s, n->right);
    }
    return res;
}


TreeNode* trimBST(TreeNode* root, int low, int high) {
    if (!root) return nullptr;
    if (root->val < low) return trimBST(root->right, low, high);
    if (root->val > high) return trimBST(root->left, low, high);
    root->left = trimBST(root->left, low, high);
    root->right = trimBST(root->right, low, high);
    return root;
}

//https://leetcode.com/problems/pseudo-palindromic-paths-in-a-binary-tree/
int pseudoPalindromicPaths(TreeNode* root, int count = 0) {
    if (!root) return 0;
    count ^= 1 << (root->val - 1);
    int res = pseudoPalindromicPaths(root->left, count) + pseudoPalindromicPaths(root->right, count);
    if (root->left == root->right and (count & (count - 1)) == 0) res++;
    return res;
}

//https://leetcode.com/problems/all-possible-full-binary-trees/
vector<TreeNode*> allPossibleFBT(int n) {
    static unordered_map<int, vector<TreeNode*>>cache;
    if (cache[n].size()) return cache[n];
    vector<TreeNode*>res;
    if (n == 1) res.push_back(new TreeNode(0));
    else {
        for (int i = 1; i < n; i += 2) {
            int l = i, r = n - 1 - i;
            for (auto left : allPossibleFBT(l)) {
                for (auto right : allPossibleFBT(r)) {
                    TreeNode* root = new TreeNode(0);
                    root->left = left;
                    root->right = right;
                    res.push_back(root);
                }
            }
        }
    }
    cache[n] = res;
    return res;
}

// Construct Binary Tree from Preorder and Postorder Traversal
int preIndex = 0, postIndex = 0;
TreeNode* constructFromPrePost(vector<int>& pre, vector<int>& post) {
    TreeNode* root = new TreeNode(pre[preIndex++]);
    if (root->val != post[postIndex])
        root->left = constructFromPrePost(pre, post);
    if (root->val != post[postIndex])
        root->right = constructFromPrePost(pre, post);
    postIndex++;
    return root;
}

//Morris traversal time => O(n), space => O(1)
vector<int>recoverTree(TreeNode* root) {
    TreeNode* temp = NULL, * pre = NULL, * first = NULL, * second = NULL;
    while (root) {
        if (root->left) {
            temp = root->left;
            while (temp->right and temp->right != root)
                temp = temp->right;
            if (temp->right) {
                if (pre and pre->val > root->val) {
                    if (first == NULL) first = pre;
                    second = root;
                }
                pre = root;
                temp->right = NULL;
                root = root->right;
            }
            else {
                temp->right = root;
                root = root->left;
            }
        }
        else {
            if (pre and pre->val > root->val) {
                if (first == NULL) first = pre;
                second = root;
            }
            pre = root;
            root = root->right;
        }
    }

    if (first and second) {
        swap(first->val, second->val);
    }

    vector<int>res;
    res.push_back(first->val);
    res.push_back(second->val);
    return res;
}


//construct binary tree from inorder and preorder traversal
TreeNode* construct_tree(vector<int>& pre, vector<int>& io, int ps, int s, int e) {
    if (s > e) return NULL;
    TreeNode* root = new TreeNode(pre[ps]);
    int i = find(begin(io) + s, begin(io) + e + 1, pre[ps]) - begin(io);
    root->left = construct_tree(pre, io, ps + 1, s, i - 1);
    root->right = construct_tree(pre, io, i + ps - s + 1, i + 1, e);
    return root;
}

//flatten binary tree to linked list
TreeNode* flatten(TreeNode* root) {
    TreeNode* curr = root;
    while (curr) {
        if (curr->left) {
            TreeNode* runner = curr->left;
            while (runner->right)
                runner = runner->right;
            runner->right = curr->right;
            curr->right = curr->left;
            curr->left = NULL;
        }
        curr = curr->right;
    }
    return root;
}

//Iterative Inorder traversal
vector<int>IterativeInorderTraversal(TreeNode* root) {
    stack<TreeNode*>stk;
    vector<int>tree;

    while (!stk.empty() or root) {
        TreeNode* node = root;
        while (root) {
            stk.push(root);
            root = root->left;
        }
        root = stk.top();
        stk.pop();
        tree.push_back(root->val);
        root = root->right;
    }
    return tree;
}

//Iterative preorder traversal
vector<int>IterativePreorderTraversal(TreeNode* root) {
    if (!root) return {};
    stack<TreeNode*> stk;
    vector<int>v;
    stk.push(root);
    while (!stk.empty()) {
        TreeNode* node = stk.top();
        stk.pop();
        v.push_back(node->val);
        if (node->right)
            stk.push(node->right);
        if (node->left)
            stk.push(node->left);
    }
    return v;
}

//Iterative postorder traversal
vector<int>IterativePostorderTraversal(TreeNode* root) {
    stack<TreeNode*>stk;
    vector<int>v;
    TreeNode* pre = NULL;
    if (!root) return {};
    while (!stk.empty() or root) {
        if (root) {
            stk.push(root);
            root = root->left;
        }
        else {
            TreeNode* node = stk.top();
            if (node->right and node->right != pre) {
                root = node->right;
            }
            else {
                v.push_back(node->val);
                pre = node;
                stk.pop();
            }
        }
    }
    return v;
}

//populate next right pointers
//void connect(TreeLinkNode* root) {
//    TreeLinkNode* prev = NULL, * left = NULL, * curr = root;
//    while (curr) {
//        while (curr) {
//            if (curr->left) {
//                if (prev)
//                    prev->next = curr->left;
//                else
//                    left = curr->left;
//                prev = curr->left;
//            }
//            if (curr->right) {
//                if (prev)
//                    prev->next = curr->right;
//                else
//                    left = curr->right;
//                prev = curr->right;
//            }
//            curr = curr->next;
//        }
//        curr = left;
//        prev = left = NULL;
//    }
//}

//class Node {
//public:
//    int count;
//    Node* ch[26];
//    Node() {
//        count = 0;
//        memset(ch, NULL, sizeof ch);
//    }
//};
//vector<string>prefix(vector<string>& A) {
//
//    auto insert = [](Node* trie, string s) {
//        for (auto c : s) {
//            if (trie->ch[c - 'a'] == NULL)
//                trie->ch[c - 'a'] = new Node();
//            trie = trie->ch[c - 'a'];
//            (trie->count)++;
//        }
//    };
//
//    auto answer = [](Node* trie, string s) {
//        for (int i = 0; i < s.size(); i++) {
//            trie = trie->ch[s[i] - 'a'];
//            if (trie->count == 1)
//                return i;
//        }
//        return (int)s.size();
//    };
//
//    Node* trie = new Node();
//    for (auto s : A) insert(trie, s);
//
//    vector<string>ans;
//    ans.clear();
//
//    for (string s : A) {
//        int j = answer(trie, s);
//        ans.push_back(s.substr(0, j + 1));
//    }
//    return ans;
//}

//2 sum binary tree
int t2Sum(TreeNode* root, int k) {
    stack<TreeNode*>l, r;

    for (TreeNode* curr = root; curr; curr = curr->left)
        l.push(curr);
    for (TreeNode* curr = root; curr; curr = curr->right)
        r.push(curr);

    while (!l.empty() and !r.empty() and l.top() != r.top()) {
        int sum = l.top()->val + r.top()->val;
        if (sum == k) return 1;
        else if (sum < k) {
            TreeNode* p = l.top(); l.pop();
            for (TreeNode* curr = p->right; curr; curr = curr->left)
                l.push(curr);
        }
        else {
            TreeNode* p = r.top(); r.pop();
            for (TreeNode* curr = p->left; curr; curr = curr->right)
                r.push(curr);
        }
    }
    return 0;
}

vector<vector<int>>verticalOrderTraversal(TreeNode* root) {
    vector<vector<int>>v;
    if (root == NULL) return v;

    map<int, vector<int>> hash;
    queue<pair<TreeNode*, int>>q;
    q.push(make_pair(root, 0));

    while (!q.empty()) {
        pair<TreeNode*, int>p = q.front();
        q.pop();

        TreeNode* temp = p.first;
        int count = p.second;

        hash[count].push_back(temp->val);

        if (temp->left)
            q.push(make_pair(temp->left, count - 1));
        if (temp->right)
            q.push(make_pair(temp->right, count + 1));
        free(temp);
    }

    for (auto t : hash) {
        v.push_back(t.second);
    }
    return v;
}