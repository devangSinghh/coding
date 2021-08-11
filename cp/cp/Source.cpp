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
#include<math.h>
#include<regex>
#include <bitset>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <numeric>
#include <deque>
#include <list>
#include <set>
#include <iterator>
#include <stack>
#include <queue>
#include <iomanip>
//#include "matrix.h"
//#include "array.h"
//#include "graph.h"
//#include "strings.h"
//#include<bits/stdc++.h>
#define all(x) x.begin(), x.end()
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int>pii;
typedef vector<int> vi;
typedef vector<bool> vb;
typedef vector<long long> vl;
typedef vector<pair<int, int>> vpii;
typedef vector<vector<int>>vii;
typedef vector<vector<long long>>vll;
typedef unordered_map<int, int> umap;
#define PQ priority_queue
#define se second
#define fi first
const int inf = INT_MAX;
const int n_inf = INT_MIN;
const int mod = 1e9 + 7;
#pragma GCC optimize("Ofast")
static const auto fast = []() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);
	return 0;
} ();
ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); };
int d2[8][2] = { {0, -1}, {-1, 0}, {0, 1}, {1, 0}, {1, 1}, {-1, 1}, {1, -1}, {-1, -1} };
int dir[5] = { 0, -1, 0, 1, 0 };

unsigned int divisor_count(unsigned int n) {
    unsigned int total = 1;
    for (; (n & 1) == 0; n >>= 1)
        ++total;
    // Odd prime factors up to the square root
    for (unsigned int p = 3; p * p <= n; p += 2) {
        unsigned int count = 1;
        for (; n % p == 0; n /= p)
            ++count;
        total *= count;
    }
    // If n > 1 then it's prime
    if (n > 1)
        total *= 2;
    return total;
}

int GetCeilIndex(vector<int>arr, vector<int>& T, int l, int r, int key) {
    while (r - l > 1) {
        int m = l + (r - l) / 2;
        if (arr[T[m]] >= key)
            r = m;
        else
            l = m;
    }
    return r;
}


int main() {
    
    vector<int>arr = { 1,2,5,3,6,4,1 };
    int n = arr.size();
    vector<vector<int>>L(n);

    L[0].push_back(arr[0]);

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[i] > arr[j] and (L[i].size() < L[j].size()))
                L[i] = L[j];
        }
        L[i].push_back(arr[i]);
    }

    vector<int>lis;

    int mx = 1;

    for (auto p : L) {
        if (p.size() > mx) {
            lis = p;
            mx = p.size();
        }
    }

    for (auto n : lis)
        cout << n << " ";
}

