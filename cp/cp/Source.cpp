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
#include <functional>
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


//class _rand_ { public: _rand_() { func(); }   void func() { srand((unsigned)time(0)); } };  _rand_ _rno_;
//
//                     clock_t _tstart, _tend;
//
//                     class ___
//                     {
//                     public:
//                         ___() { b(); }
//                         ~___() { e(); }
//                         void b()
//                         {
//                             _tstart = clock();
//#ifndef ONLINE_JUDGE
//                             freopen("input.txt", "r", stdin);
//                             freopen("output.txt", "w", stdout);
//#endif
//                         }
//                         void e()
//                         {
//                             _tend = clock();
//#ifndef ONLINE_JUDGE
//                             nl; nl; cout << "Time Take: " << (double)(_tend - _tstart) / (double)(CLOCKS_PER_SEC) << "s"; nl; nl; nl;
//#endif
//                         }
//                     };

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

vector<vector<string>> nqueen(int n) {
    vector<vector<string>>res;
    vector<string>board(n, string(n, '.'));
    vector<bool>col(n), diag1(2 * n - 1), diag2(2 * n - 1);

    static function<void(int)> dfs = [&](int i) {
        if (i == board.size())
            res.push_back(board);
        for (int j = 0; j < n; j++) {
            if (!col[j] and !diag1[i - j + n - 1] and !diag2[i + j]) {
                board[i][j] = 'Q';
                col[j] = diag1[i - j + n - 1] = diag2[i + j] = true;
                dfs(i + 1);
                board[i][j] = '.';
                col[j] = diag1[i - j + n - 1] = diag2[i + j] = false;
            }
        }
    };
    dfs(0);
    return res;
}


int main() {
    
    /*vector<int>arr = { 1,2,5,3,6,4,1 };
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
    }*/

    auto a = nqueen(8);
    cout << a.size();

}

