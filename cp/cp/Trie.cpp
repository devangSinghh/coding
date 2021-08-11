
#include<iostream>
#define NOMINMAX
#include<algorithm>
#undef NOMINMAX
#include <stdlib.h>
#include <cctype>
#include<vector>
#include<valarray>
#include<string>
#include<sstream>
using namespace std;
class Node {
public:
    bool isLeaf;
    Node* ch[26];
    Node() {
        isLeaf = false;
        memset(ch, NULL, sizeof ch);
    }
};

void insert(Node*& T, string word) {
    Node* trie = T;
    for (auto c : word) {
        if (trie->ch[c - 'a'] == NULL)
            trie->ch[c - 'a'] = new Node();
        trie = trie->ch[c - 'a'];
    }
    trie->isLeaf = true;
}
int search(Node* trie, string s) {
    Node* T = trie;
    for (char c : s) {
        if (T->ch[c - 'a'] == NULL)
            return 0;
        T = T->ch[c - 'a'];
    }
    return T and T->isLeaf;
}

void findWordStrength() {
    string A = "cool_ice_wifi";
    vector<string>B = { "water_is_cool", "cold_ice_drink", "cool_wifi_speed" };
    auto convert = [](string& s) { for (auto& c : s) if (c == '_') c = ' '; };

    vector<int>v;
    vector<pair<int, int>>p;

    Node* T = new Node();
    convert(A);
    string word;
    stringstream ss;
    ss << A;
    while (ss >> word) {
        insert(T, word);
    }

    int count = 0;

    for (int i = 0; i < B.size(); i++) {
        convert(B[i]);
        ss.clear();

        ss << B[i];

        count = 0;
        while (ss >> word) {
            if (search(T, word))
                count++;
        }

        p.push_back(make_pair(count, i));
    }

    sort(begin(p), end(p), [](auto a, auto b) {
        if (a.first == b.first)
            return a.second < b.second;
        return a.first > b.first;
        });

    for (int i = 0; i < B.size(); i++) {
        v.push_back(p[i].second);
    }

    for (auto n : v)
        cout << n << " ";
}

//maximum XOR subarray
//class Node {
//public:
//    Node* ch[2];
//    int val;
//    Node() {
//        memset(ch, NULL, sizeof ch);
//        val = 0;
//    }
//};
//
//void insert(Node* t, int a) {
//    Node* T = t;
//    for (int i = 31; i >= 0; i--) {
//        bool val = a & (1 << i);
//        if (T->ch[val] == NULL)
//            T->ch[val] = new Node();
//        T = T->ch[val];
//    }
//    T->val = a;
//}
//
//int query(Node* t, int a) {
//    Node* T = t;
//    for (int i = 31; i >= 0; i--) {
//        bool val = a & (1 << i);
//        if (T->ch[1 - val] != NULL)
//            T = T->ch[1 - val];
//        else if (T->ch[val] != NULL)
//            T = T->ch[val];
//    }
//    return a ^ (T->val);
//}
//    int maxSubarrayXOR(int n, int arr[]) {
//        Node* T = new Node();
//        insert(T, 0);
//        int res = INT_MIN, a = 0;
//        for (int i = 0; i < n; i++) {
//            a = a ^ arr[i];
//            insert(T, a);
//            res = max(res, query(T, a));
//        }
//        return res;
//}