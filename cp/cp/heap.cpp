#include "allheaders.h"
using namespace std;
//https://leetcode.com/problems/find-k-pairs-with-smallest-sums/
vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
    auto comp = [](auto a, auto b) {
        return a.first + a.second < b.first + b.second;
    };
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(comp)>pq(comp);
    for (int i = 0; i < min((int)nums1.size(), k); i++)
        for (int j = 0; j < min((int)nums2.size(), k); j++)
            if (pq.size() < k) pq.push({ nums1[i], nums2[j] });
            else
                if (nums1[i] + nums2[j] < pq.top().first + pq.top().second)
                    pq.push({ nums1[i], nums2[j] }), pq.pop();
    vector<vector<int>>res;
    while (!pq.empty())
        res.push_back({ pq.top().first, pq.top().second }), pq.pop();
    return res;
}