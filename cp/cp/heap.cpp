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

//heapify an array
void heapify(int arr[], int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < n and arr[l] > arr[largest])
        largest = l;
    if (r < n and arr[r] > arr[largest])
        largest = r;
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

//heap Sort (not a stable sort)
void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}